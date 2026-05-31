// main.cpp
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <chrono>

#include "Diver.hpp"
#include "OxygenTank.hpp"
#include "TreasureChest.hpp"
#include "Collectible.hpp"
#include "Point.hpp"
#include "GameManager.hpp"
#include "GameUI.hpp"
#include "Shark.hpp"
#include "Mine.hpp"

const int SAFE_ZONE_TOP = 180;
const int SAFE_ZONE_BOTTOM = 380;
const int TIME_LIMIT = 60;

bool checkCollision(Point a, Point b, int threshold = 40) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return (dx * dx + dy * dy <= threshold * threshold);
}

int main() {
    srand((unsigned)time(nullptr));

    GameManager gameManager;
    gameManager.showMenu();
    if (!gameManager.getIsRunning()) return 0;

    auto startTime = std::chrono::steady_clock::now();
    GameUI ui;
    Diver diver(Point(100, 300));
    diver.setSpeed(15);

    int page = 0;
    std::vector<Collectible*> collectibles;
    std::vector<Shark> sharks;
    std::vector<Mine> mines;

    bool survivedWithoutDamage = true;

    for (int i = 0; i < 3; ++i) {
        int x1 = 300 + i * 250 + rand() % 100;
        int y1 = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 100);
        collectibles.push_back(new TreasureChest(Point(x1, y1), 100));

        int x2 = 300 + i * 250 + rand() % 100;
        int y2 = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 100);
        collectibles.push_back(new OxygenTank(Point(x2, y2), 50));
    }

    for (int i = 0; i < 2; ++i) {
        int sharkX = 400 + i * 300 + rand() % 100;
        int sharkY = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 100);
        sharks.push_back(Shark(Point(sharkX, sharkY)));

        int mineX = 400 + i * 300 + rand() % 100;
        int mineY = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 100);
        mines.push_back(Mine(Point(mineX, mineY), 30));
    }

    int collectibleSpawnTimer = 0;
    int oxygenFrameCounter = 0;
    int sharkDamageCooldown = 0;
    int mineSpawnTimer = 0;

    while (diver.getHealth() > 0 && diver.getOxygenLevel() > 0 && gameManager.getIsRunning()) {
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - startTime).count();
        int timeLeft = TIME_LIMIT - elapsed;
        if (timeLeft < 0) timeLeft = 0;

        if (timeLeft <= 0) break;

        bool tookDamage = false;

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        readimagefile("gameplay.bmp", 0, 0, 840, 480);

        if (sharkDamageCooldown > 0) sharkDamageCooldown--;

        if (GetAsyncKeyState(VK_LEFT)) diver.move("left");
        if (GetAsyncKeyState(VK_RIGHT)) diver.move("right");
        if (GetAsyncKeyState(VK_UP)) diver.move("up");
        if (GetAsyncKeyState(VK_DOWN)) diver.move("down");

        collectibleSpawnTimer++;
        if (collectibleSpawnTimer >= 30) {
            collectibleSpawnTimer = 0;
            int x = 400 + rand() % 500;
            int y = SAFE_ZONE_TOP + 50 + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 150);

            if (rand() % 2 == 0)
                collectibles.push_back(new TreasureChest(Point(x, y), 100));
            else
                collectibles.push_back(new OxygenTank(Point(x, y), 50));
        }

        for (auto*& c : collectibles) {
            if (!c) continue;
            c->move();
            Point pos = c->getPosition();
            c->setPosition(pos);
            c->draw();

            if (checkCollision(diver.getPosition(), pos)) {
                if (auto* tc = dynamic_cast<TreasureChest*>(c))
                    diver.setScore(diver.getScore() + tc->collect());
                else if (auto* ot = dynamic_cast<OxygenTank*>(c))
                    diver.setOxygenLevel(diver.getOxygenLevel() + ot->collect());
                delete c; c = nullptr;
            }
        }

        collectibles.erase(std::remove_if(collectibles.begin(), collectibles.end(),
            [](Collectible* c) {
                if (!c || c->getPosition().x < -50) {
                    delete c;
                    return true;
                }
                return false;
            }), collectibles.end());

        diver.draw();

        for (auto& shark : sharks) {
            shark.move();
            Point pos = shark.getPosition();
            pos.y = std::max(SAFE_ZONE_TOP, std::min(pos.y, SAFE_ZONE_BOTTOM - 40));
            shark.setPosition(pos);
            shark.draw();

            if (checkCollision(diver.getPosition(), pos, 35) && sharkDamageCooldown <= 0) {
                diver.takeDamage(20);
                sharkDamageCooldown = 20;
            }
        }

        if (++oxygenFrameCounter >= 15) {
            diver.updateOxygen();
            oxygenFrameCounter = 0;
        }

        mineSpawnTimer++;
        if (mineSpawnTimer >= 50) {
            mineSpawnTimer = 0;
            int x = 400 + rand() % 500;
            int y = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP - 30);
            mines.push_back(Mine(Point(x, y), 20));
        }

        for (auto& mine : mines) {
            if (mine.getIsActive()) {
                mine.move();
                Point pos = mine.getPosition();

                pos.y = std::max(SAFE_ZONE_TOP, std::min(pos.y, SAFE_ZONE_BOTTOM - 30));
                mine.setPosition(pos);
                mine.draw();

                if (checkCollision(diver.getPosition(), pos, 25)) {
                    diver.setHealth(diver.getHealth() - mine.getDamage());
                    mine.triggerExplosion();
                }

                if (pos.y >= SAFE_ZONE_BOTTOM - 30) {
                    mine.triggerExplosion(); 
                }
            }
        }

        if (tookDamage) survivedWithoutDamage = false;

        mines.erase(std::remove_if(mines.begin(), mines.end(),
            [](Mine& m) { return !m.getIsActive(); }), mines.end());

        ui.drawStats(diver.getHealth(), diver.getOxygenLevel(), timeLeft, diver.getScore());
        gameManager.frame();
        delay(50);
        page = 1 - page;

    }

    if (survivedWithoutDamage && (diver.getHealth() > 0 && diver.getOxygenLevel() > 0)) {
        PlaySound(NULL, 0, 0);
        PlaySound("win.wav", NULL, SND_FILENAME | SND_ASYNC);

        setvisualpage(0);
        setactivepage(0);
        cleardevice();
        readimagefile("3.bmp", 0, 0, getmaxx(), getmaxy());

        char score[50]; 
        sprintf(score, "Final Score: %d", diver.getScore()); 
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

        delay(8000);
        getch();

    } else {
        gameManager.updateGameWithStats(diver);
    }

    gameManager.endGame();
    for (auto* c : collectibles) delete c;

    system("pause");
    closegraph();
    return 0;
}
