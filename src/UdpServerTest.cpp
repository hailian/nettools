#include "UdpServer.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void onMessageCallback(char *d, size_t len)
{
  std::cout << "onMessageCallback:" << std::string(d, len) << std::endl;
}

int main(int argc, char *argv[])
{
  try
  {
    boost::asio::io_service io_service;
    //hl::UdpServer server(io_service,9999);
    //server.start();
    boost::shared_ptr<hl::UdpServer> server = boost::make_shared<hl::UdpServer>(io_service, 9999);    
    server->setMessageCallback(boost::bind(&onMessageCallback, _1, _2));
    server->start();

    io_service.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}