/**
    *
    UDP async client based on boost.asio
    made by hailian 
    2020-12-05
    *
**/

#ifndef __UDP_ASYNC_CLIENT_H_PP__
#define __UDP_ASYNC_CLIENT_H_PP__

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "types.h"

namespace hl
{

  class UdpClient : public boost::enable_shared_from_this<UdpClient>
  {

  public:
    UdpClient(boost::asio::io_service &io_service,
              const std::string &ip_address, const short ip_port)
        : endpoint_(boost::asio::ip::address::from_string(ip_address), ip_port),
          socket_(io_service, endpoint_.protocol())

    {
    }

    void start()
    {
      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), endpoint_,
          boost::bind(&UdpClient::handle_receive_from, shared_from_this(),
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }

    void send(const char *d, size_t len)
    {
      socket_.async_send_to(
          boost::asio::buffer(d, len), endpoint_,
          boost::bind(&UdpClient::handle_send_to, shared_from_this(),
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
          mesgcb_(data_, bytes_recvd);
        }
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), endpoint_,
            boost::bind(&UdpClient::handle_receive_from, shared_from_this(),
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