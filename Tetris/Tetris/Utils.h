#ifndef __UTILS_H
#define __UTILS_H
constexpr int columnOffset = 1;
constexpr int rowOffset = 4;
constexpr int boardWidth = 10;
constexpr int boardLength = 15;

enum eKey { Left = 'g', Right = 'j', Down = 'h', Stop = 's', Rotate = 'y', Quit = '9', IncreaseSpeed = '3', DecreaseSpeed = '4', PauseResume = '2', New = '1' };

const int ShapeSize = 4;

const Point FirstAppearance = { 5,4 };

#endif __UTILS_H
