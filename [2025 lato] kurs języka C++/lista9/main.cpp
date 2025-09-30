#include "GameModel.hpp"
#include "GameView.hpp"
#include "GameController.hpp"

int main()
{
    GameModel model;
    GameView view(model);
    GameController controller(model, view);
    controller.run();
    return 0;
}