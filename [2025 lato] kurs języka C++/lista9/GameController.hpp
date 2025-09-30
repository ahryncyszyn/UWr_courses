#pragma once
#include <exception>
#include "GameModel.hpp"
#include "GameView.hpp"

class GameController
{
    GameModel& model;
    GameView& view;

public:
    GameController(GameModel& model, GameView& view);
    void run();
};