// GameManager.cpp
#include "GameManager.hpp"
#include <graphics.h>
#include <windows.h>   // for GetAsyncKeyState, Sleep
#include <mmsystem.h>  // for PlaySound
#pragma comment(lib, "winmm.lib")
#include <iostream>

GameManager::GameManager() : isRunning(false), frameCount(0), diver((400, 300)) {}

void GameManager::showMenu() {
    initwindow(840, 480, "Treasure Diver");
    startTime = std::chrono::steady_clock::now();

    bool waitingForChoice = true;
    PlaySound("start.wav", NULL, SND_FILENAME | SND_ASYNC);

    readimagefile("1.bmp", 0, 0, 840, 480);

    while (waitingForChoice) {

        if (GetAsyncKeyState('1') & 0x8000) {
            isRunning = true;
            waitingForChoice = false;
        } else if (GetAsyncKeyState('2') & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            isRunning = false;
            waitingForChoice = false;
        }

        delay(100);

        if (isRunning) {
            PlaySound("bgm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // Start game music
        }

        startTime = std::chrono::steady_clock::now();

        frameCount = 0; 

    }
}

void GameManager::updateGameWithStats(const Diver& diverRef) {
    PlaySound(NULL, 0, 0); 
    PlaySound("over1.wav", NULL, SND_FILENAME | SND_ASYNC); 

    setvisualpage(0);  
    setactivepage(0);
  
    readimagefile("2.bmp", 0, 0, 840, 480);

    char score[50]; 
    sprintf(score, "Final Score: %d", diverRef.getScore()); 
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);  
    setcolor(WHITE);
    int textW = textwidth(score);
    int textH = textheight(score);
    int scoreX = (getmaxx() - textW) / 2;
    int scoreY = 250;

    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(scoreX, scoreY, scoreX + textW, scoreY + textH);

    setbkcolor(BLUE);
    outtextxy(scoreX, scoreY, score);
    
    delay(7000);
    getch();  
}

void GameManager::frame() {
    Point p = diver.getPosition();
    int w = getmaxx();
    int h = getmaxy();

    if (p.x < 0) p.x = 0;
    if (p.x > w) p.x = w;
    if (p.y < 0) p.y = 0;
    if (p.y > h) p.y = h;

    diver.setPosition(p);
    frameCount++;
}

void GameManager::endGame() {
    closegraph();
}

bool GameManager::getIsRunning() const {
    return isRunning;
}

