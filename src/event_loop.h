#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "ncurses_model.h"

#include <chrono>
#include <cstddef>
#include <curses.h>
#include <locale>
#include <vector>
#include <map>
#include <array>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>
#include <algorithm>
#include <cmath>

class EventLoop
{
public:
    using ncurses_key_t  = int;


    enum class Direction
    {
        x,
        y,
    };

    enum class DirectionValue
    {
        positive,
        negative,
    };

    struct Animation
    {
        std::string id;
        Direction direction{};
        DirectionValue directionValue{};
        int distance{};
        double speed{};
        bool loop{};
        double overcome{};
        double total{};

        int step{};
        bool onRepeat{false};
        bool done{false};

    };

    struct DestinationAnimation
    {

        NcursesModel model{};
        int x{};
        int y{};
        double time{};

        int distanceX{};
        int distanceY{};
        double overcomeX{0};
        double overcomeY{0};
        double totalX{0};
        double totalY{0};
        double speedX{};
        double speedY{};
        int stepX{};
        int stepY{};
        bool doneX{false};
        bool doneY{false};

        DestinationAnimation()
        {

        }

        DestinationAnimation(NcursesModel _model, int _x, int _y, double _time) : model{_model}, x(_x), y(_y), time{_time}
        {
            distanceX = std::abs(x - model.x());
            distanceY = std::abs(y - model.y());
            speedX = static_cast<double>(distanceX) / time;
            speedY = static_cast<double>(distanceY) / time;
            stepX = (x > model.x()) ? 1 : -1;
            stepY = (y > model.y()) ? 1 : -1;
        }



    };

    struct CoordinatesFuncPair
    {
        int x{};
        int y{};
        std::function<void()> func{};
    };

    struct TimeFuncPair
    {
        std::chrono::milliseconds set{};
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> timePoint{};
        std::function<void()> func{};
        int* add{nullptr};
    };

    struct KeyFuncPair
    {
        ncurses_key_t key{};
        std::function<void()> func{};
    };


    // pair aliases
    using str_pair_t      = std::pair<std::string, std::string>;

    // event container item alisases
    using str_func_pair_t  = std::pair<str_pair_t, std::function<void()>>;

private:

    struct ModelWrapper
    {
        NcursesModel model{};
        std::string id{};
        bool hasAnimation{false};
        bool show{false};
    };

    // every model is associated with std::string ud
    std::unordered_map<std::string, ModelWrapper> m_models;

    // every event is associated with Model std::string id
    // so after removing a model from loop, all it's events would be removed too

    // event containers
    std::map<std::string, KeyFuncPair>   m_keyPressEvents;
    std::map<std::string, KeyFuncPair>   m_keyReleaseEvents;
    std::map<std::string, Animation>     m_animations;
    std::map<std::string, DestinationAnimation> m_destAnimations;
    std::map<std::string, TimeFuncPair>  m_timeEvents;
    std::map<std::string, str_func_pair_t>   m_collisionEvents;
    std::map<std::string, CoordinatesFuncPair>   m_moveEvents;

    int m_lastKeyPress{};
    bool drawModel(const ModelWrapper& wrapper) const;

    ModelWrapper& getWrapper(const std::string& id) { return m_models[id]; }


public:

    EventLoop();

    int frameCount{};

    // getters and setters
    std::size_t modelCount()
    {
        return m_models.size();
    }

    NcursesModel& getModel(const std::string& id)
    {
        return m_models[id].model;
    }

    NcursesModel& addModel(const NcursesModel& model, const std::string& id, int x, int y)
    {
        m_models[id] = ModelWrapper{model, id};

        NcursesModel& newModel{getModel(id)};
        newModel.move(x, y);

        return newModel;
    };

    template <typename T, typename Y>
    void rm(const std::string& id, std::map<T, Y>& map)
    {
        if (map.count(id) > 0)
            map.erase(id);
    }

    template <typename T, typename Y>
    void rm(const std::string& id, std::unordered_map<T, Y>& map)
    {
        if (map.count(id) > 0)
            map.erase(id);
    }

    void removeModel(const std::string& id)
    {
        rm(id, m_models);
        rm(id, m_animations);
        rm(id, m_destAnimations);
        rm(id, m_collisionEvents);
        rm(id, m_keyPressEvents);
        rm(id, m_keyReleaseEvents);
        rm(id, m_timeEvents);

    }

    void clearAnimations()
    {
        m_animations.clear();
    }


    // event setters
    void everyMilliseconds(const std::string& associatedWith, int ms, std::function<void()> exec, int* add = nullptr);

    void onKeyPressed(const std::string& associatedWith, int key, std::function<void()> exec)
    {
        m_keyPressEvents[associatedWith] = {key, exec};
    }

    void onKeyReleased(const std::string& associatedWith, int key, std::function<void()> exec)
    {
        m_keyReleaseEvents[associatedWith] = {key, exec};
    }

    void onCollision(const std::string& associatedWith, const std::string& model1, const std::string& model2, std::function<void()> exec)
    {

        m_collisionEvents[associatedWith] = {{model1, model2}, exec};
    }

    void onModelMovedTo(const std::string& associatedWith, int x, int y, std::function<void()> exec)
    {
        m_moveEvents[associatedWith] = {x, y, exec};
    }

    void vectorAnimate(const std::string& id, Direction direction, DirectionValue directionValue, int range, double speed, bool cycle = false)
    {
        if (m_animations.count(id) == 0)
            m_animations[id] = Animation{id, direction, directionValue, range, speed, cycle};
    }

    void destAnimate(const std::string& id, int x, int y, double time)
    {
        m_destAnimations[id] = DestinationAnimation{getModel(id), x, y, time};
    }

    void show(const std::string& id) { getWrapper(id).show = true; }

    // event execution
    void executeTimeEvents();
    void executeVectorAnimtaions();
    void executeDestinationAnimations();
    void executeKeyEvents();
    void executeDrawEvents();
    void executeMoveEvents();


    void start();
    void stop();
};

#endif
