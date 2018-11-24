#ifndef DECODESBS_H
#define DECODESBS_H
#include <iostream>
#include <future>
#include <functional>
#include <vector>

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


class decodeSBS {
  public:
    // clientSock(string host, unsigned int port);
    decodeSBS(); //Constructor of decodeSBS
    // clientSock(int sock);
    // ~clientSock();

    void split(const std::string& s, char c,
                std::vector<std::string>& v);

  protected:

  private:

};

#endif // DECODESBS_H