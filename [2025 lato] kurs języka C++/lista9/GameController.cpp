#include "GameController.hpp"

GameController::GameController(GameModel& model, GameView& view)
: model(model), view(view) {}

void GameController::run()
{
    view.display_instroduction();

    while (true)
    {
        view.display_board(model.get_board());

        string move = view.prompt_move();
        
        try 
        {
            model.make_move(move);
        } catch (const exception& e)
        {
            view.show_message(e.what());
        }

        if (model.is_game_over())
        {
            if (model.is_game_won()) view.display_game_over(1);
            else view.display_game_over(0);
            break;
        }
    }
}