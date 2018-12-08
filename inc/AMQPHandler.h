#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
#include <amqpcpp/libboostasio.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>

#ifndef AMQPHANDLER_H
#define AMQPHANDLER_H

class AMQPHandler
{
  public:
    AMQPHandler(AMQP::TcpConnection &connection);
    ~AMQPHandler();
    void AMQPConfigure();
    void AMQPPublishMessage(std::string message);
  private:
    AMQP::TcpChannel amqpChannel_;
    std::string amqp_exchange_name_;
    std::string amqp_queue_name_;
    std::string amqp_key_;
};

#endif