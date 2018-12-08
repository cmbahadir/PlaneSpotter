#include "DecodeSBS.h"
#include "TCPListener.h"
#include "AMQPHandler.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

using namespace std;
using boost::asio::deadline_timer;
using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        /*AMQP*/
        boost::asio::io_service amqp_service(4);
        AMQP::LibBoostAsioHandler handler(amqp_service);
        AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@localhost/"));
        AMQPHandler adsb(connection);
        adsb.AMQPConfigure();
        adsb.AMQPPublishMessage("test_message");

        //Decode SBS Sentence
        //TODO: Decode for logging after getting SBS Sentence String
        //vector<string> v;
        //DecodeSBS decode();
        //decode.split(reponse, ",", v)

        //TCP Client Service
        boost::asio::io_service io_service;
        tcp::resolver r(io_service);
        client c(io_service);

        c.start(r.resolve(tcp::resolver::query(argv[1], argv[2])));

        //Transfering handlers of services to run in parallel
        boost::thread_group threads;
        threads.create_thread(boost::bind(&boost::asio::io_service::run, &amqp_service));
        io_service.run();
        threads.join_all();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
