#include "AMQPHandler.h"

int AMQPOperation(std::string hostname, std::string message)
{
    //AMQP Handlers
    boost::asio::io_service service(4);
    AMQP::LibBoostAsioHandler handler(service);
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@" + hostname + "/"));
    AMQP::TcpChannel adsbChannel(&connection);
    adsbChannel.declareExchange("ADSB_EXCHANGE", AMQP::fanout);
    adsbChannel.declareQueue("ADSB_QUEUE").onSuccess([&connection](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
        std::cout << "declared queue " << name << std::endl;
        //connection.close();
    });
    adsbChannel.bindQueue("ADSB_EXCHANGE", "ADSB_QUEUE", "my-key");

    //Publish Message to the Queue
    adsbChannel.startTransaction();
    adsbChannel.publish("ADSB_EXCHANGE", "my-key", message);
    adsbChannel.commitTransaction();
    return service.run();
}
