#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    // domain resolve
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
        resolver.resolve(argv[1], "50013");
    for (auto &x : endpoints)
    {
      std::cout << x.endpoint() << std::endl;
    }
    // create tcp socket
    tcp::socket socket(io_context);
    // connect to endpoints, may throw
    boost::system::error_code error;
    auto endpoint = boost::asio::connect(socket, endpoints, error);
    if (error.failed())
    {
      std::cerr << error.message() << std::endl;
      return EXIT_FAILURE;
    }

    for (;;)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}