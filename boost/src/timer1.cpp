#include <cstdio>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    boost::asio::io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

    t.wait();

    printf("Hello, World\n");
    return 0;
}
