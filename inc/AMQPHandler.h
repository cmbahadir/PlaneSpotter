
#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
extern fd_set rfds;

class MyTcpHandler : public AMQP::TcpHandler
{
    public:
    //Constructor
    MyTcpHandler();
    //Destructor
    ~MyTcpHandler();
    int m_fd;
    int m_flags;

    private:
    virtual void onAttached(AMQP::TcpConnection *connection) override;
    virtual void onConnected(AMQP::TcpConnection *connection) override;
    virtual bool onSecured(AMQP::TcpConnection *connection, const SSL *ssl) override;
    virtual void onReady(AMQP::TcpConnection *connection) override;
    virtual void onError(AMQP::TcpConnection *connection, const char *message) override;
    virtual void onClosed(AMQP::TcpConnection *connection) override;
    virtual void onLost(AMQP::TcpConnection *connection) override;
    virtual void onDetached(AMQP::TcpConnection *connection) override;
    virtual void monitor(AMQP::TcpConnection *connection, int fd, int flags) override;
};