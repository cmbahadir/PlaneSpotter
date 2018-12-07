#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
#include <amqpcpp/libboostasio.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>

#ifndef AMQPHANDLER_H
#define AMQPHANDLER_H

int AMQPOperation(std::string, std::string);

#endif