#include "UdpClient.hpp"
#include <boost/shared_ptr.hpp>

void onMessageCallback(char *d, size_t len)
{
  std::cout << "onMessageCallback:" << std::string(d, len) << std::endl;
}

int main(int argc, char *argv[])
{
  try
  {
    boost::asio::io_service io_service;
    //hl::UdpClient client(io_service,9999);
    //client.start();
    boost::shared_ptr<hl::UdpClient> client = boost::make_shared<hl::UdpClient>(io_service, "127.0.0.1", 9999);
    //client->setMessageCallback(boost::bind(&onMessageCallback,_1,_2));
    client->start();

    std::string msg("hello from client");
    client->send(msg.data(), msg.length());

    io_service.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}