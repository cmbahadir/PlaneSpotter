#include "TCPListener.h"

using boost::asio::deadline_timer;
using boost::asio::ip::tcp;

client::client(boost::asio::io_service &io_service)
    : stopped_(false),
      socket_(io_service),
      deadline_(io_service),
      heartbeat_timer_(io_service)
{
}

client::~client()
{
    
}

// Called by the user of the client class to initiate the connection process.
// The endpoint iterator will have been obtained using a tcp::resolver.
void client::start(tcp::resolver::iterator endpoint_iter)
{
    // Start the connect actor.
    client::start_connect(endpoint_iter);

    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
    client::deadline_.async_wait(boost::bind(&client::check_deadline, this));
}

// This function terminates all the actors to shut down the connection. It
// may be called by the user of the client class, or by the class itself in
// response to graceful termination or an unrecoverable error.
void client::stop()
{
    client::stopped_ = true;
    client::socket_.close();
    client::deadline_.cancel();
    client::heartbeat_timer_.cancel();
}

void client::start_connect(tcp::resolver::iterator endpoint_iter)
{
    if (endpoint_iter != tcp::resolver::iterator())
    {
        std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

        // Set a deadline for the connect operation.
        deadline_.expires_from_now(boost::posix_time::seconds(60));

        // Start the asynchronous connect operation.
        socket_.async_connect(endpoint_iter->endpoint(),
                              boost::bind(&client::handle_connect,
                                          this, _1, endpoint_iter));
    }
    else
    {
        // There are no more endpoints to try. Shut down the client.
        stop();
    }
}

void client::handle_connect(const boost::system::error_code &ec,
                            tcp::resolver::iterator endpoint_iter)
{
    if (client::stopped_)
        return;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!client::socket_.is_open())
    {
        std::cout << "Connect timed out\n";

        // Try the next available endpoint.
        client::start_connect(++endpoint_iter);
    }

    // Check if the connect operation failed before the deadline expired.
    else if (ec)
    {
        std::cout << "Connect error: " << ec.message() << "\n";

        // We need to close the socket used in the previous connection attempt
        // before starting a new one.
        client::socket_.close();

        // Try the next available endpoint.
        client::start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
        std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

        // Start the input actor.
        client::start_read();

        // Start the heartbeat actor.
        client::start_write();
    }
}

void client::start_read()
{
    // Set a deadline for the read operation.
    client::deadline_.expires_from_now(boost::posix_time::seconds(30));

    // Start an asynchronous operation to read a newline-delimited message.
    boost::asio::async_read_until(client::socket_, client::input_buffer_, '\n',
                                  boost::bind(&client::handle_read, this, _1));
}

void client::handle_read(const boost::system::error_code &ec)
{
    if (client::stopped_)
        return;

    if (!ec)
    {
        // Extract the newline-delimited message from the buffer.
        std::string line;
        std::istream is(&input_buffer_);
        std::getline(is, line);

        // Empty messages are heartbeats and so ignored.
        if (!line.empty())
        {
            std::cout << "Received: " << line << "\n";
        }

        client::start_read();
    }
    else
    {
        std::cout << "Error on receive: " << ec.message() << "\n";

        stop();
    }
}

void client::check_deadline()
{
    if (client::stopped_)
        return;

    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (client::deadline_.expires_at() <= deadline_timer::traits_type::now())
    {
        // The deadline has passed. The socket is closed so that any outstanding
        // asynchronous operations are cancelled.
        client::socket_.close();

        // There is no longer an active deadline. The expiry is set to positive
        // infinity so that the actor takes no action until a new deadline is set.
        client::deadline_.expires_at(boost::posix_time::pos_infin);
    }

    // Put the actor back to sleep.
    client::deadline_.async_wait(boost::bind(&client::check_deadline, this));
}

void client::start_write()
{
    if (client::stopped_)
        return;

    // Start an asynchronous operation to send a heartbeat message.
    boost::asio::async_write(client::socket_, boost::asio::buffer("\n", 1),
                             boost::bind(&client::handle_write, this, _1));
}

void client::handle_write(const boost::system::error_code &ec)
{
    if (client::stopped_)
        return;

    if (!ec)
    {
        // Wait 10 seconds before sending the next heartbeat.
        client::heartbeat_timer_.expires_from_now(boost::posix_time::seconds(10));
        client::heartbeat_timer_.async_wait(boost::bind(&client::start_write, this));
    }
    else
    {
        std::cout << "Error on heartbeat: " << ec.message() << "\n";

        stop();
    }
}
