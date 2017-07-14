#ifndef PARALLAX_TIME_HPP_GUARD
#define PARALLAX_TIME_HPP_GUARD

#include <boost/timer/timer.hpp>

namespace Parallax
{
    /*
     * For now on, use Boost for time until we have to optimize the code or the compilation don't work
     */
    /**
     * \namespace   Parallax::Timer
     * \ingroup     PIL
     */
    namespace Timer = boost::timer;
}

#endif
