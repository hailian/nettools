/**
    *
    UDP async server based on boost.asio
    made by hailian 
    2020-12-05
    *
**/

#ifndef __UDP_SERVER_H_PP__
#define __UDP_SERVER_H_PP__

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "types.h"

namespace hl
{

  class UdpServer : public boost::enable_shared_from_this<UdpServer>
  {
  public:
    UdpServer(boost::asio::io_service &io_service, short port)
        : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
    }

    void start()
    {
      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&UdpServer::handle_receive_from, shared_from_this(),
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }

    void send(const char *d, size_t len)
    {
      socket_.async_send_to(
          boost::asio::buffer(d, len), sender_endpoint_,
          boost::bind(&UdpServer::handle_send_to, shared_from_this(),
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }

    void setMessageCallback(const MessageCallback cb)
    {
      mesgcb_ = cb;
    }

  private:
    void handle_receive_from(const boost::system::error_code &error,
                             size_t bytes_recvd)
    {
      if (!error)
      {
        if (mesgcb_)
        {
          mesgcb_(data_, bytes_recvd);
        }
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&UdpServer::handle_receive_from, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
      }
    }

    void handle_send_to(const boost::system::error_code & /*error*/,
                        size_t /*bytes_sent*/)
    {
    }

  private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    enum
    {
      max_length = 1024
    };
    char data_[max_length];

    MessageCallback mesgcb_;
  };

} // namespace hl

#endif