#include "game.h"



Game::Game(std::size_t grid_width, std::size_t grid_height, int mode)
    : snake(grid_width, grid_height),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width) - 1),
    random_h(0, static_cast<int>(grid_height) - 1) {
    if (mode == 2) SetPlayer();
    PlaceFood();
}

void Game::SetPlayer() {
    player.reset(new Player(&snake, &food));
}


void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::Update() {
    if (!snake.alive) return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        
        snake.GrowBody();
        snake.speed += 0.02;
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }