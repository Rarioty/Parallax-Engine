#ifndef TIME_HPP
#define TIME_HPP

#include <boost/timer/timer.hpp>

namespace Parallax
{
    /*
     * For now on, use Boost for time until we have to optimize the code or the compilation don't work
     */
    namespace Timer = boost::timer;
}

#endif
