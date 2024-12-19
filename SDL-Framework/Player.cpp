#include "player.h"

Player::Player(const Snake* snake, const SDL_Point* food) : _snake(snake), _food(food) {
    
};

Player::~Player() {
    
}

void Player::play()
{
    // get the location of the head of snake
    int cur_x = static_cast<int>(_snake->head_x);
    int cur_y = static_cast<int>(_snake->head_y);

    if (cur_x != _food->x && cur_y != _food->y) return;  
    if (cur_x == _food->x && cur_y == _food->y) return; 

    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;

    if (cur_x == _food->x)
    {
        if (cur_y > _food->y) sdlevent.key.keysym.sym = SDLK_UP;
        else sdlevent.key.keysym.sym = SDLK_DOWN;
    }
    else 
    {
        if (cur_x > _food->x) sdlevent.key.keysym.sym = SDLK_LEFT;
        else sdlevent.key.keysym.sym = SDLK_RIGHT;
    }

    SDL_PushEvent(&sdlevent);
}