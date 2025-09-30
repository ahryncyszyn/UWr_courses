#include "GameView.hpp"

GameView::GameView(GameModel& model) : model(model) {};

void GameView::display_instroduction()
{
    cout << "Witamy w grze \"Samotnik\"!" << endl;
}

void GameView::display_board(vector<vector<int>>& board)
{
    cout << "\n\n    A B C D E F G" << endl;
    cout << "    ";
    for (int i = 0 ; i < 6; i++) cout << "--"; cout << "-";
    cout << endl;
    for (int i = 1; i <= 7; i++)
    {
        cout << i << " | ";
        vector<int> row = board[i - 1];
        for (int pawn : row)
        {
            if (pawn == -1) cout << "x ";
            if (pawn == 1) cout << "o ";
            if (pawn == 0) cout << "  ";
        }
        cout << "|" << endl;
    }
    cout << "    ";
    for (int i = 0 ; i < 7; i++) cout << "--";
    cout << endl;
    cout << endl;
}

void GameView::display_game_over(int is_game_won)
{
    int game_time = model.get_elapsed_time();
    int minutes = game_time / 60;
    int seconds = game_time % 60;
    if (is_game_won) cout << "Wygrana!" << endl;
    else cout << "Przegrana!" << endl;
    cout << "Statystyki gry:" << endl;
    cout << "- czas gry: " << minutes << " min " << seconds << "sec" << endl;
    cout << "- liczba pozostałych pionkow: " << model.get_pawns_count() << endl;
};

void GameView::show_message(string message)
{
    cout << message << endl;
}

string GameView::prompt_move()
{
    cout << "Podaj swoj ruch: ";
    string move;
    cin >> move;
    return move;
}