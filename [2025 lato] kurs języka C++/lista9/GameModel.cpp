#include "GameModel.hpp"
#include "Exceptions.hpp"
using namespace std;

GameModel::GameModel() : 
    board(7, vector<int>(7, 1)), 
    pawns_count(32), 
    start_time(std::chrono::steady_clock::now())
{
    int indexes[4] = {0, 1, 5, 6};
    for (int i : indexes)
    {
        for (int j : indexes)
        {
            board[i][j] = -1;
        }
    }
    board[3][3] = 0;
};

vector<vector<int>>& GameModel::get_board()
{
    return board;
};

bool GameModel::is_command_valid(string move)
{
    if (move.size() != 3)
    {
        throw niepoprawna_komenda("ruch powinen się składać z trzech znakow");
    }
    if (!isalpha(move[0]))
    {
        throw niepoprawna_komenda("kolumna powinna byc podana jako litera w zakresie A-G");
    }
    if (!isdigit(move[1]))
    {
        throw niepoprawna_komenda("rzad powinien byc podany jako liczba w zakresie 1-7");
    }
    return true;
}

bool GameModel::is_index_valid(int index)
{
    return (0 <= index && index <= 6);
}

bool GameModel::is_move_valid(int from_row, int from_col, int to_row, int to_col)
{   
    if (!(is_index_valid(from_row)) || !(is_index_valid(from_col))
        || !(is_index_valid(to_row)) || !(is_index_valid(to_col)))
    {
        throw nieprawidlowy_ruch("podane wspolrzedne wykraczaja poza plansze!");
    }
    if (board[from_row][from_col] != 1)
    {
        throw nieprawidlowy_ruch("na podanym polu nie ma pionka!");
    }
    if (board[to_row][to_col] != 0)
    {
        throw nieprawidlowy_ruch("dane pole jest niedostepne!");
    }
    int jumped_row = (from_row + to_row) / 2;
    int jumped_col = (from_col + to_col) / 2;
    if (board[jumped_row][jumped_col] != 1)
    {
        throw nieprawidlowy_ruch("dany ruch nie przeskakuje zadnego pionka!");
    }
    return true;
};

void GameModel::make_move(string move)
{
    is_command_valid(move);
    for(auto& c : move) c = tolower(c);
    int from_col = move[0] - 'a';
    int from_row = move[1] - '1';
    int to_col = from_col;
    int to_row = from_row;
    switch (move[2])
    {
        case 'r': to_col += 2; break;
        case 'l': to_col -= 2; break;
        case 'u': to_row -= 2; break;
        case 'd': to_row += 2; break;
        default: throw niepoprawna_komenda("kierunek powinien byc podany jako litera u/d/l/r");
    }

    is_move_valid(from_row, from_col, to_row, to_col);

    board[from_row][from_col] = 0;
    board[to_row][to_col] = 1;
    switch (move[2])
    {
        case 'r': board[from_row][from_col + 1] = 0; break;
        case 'l': board[from_row][from_col - 1] = 0; break;
        case 'u': board[from_row - 1][from_col] = 0; break;
        case 'd': board[from_row + 1][from_col] = 0; break;
    }
    pawns_count--;
}

bool GameModel::is_game_over()
{
    int moves[4][2] = 
    {
        {-2, 0}, {2, 0}, 
        {0, -2}, {0, 2}  
    };
    for (int row = 0; row < 7; row++) 
    {
        for (int col = 0; col < 7; col++) 
        {
            if (board[row][col] != 1) continue;

            for (auto& dir : moves) {
                int to_row = row + dir[0];
                int to_col = col + dir[1];

                if (!is_index_valid(to_row) || !is_index_valid(to_col)) continue;

                try 
                {
                    if (is_move_valid(row, col, to_row, to_col)) return false; 
                } catch (...) {}
            }
        }
    }
    return true;
}

bool GameModel::is_game_won()
{
    return pawns_count == 1 && board[3][3] == 1;
}

int GameModel::get_elapsed_time()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
    return static_cast<int>(duration.count());
}

int GameModel::get_pawns_count()
{
    return pawns_count;
}