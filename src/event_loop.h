#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

class EventLoop
{
private:
    unsigned int m_refreshRate;

public:

    EventLoop();

    void setRefreshRate(unsigned int refreshRate) { m_refreshRate = refreshRate; };
    void addModel();
    void removeModel();
    void addEvent();
    void removeEvent();
    void onAnyKeyPressed();

    void start();
};

#endif
