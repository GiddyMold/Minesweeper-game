#ifndef SOLUTIONS_MINESWEEPER_H
#define SOLUTIONS_MINESWEEPER_H

#include <iostream>
#include "field.h"

enum GameMode  { DEBUG, EASY=10, NORMAL=20, HARD=30 };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };


class MinesweeperBoard
{
    Field board[100][100];
    int width;
    int height;
    int mine_count;
    bool first_action;
    GameState state;
public:
    MinesweeperBoard(unsigned int width=10,unsigned int height=10,GameMode mode=DEBUG);
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;
};

#endif