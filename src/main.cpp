#include "DecodeSBS.h"
#include "TCPListener.h"
#include "AMQPHandler.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

using namespace std;

int main(int argc, char *argv[])
{
    string hostaddress;
    vector<string> v;
    char comma = ',';
    int hostport = 30003;
    bool connectStatus;

    if (argc < 2)
    {
        cout << "Usage: PlaneSpotter <hostname>" << endl;
        return 0;
    }
    else
    {
        //Class instantiation
        hostaddress = argv[1];
        DecodeSBS *decode = new DecodeSBS();
        TCPListener *client = new TCPListener(hostaddress, hostport);
        connectStatus = client->connected;
        while (connectStatus == true)
        {
            string response = client->read();
            cout << "Response: " << response << endl;
            AMQPOperation(hostaddress, response);
            decode->split(response, comma, v);
        }
        client->disconnect(); //Disconnnect method is not implemented.
        
    }
}

