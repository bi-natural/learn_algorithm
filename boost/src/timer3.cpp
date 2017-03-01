#include <cstdio>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void task1(const boost::system::error_code& e,
  boost::asio::deadline_timer* t, int *count)
{
  if (*count < 5) {
    printf(" %d \n", ++(*count));
    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(task1, boost::asio::placeholders::error, t, count));
  }
}

int main()
{
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  int count = 0;

  t.async_wait(boost::bind(task1, boost::asio::placeholders::error, &t, &count));

  io.run();
  printf("Final count is %d\n", count);
  return 0;
}
