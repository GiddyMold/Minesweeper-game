#include "MSTextController.h"
#include "MSBoardTextView.h"

MSTextController::MSTextController(MinesweeperBoard & bboard, MSBoardTextView & vview) : board(bboard), view(vview){}

void MSTextController::play()
{
    view.main();
}