#include <iostream>
#include "minesweeper.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

int main()
{
    MinesweeperBoard board(10,10,EASY);
    MSBoardTextView view{board};

    MSTextController ctrl ( board, view );

    ctrl.play();

    return 0;
}
