#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 

void error(const char *msg) { perror(msg); exit(0); }

int adsb_post(char hex, char flight, int altitude, int speed, char lat, char lon, char track, int messages, int seen){

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
	char *message, response[4096], *data, *host;
	host="selftronics.com";
	int portno=80;
	
	
	sprintf(data,"\r\n?hex=%s&flight=%s&altitude=%s&speed=%s&lat=%s&lon=%s&track=%s&messages=%s&seen=%s\r\n",
			hex,flight,altitude,speed,lat,lon,track,messages,seen);
	message_size=strlen(data);
	sprintf(message,"POST /add.php HTTP/1.1\r\n Host:www.selftronics.com\r\nContent-Length : %s\r\nContent-Type : application/x-www-form-urlencoded\r\n",message_size);
	strcat(message,data);
	
	printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
	printf("Request:\n%s\n",server);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
	total = sizeof(response)-1;
	received = 0;
	do {
		printf("RESPONSE: %s\n", response);
		// HANDLE RESPONSE CHUCK HERE BY, FOR EXAMPLE, SAVING TO A FILE.
		memset(response, 0, sizeof(response));
		bytes = recv(sockfd, response, 1024, 0);
		if (bytes < 0)
			printf("ERROR reading response from socket");
		if (bytes == 0)
			break;
		received+=bytes;
	} while (1); 

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);
    return 0;
}