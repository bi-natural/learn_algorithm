#include <cstdio>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void task1(const boost::system::error_code& e)
{
  printf("Hello, world.. async_timer\n");
}

int main()
{
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

  t.async_wait(task1);

  io.run();
  return 0;
}
