/* server.c
 * Author : Lee Minjae
 * ID     : 21011741
 * dept   : Information Security
 * date   : 2023.12.06
 * Contact: leejoy2@sju.ac.kr
 */

#include "server.h"

void *addition(void *data)
{
	operation_data *op_data = (operation_data *)data; // 연산 데이터 구조체
	int result = op_data->num1 + op_data->num2;	// 두 숫자를 더함
	char buffer[256];							// 송수신 버퍼

	sprintf(buffer, "Addition result: %d", result);	// 버퍼에 덧셈 결과를 저장
	write(op_data->sock, buffer, strlen(buffer));	// 클라이언트에 덧셈 결과 전송
	printf("Addition result: %d\n", result);		// 덧셈 결과 출력
	free(data); // 구조체 메모리 해제
	return NULL;
}

void *multiplication(void *data)
{
	operation_data *op_data = (operation_data *)data;		// 연산 데이터 구조체
	int result = op_data->num1 * op_data->num2;			// 두 숫자를 곱함
	char buffer[256];

	sprintf(buffer, "Multiplication result: %d", result);	// 버퍼에 곱셈 결과를 저장
	write(op_data->sock, buffer, strlen(buffer));			// 클라이언트에 곱셈 결과 전송
	printf("Multiplication result: %d\n", result);		// 곱셈 결과 출력
	free(data); // 구조체 메모리 해제
	return NULL;
}

void *handle_client(void *sockfd)
{
	int sock = *(int *)sockfd;			// 클라이언트 소켓 파일 디스크립터
	char buffer[256];					// 데이터 송수신에 사용되는 버퍼
	int n;								// 송수신된 바이트 수

	bzero(buffer, 256);					// 버퍼 초기화
	n = read(sock, buffer, 255);		// 클라이언트로부터 데이터 수신
	if (n < 0)							// 데이터 수신 실패시 에러 메시지 출력
	{
		perror("ERROR reading from socket");
		close(sock);
		return NULL;
	}

	printf("Received: %s\n", buffer);	// 수신된 데이터 출력

	char *token = strtok(buffer, ":");	// 버퍼에서 ':' 문자를 기준으로 문자열을 자름 (add:1,2 -> add, 1,2)
	pthread_t thread_id;				// 스레드 아이디
	operation_data *op_data = malloc(sizeof(operation_data));	// 연산 데이터 구조체 동적 할당
	op_data->sock = sock;						// 연산 데이터 구조체에 클라이언트 소켓 파일 디스크립터 저장

	if (strcmp(token, "add") == 0)			// 덧셈 연산일 경우
	{
		token = strtok(NULL, ",");			// 버퍼에서 ',' 문자를 기준으로 문자열을 자름 (1,2 -> 1, 2)
		op_data->num1 = atoi(token);		// 문자열을 정수형으로 변환하여 연산 데이터 구조체에 저장
		token = strtok(NULL, ",");			
		op_data->num2 = atoi(token);

		pthread_create(&thread_id, NULL, addition, op_data);		// 덧셈 연산 스레드 생성
	}
	else if (strcmp(token, "mult") == 0)	// 덧셈 메커니즘과 동일
	{
		token = strtok(NULL, ",");
		op_data->num1 = atoi(token);
		token = strtok(NULL, ",");
		op_data->num2 = atoi(token);

		pthread_create(&thread_id, NULL, multiplication, op_data);
	}
	else
	{
		sprintf(buffer, "Invalid operation");	// 연산이 잘못되었을 경우 에러 메시지를 버퍼에 저장
		write(sock, buffer, strlen(buffer));	// 클라이언트에 에러 메시지 전송
		free(op_data);
	}

	pthread_detach(thread_id);				// 스레드 종료시 자원 해제
	return NULL;
}

int main()
{
	int sockfd, newsockfd, portno = 2222; 	// 소켓 파일 디스크립터 및 포트 번호 설정
	socklen_t clilen;						//  클라이언트 주소 정보 구조체
	struct sockaddr_in serv_addr, cli_addr;	// 서버 및 클라이언트 주소 정보 구조체

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// TCP/IP 소켓 생성
	if (sockfd < 0)
	{
		perror("ERROR opening socket");			// 소켓 생성 실패시 에러 메시지 출력
		exit(1);
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));	// 서버 주소 구조체 초기화
	serv_addr.sin_family = AF_INET;					// 주소 체계를 IPv4로 설정
	serv_addr.sin_addr.s_addr = INADDR_ANY;			// 서버의 IP 주소를 자동으로 찾아서 설정
	serv_addr.sin_port = htons(portno);				// 포트 번호를 네트워크 바이트 순서로 변환하여 설정

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)	// 소켓에 서버 주소 정보를 할당
	{
		perror("ERROR on binding");								// 할당 실패시 에러 메시지 출력
		exit(1);
	}

	listen(sockfd, 5);							// 소켓을 수동 대기모드로 설정, 최대 5개의 클라이언트가 대기 가능
	clilen = sizeof(cli_addr);					// 클라이언트 주소 정보 구조체의 크기 설정

	while (1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);	// 클라이언트의 연결 요청 수락
		if (newsockfd < 0)								// 연결 요청 수락 실패시 에러 메시지 출력
		{
			perror("ERROR on accept");
			continue;
		}

		handle_client((void *)&newsockfd); 					// 덧셈 및 곱셈 핸들러함수 호출
	}

	close(sockfd);				// 소켓 연결 종료
	return 0;
}