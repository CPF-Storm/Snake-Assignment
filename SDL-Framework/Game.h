#pragma once

#include <random>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "player.h"
#include "Graphics.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height, int mode);
    

    int GetScore() const;
    int GetSize() const;

private:
    Snake snake;
    SDL_Point food;
    std::unique_ptr<Player> player;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{ 0 };

    void PlaceFood();
    void Update();
    void SetPlayer();
};