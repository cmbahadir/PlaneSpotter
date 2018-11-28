#include "DecodeSBS.h"
#include "TCPListener.h"
#include "AMQPHandler.h"

using namespace std;

int main(int argc, char *argv[]) {
    string hostaddress;
    vector<string> v;
    char comma = ',';
    int hostport = 30003;
    bool connectStatus;

    if(argc < 2) {
        cout << "Usage: sbsDecode <hostname>" << endl;
        return 0;
    }
    else {
        //Class instantiation
        hostaddress = argv[1];
        DecodeSBS* decode = new DecodeSBS();
        TCPListener* client = new TCPListener(hostaddress, hostport);
        connectStatus = client->connected;
        if (connectStatus == true){
            string response = client->read();
            cout << "Response: %s" << response << endl;
            decode->split(response, comma, v);
            client->disconnect(); //Disconnnect method is not implemented.
        }
    }

    // create an instance of your own tcp handler
    MyTcpHandler myHandler;
    int maxfd = 1;
    int result = 0;

    struct timeval tv
    {
        1, 0
    };

    // address of the server
    AMQP::Address address("amqp://test:test@192.168.1.102/");

    // create a AMQP connection object
    AMQP::TcpConnection connection(&myHandler, address);

    // and create a channel
    AMQP::TcpChannel channel(&connection);

    channel.onError([](const char* message)
    {
        std::cout << "channel error: " << message << std::endl;
    });
    channel.onReady([]()
    {
        std::cout << "channel ready " << std::endl;
    });

    // use the channel object to call the AMQP method you like
    channel.declareExchange("my-exchange", AMQP::fanout);
    channel.declareQueue("my-queue");
    channel.bindQueue("my-exchange", "my-queue", "my-routing-key");

    
    do
    {
        FD_ZERO(&rfds);
        std::cout << myHandler.m_fd << std::endl;
        FD_SET(myHandler.m_fd, &rfds);
        if (myHandler.m_fd != -1)
        {
            maxfd = myHandler.m_fd + 1;
        }

        result = select(maxfd, &rfds, NULL, NULL, &tv);
        if ((result == -1) && errno == EINTR)
        {
            std::cout << "Error in socket" << std::endl;
        }
        else if (result > 0)
        {
            if (myHandler.m_flags & AMQP::readable)

                std::cout << "Got something" << std::endl;
            if (FD_ISSET(myHandler.m_fd, &rfds))
            {
                std::cout << "Process over Connection" << std::endl;
                connection.process(maxfd, myHandler.m_flags);
            }
        }
    }
    while (1);

}