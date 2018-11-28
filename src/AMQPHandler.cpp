#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
#include "AMQPHandler.h"
fd_set rfds;

//Constructor
MyTcpHandler::MyTcpHandler()
{
    m_fd = -1;
    m_flags = 0;
}

//Destructor
MyTcpHandler::~MyTcpHandler()
{
}

void MyTcpHandler::monitor(AMQP::TcpConnection *connection, int fd, int flags)
{
    std::cout << "Monitor" << std::endl;
    if (flags == 0)
        return;
    std::cout << "FD" << fd << " Flags " << flags << std::endl;
    if (flags & AMQP::readable) //check if FD`s flag indcates that file is readable
    {
        FD_SET(fd, &rfds);
        MyTcpHandler::m_fd = fd;
        MyTcpHandler::m_flags = flags;
    }
    //connection->process(fd, flags);
    // @todo
    //  add your own implementation, for example by adding the file
    //  descriptor to the main application event loop (like the select() or
    //  poll() loop). When the event loop reports that the descriptor becomes
    //  readable and/or writable, it is up to you to inform the AMQP-CPP
    //  library that the filedescriptor is active by calling the
    //  connection->process(fd, flags) method.
}

bool MyTcpHandler::onSecured(AMQP::TcpConnection *connection, const SSL *ssl)
{
    return true;
}

void MyTcpHandler::onAttached(AMQP::TcpConnection *connection)
{
    // @todo
    //  add your own implementation, for example initialize things
    //  to handle the connection.
}

void MyTcpHandler::onConnected(AMQP::TcpConnection *connection)
{
    // @todo
    //  add your own implementation (probably not needed)
}

void MyTcpHandler::onReady(AMQP::TcpConnection *connection)
{
    //@todo
    //  add your own implementation, for example by creating a channel
    //  instance, and start publishing or consuming
}

void MyTcpHandler::onError(AMQP::TcpConnection *connection, const char *message)
{
    // @todo
    //  add your own implementation, for example by reporting the error
    //  to the user of your program and logging the error
}

void MyTcpHandler::onClosed(AMQP::TcpConnection *connection)
{
    // @todo
    //  add your own implementation (probably not necessary, but it could
    //  be useful if you want to do some something immediately after the
    //  amqp connection is over, but do not want to wait for the tcp
    //  connection to shut down
}

void MyTcpHandler::onLost(AMQP::TcpConnection *connection)
{
    // @todo
    //  add your own implementation (probably not necessary)
}

void MyTcpHandler::onDetached(AMQP::TcpConnection *connection)
{
    // @todo
    //  add your own implementation, like cleanup resources or exit the application
}