#ifndef NCURSES_MODEL_H
#define NCURSES_MODEL_H

#include <ncurses.h>
#include <cstddef>
#include <vector>
#include <stdexcept>

class NcursesModel
{
public:
    using matrix_t = std::vector<std::string>;
    using frames_vec_t = std::vector<matrix_t>;

    enum class Coord
    {
      x,
      y,
    };

private:

    int m_x;
    int m_y;
    int m_prevX;
    int m_prevY;

    frames_vec_t    m_frames;
    int m_midX;
    int m_midY;

    bool m_hasAnimation{};
    std::vector<int> m_animation;
    Coord m_direction;
    int m_animateEvery;
    std::size_t m_currentAnimationFrame;
    int m_frameCount;

    int  m_prevFrameNum{};
    int  m_currentFrameNum{};
    int  m_frameNumber{};


public:


    NcursesModel(WINDOW* window = stdscr, frames_vec_t m_framesVector = {}, int m_x = 0, int m_y = 0);

    int x() const { return m_x; }
    int y() const { return m_y; }
    void move(int m_xCoord, int m_yCoord) { m_prevX =m_x; m_prevY = m_y,m_x =m_xCoord; m_y = m_yCoord; }

    bool hasAnimation()    { return m_hasAnimation; }
    void setHasAnimation(bool hasAnimation) { m_hasAnimation = hasAnimation; }

    const matrix_t& getCurrentMatrix() const  { return m_frames.at( m_currentFrameNum);    }
    int getCurrentFrameNum()              { return  m_currentFrameNum; }
    void setCurrentFrameNum(int num)      {  m_prevFrameNum = m_currentFrameNum; m_currentFrameNum = num; }
    int getMaxFrameNum() const { return m_frameNumber; };
    const matrix_t& getMatrix(int number) { return m_frames.at(number); }

    void nextFrame();
    void print(WINDOW* win = stdscr);
    void clear(WINDOW* win = stdscr);
    void clearPrevious(WINDOW* win = stdscr);
    void applyAnimation(Coord coord, std::vector<int> coords, int everyFrames = 1);
};

#endif
