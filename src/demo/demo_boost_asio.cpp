#include "demo_boost_asio.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>      // asio库，需要link libboost_system
#include <boost/bind/bind.hpp> // bind库

#include "utils.h"

namespace asio_ip = boost::asio::ip;

void demo_sync_wait()
{
  boost::asio::io_context io;

  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  t.wait();
  std::cout << "Hello asio!" << std::endl;
}

void print(const boost::system::error_code &e)
{
  std::cout << "Hello asio!" << std::endl;
  std::cout << "error_code: " << e.value() << ", " << e.message() << std::endl;
}

void demo_async_wait()
{
  // 1. io_context
  boost::asio::io_context io;
  // 2. create a new timer
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  // 3. async wait
  t.async_wait(&print);
  // 4. run context
  io.run();
}

void print_3params(const boost::system::error_code &e, boost::asio::steady_timer *t, int *count)
{
  if (*count < 5)
  {
    std::cout << *count << std::endl;
    ++*count;

    t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
    // await
    t->async_wait(boost::bind(print_3params, boost::asio::placeholders::error, t, count));
    std::cout << "---" << std::endl;
  }
}

void demo_bind()
{
  boost::asio::io_context io;

  int count = 0;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  // await
  t.async_wait(boost::bind(print_3params,
                           boost::asio::placeholders::error, &t, &count));
  io.run();

  std::cout << "Final count is " << count << std::endl;
}

void Printer::print()
{
  {
    if (count < 5)
    {
      std::cout << count << std::endl;
      ++count;
      timer.expires_at(timer.expiry() + boost::asio::chrono::seconds(1));
      timer.async_wait(boost::bind(&Printer::print, this));
    }
  }
}

void demo_member_function()
{

  boost::asio::io_context io;
  Printer p(io);
  io.run();
}

void MultiThreadedPrinter::print1()
{
  if (count < 10)
  {
    std::cout << std::this_thread::get_id() << " Timer 1: " << count << std::endl;
    ++count;
    t1.expires_at(t1.expiry() + boost::asio::chrono::seconds(1));
    t1.async_wait(b_asio::bind_executor(
        strand,
        boost::bind(
            &MultiThreadedPrinter::print1,
            this)));
  }
}

void MultiThreadedPrinter::print2()
{
  if (count < 10)
  {
    std::cout << std::this_thread::get_id() << " Timer 2: " << count << std::endl;
    ++count;
    t2.expires_at(t2.expiry() + boost::asio::chrono::seconds(1));
    t2.async_wait(b_asio::bind_executor(
        strand,
        boost::bind(
            &MultiThreadedPrinter::print2,
            this)));
  }
}

void demo_multi_threading()
{
  b_asio::io_context io;
  MultiThreadedPrinter p(io);
  // 子线程run
  boost::thread t(boost::bind(&b_asio::io_context::run, &io));

  // 主线程run
  io.run();

  // join子线程
  t.join();
}

void demo_tcp()
{
  boost::asio::io_context ctx;
  asio_ip::tcp::resolver resolver(ctx);
  asio_ip::tcp::resolver::query query("fapi.binance.com", "https");
  asio_ip::tcp::resolver::iterator iter = resolver.resolve(query);
  asio_ip::tcp::resolver::iterator end; // End marker.
  while (iter != end)
  {
    asio_ip::tcp::endpoint endpoint = *iter++;
    std::cout << endpoint << std::endl;
  }
}

int main()
{
  // RUN_DEMO(demo_sync_wait);
  // RUN_DEMO(demo_async_wait);
  // RUN_DEMO(demo_bind);
  // RUN_DEMO(demo_member_function);
  // RUN_DEMO(demo_multi_threading);
  RUN_DEMO(demo_tcp);
  return EXIT_SUCCESS;
}