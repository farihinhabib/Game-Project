// GameUI.cpp
#include "GameUI.hpp"
#include "Diver.hpp"

#include <graphics.h>
#include <string>
#include <cmath>

void GameUI::drawText(int x, int y, const std::string& text, int color) {
    int padding = 2;

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    int textW = textwidth(const_cast<char*>(text.c_str()));
    int textH = textheight(const_cast<char*>(text.c_str()));

    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(x - padding, y - padding, x + textW + padding, y + textH + padding);

    setbkcolor(LIGHTCYAN);
    setcolor(color);
    outtextxy(x, y, const_cast<char*>(text.c_str()));
}

void GameUI::drawBar(int x, int y, int width, int height, int value, int maxValue, int barColor, int borderColor) {
    setcolor(borderColor);
    rectangle(x, y, x + width, y + height);

    int fillWidth = static_cast<int>((float)value / maxValue * width);
    if (fillWidth > width) fillWidth = width;
    if (fillWidth < 0) fillWidth = 0;

    setfillstyle(SOLID_FILL, barColor);
    bar(x + 1, y + 1, x + fillWidth - 1, y + height - 1);
}

void GameUI::drawStats(int health, int oxygen, int time, int score) {
    int startX = 10;
    int startY = 10;  
    int lineHeight = 25;

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    // Time
    drawText(startX, startY + 2, "Time:", GREEN);
    drawBar(startX + 60, startY, 150, 15, time, 60, BLUE, DARKGRAY);

    char timeStr[10];
    sprintf(timeStr, "%d:%02d", time / 60, time % 60);
    drawText(startX + 220, startY + 5, timeStr, BLACK);

    // Health 
    drawText(startX, startY + lineHeight, "Health:", MAGENTA);
    drawBar(startX + 60, startY + lineHeight, 150, 15, health, 100, RED, DARKGRAY);

    // Oxygen 
    drawText(startX, startY + 2 * lineHeight, "Oxygen:", BLACK);
    drawBar(startX + 60, startY + 2 * lineHeight, 150, 15, oxygen, 100, CYAN, DARKGRAY);

    // Score 
    char buffer[50];
    sprintf(buffer, "Score: %d", score);
    drawText(startX, startY + 3 * lineHeight, buffer, LIGHTRED);
}



 
