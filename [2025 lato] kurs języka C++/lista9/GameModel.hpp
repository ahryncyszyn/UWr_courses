#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

class GameModel
{
    vector<vector<int>> board;
    int pawns_count;
    std::chrono::steady_clock::time_point start_time;

public:
    GameModel();
    bool is_index_valid(int index);
    bool is_command_valid(string move);
    bool is_move_valid(int from_row, int from_col, int to_row, int to_col);
    void make_move(string move);

    bool is_game_over();
    bool is_game_won();
    int get_elapsed_time();

    vector<vector<int>>& get_board();
    int get_pawns_count();
};