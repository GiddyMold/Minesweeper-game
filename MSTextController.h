#ifndef SOLUTIONS_MSTEXTCONTROLLER_H
#define SOLUTIONS_MSTEXTCONTROLLER_H
#include "MSBoardTextView.h"
#include "minesweeper.h"

class MinesweeperBoard;
class MSBoardTextView;

class MSTextController {
    MinesweeperBoard & board;
    MSBoardTextView & view;

public:
    MSTextController(MinesweeperBoard & bboard, MSBoardTextView & vview);
    void play();
};

#endif
