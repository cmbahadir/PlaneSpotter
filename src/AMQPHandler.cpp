#include "AMQPHandler.h"

AMQPHandler::AMQPHandler(AMQP::TcpConnection &connection)
    : amqpChannel_(&connection),
      amqp_exchange_name_("ADSB_EXCHANGE"),
      amqp_queue_name_("ADSB_QUEUE"),
      amqp_key_("MY-KEY")
{
}

AMQPHandler::~AMQPHandler()
{
}

void AMQPHandler::AMQPConfigure()
{
    AMQPHandler::amqpChannel_.declareExchange(AMQPHandler::amqp_exchange_name_, AMQP::fanout);
    AMQPHandler::amqpChannel_.declareQueue(AMQPHandler::amqp_queue_name_);
    AMQPHandler::amqpChannel_.bindQueue(AMQPHandler::amqp_exchange_name_, AMQPHandler::amqp_queue_name_, AMQPHandler::amqp_key_);
}

void AMQPHandler::AMQPPublishMessage(std::string message)
{
    AMQPHandler::amqpChannel_.startTransaction();
    AMQPHandler::amqpChannel_.publish(AMQPHandler::amqp_exchange_name_, AMQPHandler::amqp_key_, message);
    AMQPHandler::amqpChannel_.commitTransaction();
}
