#include "DecodeSBS.h"
#include "TCPListener.h"
#include "AMQPHandler.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

using namespace std;

int main(int argc, char *argv[]) {
    string hostaddress;
    vector<string> v;
    char comma = ',';
    int hostport = 30003;
    bool connectStatus;

    if(argc < 2) {
        cout << "Usage: PlaneSpotter <hostname>" << endl;
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
    // access to the boost asio handler
    // note: we suggest use of 2 threads - normally one is fin (we are simply demonstrating thread safety).
    boost::asio::io_service service(4);

    // handler for libev
    AMQP::LibBoostAsioHandler handler(service);
    
    // make a connection
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@localhost/"));
    
    // we need a channel too
    AMQP::TcpChannel channel(&connection);
    
    // create a temporary queue
    channel.declareQueue(AMQP::exclusive).onSuccess([&connection](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
        
        // report the name of the temporary queue
        std::cout << "declared queue " << name << std::endl;
        
        // now we can close the connection
        connection.close();
    });
    
    // run the handler
    // a t the moment, one will need SIGINT to stop.  In time, should add signal handling through boost API.
    return service.run();
}