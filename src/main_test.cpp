#include "event_loop.h"

int main()
{
    EventLoop eventLoop{};

    eventLoop.start();

    return 0;
}
