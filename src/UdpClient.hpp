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
#include "UdpSession.hpp"

namespace hl
{

  class UdpClient : public boost::enable_shared_from_this<UdpClient>
  {

  public:
    UdpClient(boost::asio::io_service &io_service,
              const std::string &ip_address, const short ip_port)
        : endpoint_(boost::asio::ip::address::from_string(ip_address), ip_port),
        session_(boost::make_shared<UdpSession >(io_service,endpoint_))
          //socket_(io_service, endpoint_.protocol()),
          //session_(io_service,endpoint_)

    {
      //session_ = boost::make_shared<UdpSession >(io_service,endpoint_);
    }

    void start()
    {
      session_->start();
    }

    void send(const char *d, size_t len)
    {
      session_->send(d,len);
    }

    void setMessageCallback(const MessageCallback cb)
    {
      //mesgcb_ = cb;
      session_->setMessageCallback(cb);
    }

  private:
    

  private:
    boost::asio::ip::udp::endpoint endpoint_;
    //boost::asio::ip::udp::socket socket_;
    UdpSession_ptr session_;
    MessageCallback mesgcb_;
  };

} // namespace hl

#endif