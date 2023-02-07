#ifndef SOLUTIONS_MSBOARDTEXTVIEW_H
#define SOLUTIONS_MSBOARDTEXTVIEW_H
#include "minesweeper.h"

class MSBoardTextView
{
        MinesweeperBoard & board;
    public:
        MSBoardTextView(MinesweeperBoard & bboard);
        void display();
        void gamestate();
        void main();
};

#endif
