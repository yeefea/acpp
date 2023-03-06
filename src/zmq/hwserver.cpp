#include <string>
#include <iostream>
#include <unistd.h>
#include <cppzmq/zmq.hpp>
#include <cppzmq/zmq_addon.hpp>

int main(int argc, char **argv)
{
  // 注意：
  // 先启动client，再启动server。ok，client会等待server启动
  // client在等待响应的时候关掉server，再重新启动server，client无法自动恢复。

  auto version = zmq::version();

  std::cout << "ZeroMQ version: " << std::get<0>(version) << "." << std::get<1>(version) << "." << std::get<2>(version) << std::endl;

  zmq::context_t context(2);
  zmq::socket_t socket(context, zmq::socket_type::rep);
  socket.bind("tcp://*:5555");
  // server
  while (true)
  {
    zmq::message_t request;

    //  Wait for next request from client
    socket.recv(request, zmq::recv_flags::none);
    std::cout << "Received Hello" << std::endl;

    //  Do some 'work'
    sleep(1);

    //  Send reply back to client
    zmq::message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply, zmq::send_flags::none);
  }
  return EXIT_SUCCESS;
}