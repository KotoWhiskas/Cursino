#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>
#include <cstddef>
#include <vector>
#include <string>

void clearMatrix(WINDOW* screen, int x, int y, const std::vector<std::string>& matrix);
void printMatrix(WINDOW* screen, int x, int y, const std::vector<std::string>& matrix, bool* panic_status = nullptr, bool panic = false);


#endif
