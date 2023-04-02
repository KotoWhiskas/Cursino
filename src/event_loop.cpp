#include "event_loop.h"

#include "util.h"

#include <chrono>
#include <iostream>



EventLoop::EventLoop()
{

}

void EventLoop::start()
{
    while (true)
    {
        static int frameCounter{};
        static int fps60Counter{};

        auto start{std::chrono::steady_clock::now()};
        auto start_ms{std::chrono::time_point_cast<std::chrono::milliseconds>(start)};

        // do stuff



        auto end{std::chrono::steady_clock::now()};
        auto end_ms{std::chrono::time_point_cast<std::chrono::milliseconds>(end)};

        std::chrono::duration<double> elapsedMS{end - start};


        static constexpr float fps60sleep{16.66};
        sleep(fps60sleep - elapsedMS.count());
    }
}
