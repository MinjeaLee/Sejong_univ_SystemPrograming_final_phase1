/* client.h 
 * Author : Lee Minjae
 * ID     : 21011741
 * dept   : Information Security
 * date   : 2023.12.06
 * Contact: leejoy2@sju.ac.kr
*/

#ifndef CLIENT_H
# define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

#endif