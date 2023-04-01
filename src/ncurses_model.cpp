#include "ncurses_model.h"

#include "util.h"

#include <ncurses.h>
#include <stdexcept>
#include <iostream>

NcursesModel::NcursesModel(WINDOW* window, frames_vec_t framesVector, int x, int y)
    : m_frames{framesVector},
      m_x{x}, m_y{y}, m_midX{}, m_midY{},
      m_prevX{x}, m_prevY{y},
      m_animateEvery{}, m_currentAnimationFrame{},
      win{window}
{
    m_currentFrameNum = 0;
    m_frameNumber = m_frames.size();

}

void NcursesModel::nextFrame()
{
    m_prevFrameNum = m_currentFrameNum;
    ++m_currentFrameNum;
    if (m_currentFrameNum == m_frameNumber)
    {
        m_currentFrameNum = 0;
    }
}

void NcursesModel::print(bool* panic_status, bool panic)
{
    int x{m_x};
    int y{m_y};

    if (m_currentAnimationFrame < m_animation.size())
    {
        if (m_direction == Coord::x)
        {
            x += m_animation[m_currentAnimationFrame];
        }
        else if (m_direction == Coord::y)
        {
            y += m_animation[m_currentAnimationFrame];
        }
        ++m_currentAnimationFrame;
    }

    printMatrix(win, x, y, getMatrix(m_currentFrameNum), panic_status, panic);

    m_prevX = x;
    m_prevY = y;
}

void NcursesModel::clear()
{
    clearMatrix(win, m_x, m_y, getMatrix(m_currentFrameNum));
}

void NcursesModel::clearPrevious()
{
    clearMatrix(win, m_prevX, m_prevY, getMatrix(m_prevFrameNum));
    m_prevFrameNum = m_currentFrameNum;

}

void NcursesModel::applyAnimation(Coord coord, std::vector<int> coords, int frames)
{
    m_animation = coords;
    m_direction = coord;
    m_animateEvery = frames;
    m_currentAnimationFrame = 0;
}
