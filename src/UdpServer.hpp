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
#include "UdpSession.hpp"

namespace hl
{

  class UdpServer : public boost::enable_shared_from_this<UdpServer>
  {
  public:
    UdpServer(boost::asio::io_service &io_service, short port)
        : session_(boost::make_shared<UdpSession>(io_service, port))
    {
    }

    void start()
    {
      session_->start();
    }

    void send(const char *d, size_t len)
    {
      session_->send(d, len);
    }

    void setMessageCallback(const MessageCallback cb)
    {
      session_->setMessageCallback(cb);
    }

  private:
    UdpSession_ptr session_;
    MessageCallback mesgcb_;
  };

} // namespace hl

#endif