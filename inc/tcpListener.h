#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <iostream>
#include <future>
#include <functional>

#include <errno.h>
#include <string.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/signal.h>

class tcpListener {
  public:
    tcpListener(std::string host, unsigned int port);
    tcpListener();
    tcpListener(int sock);
    ~tcpListener();

    bool hasError();
    int connect(std::string host, unsigned int port);
    int disconnect();

    int write(std::string mesg);
    std::string read();
    std::string readAll();

    std::string host;
    unsigned int port;
    bool connected;

  protected: //Can be accessed via child classes

  private:
    int enable_keepalive(int sock);

    static const unsigned int buffSize = 1000;
    int sockfd;//establish connection to ID distribution server
    struct sockaddr_in servaddr;
    char recv[buffSize];
    struct hostent* server;
};

#endif // TCPLISTENER_H