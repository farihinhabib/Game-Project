#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
#include "Diver.hpp"
#include <chrono>

class GameManager {
private:
    bool isRunning;
    int frameCount;

    Diver diver;
    std::chrono::steady_clock::time_point startTime;
    const int TIME_LIMIT = 60;

public:
    GameManager();

    void showMenu();
    void frame();
    void endGame();
    bool getIsRunning() const;
    void updateGameWithStats(const Diver& diverRef);
};

#endif
