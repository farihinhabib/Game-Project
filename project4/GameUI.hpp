#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <string>
#include <graphics.h>
#include "Diver.hpp"

class GameUI {
public:
    GameUI() = default;

    void drawText(int x, int y, const std::string& text, int color = 15);
    void drawBar(int x, int y, int width, int height, int value, int maxValue, int barColor, int borderColor);
    void drawStats(int health, int oxygen, int time, int score);

};

#endif