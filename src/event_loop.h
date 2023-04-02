#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "ncurses_model.h"

#include <vector>
#include <map>
#include <string>

class EventLoop
{
public:
    enum class Direction
    {
        x,
        y,
    };

private:
    std::map<std::string, NcursesModel> m_models;

public:

    EventLoop();

    void addModel(const NcursesModel& model, const std::string& id) {m_models[id] = model; };
    void removeModel(const std::string& id) { m_models.erase(id); };

    void addKeyEvent(const std::string& id, const char* key = nullptr);
    void addMoveEvent(const std::string& id, double speed);
    void addVectorAnimationEvent(Direction direction, int range, double speed, bool cycle = false);
    void addMatrixChangeEvent(const std::string& id, double every = 0);

    void start();
};

#endif
