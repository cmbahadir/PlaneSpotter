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
    //AMQP Handlers
    boost::asio::io_service service(4);
    AMQP::LibBoostAsioHandler handler(service);

    string hostaddress;
    vector<string> v;
    char comma = ',';
    int hostport = 30003;
    bool connectStatus, queueDeclareStat;

    if(argc < 2) {
        cout << "Usage: PlaneSpotter <hostname>" << endl;
        return 0;
    }
    else {
        AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@localhost/"));
        AMQP::TcpChannel adsbChannel(&connection);
        adsbChannel.declareExchange("ADSB_EXCHANGE",AMQP::fanout);
        adsbChannel.declareQueue("ADSB_QUEUE").onSuccess([&connection](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            std::cout << "declared queue " << name << std::endl;
            //connection.close();
        });
        adsbChannel.bindQueue("ADSB_EXCHANGE", "ADSB_QUEUE", "my-key");
        //Class instantiation
        hostaddress = argv[1];
        DecodeSBS* decode = new DecodeSBS();
        TCPListener* client = new TCPListener(hostaddress, hostport);
        connectStatus = client->connected;
        if (connectStatus == true){
            string response = client->read();
            cout << "Response: " << response << endl;
            //TODO : Publish response
            adsbChannel.startTransaction();
            adsbChannel.publish("ADSB_EXCHANGE", "my-key", response);
            adsbChannel.commitTransaction();
            decode->split(response, comma, v);
            client->disconnect(); //Disconnnect method is not implemented.
        }
        return service.run();
    }
}