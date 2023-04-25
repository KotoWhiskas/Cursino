#include "event_loop.h"
#include "dino.h"
#include "cactus.h"
#include "frames.h"

#include <ncurses.h>

int main()
{
    EventLoop eventLoop{};

    eventLoop.addModel(Dino{}, "dino1");

    eventLoop.onKeyPressed(ARROW_UP,
                           [=]() { eventLoop.vectorAnimate("dino1", EventLoop::Direction::y, 2.5, true); } );
    eventLoop.onKeyPressed(ARROW_DOWN,
        [=]() { eventLoop.vectorUndoAnimation("dino1"); } );
    eventLoop.onKeyPressed(ARROW_DOWN,
        [=]() { auto& dino = eventLoop.get("dino1"); dino.changeFrame(Frames::Dino::dinoCrouch); } );
    eventLoop.onKeyReleased(ARROW_DOWN,
        [=]() { auto& dino = eventLoop.get("dino1"); dino.nextFrame(); } );


    eventLoop.everySeconds(5, eventLoop.multiplier,
        [=]() { eventLoop.addModel(Cactus{}, "cactus", MAX_X + 10, Y); };
    );

    eventLoop.afterModelAdded("cactus", 0,
        [=]() { eventLoop.vectorAnimate("cactus", EventLoop::Direction::x, -10, false); }
    );

    eventLoop.afterModelAdded("cactus", 5,
        [=]() { eventLoop.removeModel("cactus"); }
    );


    eventLoop.onCollision("dino1", cactus,
        [=]() { eventLoop.stop(); eventLoop.printMid("Game Over!"); }

    );

    eventLoop.show("dino1");
    eventLoop.show("cactus");
    eventLoop.start();


    return 0;
}
