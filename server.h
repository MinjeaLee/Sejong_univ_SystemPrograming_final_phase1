/* server.h
 * Author : Lee Minjae
 * ID     : 21011741
 * dept   : Information Security
 * date   : 2023.12.06
 * Contact: leejoy2@sju.ac.kr
*/

#ifndef SERVER_H
# define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct 
{
	int sock; // 클라이언트 소켓
	int num1;
	int num2;
} operation_data;	

void *handle_client(void *sockfd);

#endif