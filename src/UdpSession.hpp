/**
    *
    UDP session based on boost.asio
    made by hailian 
    2020-12-06
    *
**/

#ifndef __UDP_ASYNC_SESSION_H_PP__
#define __UDP_ASYNC_SESSION_H_PP__

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "types.h"
#include <boost/make_shared.hpp>

namespace hl
{

  class UdpSession : public boost::enable_shared_from_this<UdpSession>
  {

  public:
    UdpSession(boost::asio::io_service &io_service, const std::string &ip_address, const short ip_port)
        : endpoint_(boost::asio::ip::address::from_string(ip_address), ip_port),
          socket_(io_service, endpoint_.protocol())
    {
    }

    UdpSession(boost::asio::io_service &io_service, short port)
        : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
    }

    void start()
    {
      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), endpoint_,
          boost::bind(&UdpSession::handle_receive_from, shared_from_this(),
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }

    void send(const char *d, size_t len)
    {
      socket_.async_send_to(
          boost::asio::buffer(d, len), endpoint_,
          boost::bind(&UdpSession::handle_send_to, shared_from_this(),
                      boost::asio::placeholders::error));
    }

    void setMessageCallback(const MessageCallback cb)
    {
      mesgcb_ = cb;
    }

  private:
    void handle_send_to(const boost::system::error_code &error)
    {
      if (!error)
      {
      }
    }

    void handle_receive_from(const boost::system::error_code &error,
                             size_t bytes_recvd)
    {
      if (!error)
      {
        if (mesgcb_)
        {
          mesgcb_(shared_from_this(), data_, bytes_recvd);
        }
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), endpoint_,
            boost::bind(&UdpSession::handle_receive_from, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
      }
    }

  private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;

    enum
    {
      max_length = 1024
    };
    char data_[max_length];

    MessageCallback mesgcb_;
  };

} // namespace hl

#endif