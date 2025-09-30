#pragma once
#include "GameModel.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <vector>
using namespace std;

class GameView
{
    GameModel& model;
    
public:
    GameView(GameModel& model);
    void display_instroduction();
    void display_board(vector<vector<int>>& board);
    void show_message(string message);
    void display_game_over(int is_game_won);
    string prompt_move();
};