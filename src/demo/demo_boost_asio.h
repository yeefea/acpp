#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace b_asio = boost::asio;

class Printer
{
public:
  Printer(boost::asio::io_context &io)
      : timer(io, boost::asio::chrono::seconds(1)), count(0)
  {
    auto method = &Printer::print; // (this->*method)();

    // bind member function写法
    // boost::bind(method, this)
    timer.async_wait(boost::bind(method, this));
    // timer.async_wait(boost::bind(&Printer::print, this));  这样更简单
  }
  void print();
  ~Printer()
  {
    std::cout << "Printer final count is " << count << std::endl;
  }

private:
  boost::asio::steady_timer timer;
  int count;
};

class MultiThreadedPrinter
{

public:
  MultiThreadedPrinter(b_asio::io_context &io)
      : strand(b_asio::make_strand(io)),
        t1(io, b_asio::chrono::seconds(1)),
        t2(io, b_asio::chrono::seconds(1)),
        count(0)
  {
    t1.async_wait(b_asio::bind_executor(strand, boost::bind(&MultiThreadedPrinter::print1, this)));
    t2.async_wait(b_asio::bind_executor(strand, boost::bind(&MultiThreadedPrinter::print2, this)));
  }
  ~MultiThreadedPrinter(){
    std::cout << "MultiThreadedPrinter final count is " << count << std::endl;
  }

  void print1();
  void print2();

private:
  b_asio::strand<b_asio::io_context::executor_type> strand;
  b_asio::steady_timer t1;
  b_asio::steady_timer t2;
  int count;
};