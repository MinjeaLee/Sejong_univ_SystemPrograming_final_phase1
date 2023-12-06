/* client_mul.c
 * Author : Lee Minjae
 * ID     : 21011741
 * dept   : Information Security
 * date   : 2023.12.06
 * Contact: leejoy2@sju.ac.kr
 * repo   : https://github.com/MinjeaLee/Sejong_univ_SystemPrograming_final_phase1
*/

#include "client.h"

int main()
{
	int sockfd, portno = 2222, n; // sockfd(소켓 파일 디스크립터), portno(포트 번호), n(송 및 수신된 바이트 수)
	struct sockaddr_in serv_addr; // 서버 주소 정보 구조체
	struct hostent *server;		  // 호스트 정보 구조체
	char buffer[256];			  // 데이터 송수신에 사용되는 버퍼

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // TCP/IP 소켓 생성
	if (sockfd < 0)
		error("ERROR opening socket"); // 소켓 생성 실패시 에러 메시지 출력

	server = gethostbyname("localhost"); // 서버의 호스트 이름을 'localhost'로 설정 (localhost == 로컬)
	if (server == NULL)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *)&serv_addr, sizeof(serv_addr)); // 서버 주소 구조체 초기화
	serv_addr.sin_family = AF_INET;				  // 주소 체계를 IPv4로 설정
	bcopy((char *)server->h_addr,
		  (char *)&serv_addr.sin_addr.s_addr,
		  server->h_length);			// 서버의 IP 주소 설정
	serv_addr.sin_port = htons(portno); // 포트 번호를 네트워크 바이트 순서로 변환하여 설정

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting"); // 서버에 연결을 시도, 실패시 에러 메시지를 출력

	printf("Enter two numbers for addition (x y): "); // 사용자에게 두 숫자를 입력하라는 메시지 출력
	int x, y;
	scanf("%d %d", &x, &y); // 두 숫자 입력
	sprintf(buffer, "mult:%d,%d", x, y); // 버퍼에 두 숫자를 포맷에 맞게 저장 (mul:x,y, mul일 시 앞에 mul 접두사를 붙여줌)

	n = write(sockfd, buffer, strlen(buffer)); // 서버에 데이터 전송
	if (n < 0)
		error("ERROR writing to socket"); // 데이터 전송 실패시 에러 메시지 출력

	bzero(buffer, 256);			   // 버퍼 초기화
	n = read(sockfd, buffer, 255); // 서버로부터 데이터 수신
	if (n < 0)
		error("ERROR reading from socket"); // 데이터 수신 실패시 에러 메시지 출력

	printf("%s\n", buffer); // 수신된 데이터(곱셈 결과) 출력
	close(sockfd);			// 소켓 연결 종료
	return 0;
}