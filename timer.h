/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008 - 2014 André Müller
 *
 *****************************************************************************/

#ifndef AM_TIMER_H
#define AM_TIMER_H

#include <ctime>
#include <ratio>
#include <chrono>


namespace am {


/*****************************************************************************
 *
 *
 * @brief simple timer class
 *
 *
 *****************************************************************************/
class timer
{
    using basic_duration_t = std::chrono::milliseconds;

public:
    //---------------------------------------------------------------
    void
    start() {
        if(!running_) {
            running_ = true;
            start_ = std::chrono::high_resolution_clock::now();
        }
    }
    //-----------------------------------------------------
    void
    reset() {
        total_ = basic_duration_t(0);
        running_ = false;
    }
    //-----------------------------------------------------
    void
    restart() {
        reset();
        start();
    }

    //-----------------------------------------------------
    void
    stop() {
        if(running_) {
            stop_ = std::chrono::high_resolution_clock::now();
            total_ += std::chrono::duration_cast<basic_duration_t>(stop_-start_);
            running_ = false;
        }
    }


    //---------------------------------------------------------------
    // GETTERS
    //---------------------------------------------------------------
    bool
    running() const {
        return running_;
    }

    //-----------------------------------------------------
    int64_t
    milliseconds() const {
        return std::chrono::duration_cast<
            std::chrono::milliseconds>(current()).count();
    }

    int64_t
    full_seconds() const {
        return std::chrono::duration_cast<
            std::chrono::seconds>(current()).count();
    }

    int
    full_minutes() const {
        return std::chrono::duration_cast<
            std::chrono::minutes>(current()).count();
    }

    int
    full_hours() const {
        return std::chrono::duration_cast<
            std::chrono::hours>(current()).count();
    }


    //-----------------------------------------------------
    double
    seconds() const {
        return (milliseconds() / 1000.0);
    }

    double
    minutes() const {
        return (milliseconds() / 60000.0);
    }

    double
    hours() const {
        return (milliseconds() / 3600000.0);
    }


private:
    //-----------------------------------------------------
    basic_duration_t
    current() const {
        if(!running_) return total_;

        return (
            total_ + (std::chrono::duration_cast<basic_duration_t>(
                std::chrono::high_resolution_clock::now() - start_)) );
    }

    //---------------------------------------------------------------
    std::chrono::high_resolution_clock::time_point start_, stop_;
    basic_duration_t total_ = basic_duration_t(0);
    bool running_ = false;
};


}  // namespace am


#endif
