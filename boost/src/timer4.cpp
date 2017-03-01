#include <cstdio>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class task1 {
public:
    task1(boost::asio::io_service& io) : timer_(io, boost::posix_time::seconds(1)),
    count_(0)
    {
      timer_.async_wait(boost::bind(&task1::print, this));
    }
    ~task1()
    {
      printf("Final count is %d\n", count_);
    }

    void print()
    {
      if (count_ < 5) {
        printf(" %d \n", count_);
        ++count_;

        timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&task1::print, this));
      }
    }
  private:
    boost::asio::deadline_timer timer_;
    int count_;
};

int main()
{
  boost::asio::io_service io;
  task1 t(io);
  io.run();
  return 0;
}
