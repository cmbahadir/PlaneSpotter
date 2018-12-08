#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
#include <amqpcpp/libboostasio.h>
#include <boost/asio/strand.hpp>

#ifndef TCPLISTENER_H
#define TCPLISTENER_H

class client
{
  public:
    client(boost::asio::io_service &io_service);
    ~client();
    void start(boost::asio::ip::tcp::resolver::iterator endpoint_iter);
    void stop();
  private:
    void start_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iter);
    void handle_connect(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator endpoint_iter);
    void start_read();
    void handle_read(const boost::system::error_code &ec);
    void start_write();
    void handle_write(const boost::system::error_code&);
    void check_deadline();

  private:
    bool stopped_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf input_buffer_;
    boost::asio::deadline_timer deadline_;
    boost::asio::deadline_timer heartbeat_timer_;
};

#endif