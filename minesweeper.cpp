#include <iostream>
#include <time.h>
#include "minesweeper.h"
using std::cout;
using std::endl;

MinesweeperBoard::MinesweeperBoard(unsigned int width,unsigned int height,GameMode mode)
{
    srand(time(NULL));
    this->first_action=true;
    this->state = GameState::RUNNING;
    this->width = width;
    this->height = height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            board[i][j].hasFlag = 0;
            board[i][j].hasMine = 0;
            board[i][j].isRevealed = 0;
        }
    }
    if (mode == DEBUG)
    {
        for (int j=0;j<width; j++)
        {
            for (int i=0; i<height; i++)
            {
                if (i == j)
                    board[i][j].hasMine = 1;
                if (i == 0)
                    board[j][i].hasMine = 1;
                if (j == 0 && i%2 == 0)
                    board[j][i].hasMine = 1;
            }
        }
    }
    if (mode != DEBUG)
    {
        mine_count = (width * height * mode)/100;
        int mine_countt=mine_count;
        while (mine_countt > 0)
        {
            int x = rand() % getBoardWidth();
            int y = rand() % getBoardHeight();
            if (this->board[x][y].hasMine == 0)
            {
                this->board[x][y].hasMine = 1;
                mine_countt--;
            }
        }
    }
}

void MinesweeperBoard::debug_display() const
{
    cout<<"W: "<<this->width<<" H: "<<this->height<<endl;
    for(int i=0; i<getBoardHeight(); i++)
    {
        for(int j=0; j<getBoardWidth(); j++)
        {
            cout<<"[";
            if(board[j][i].hasMine==1) cout<<"M";
            else cout<<".";
            if(board[j][i].isRevealed==1) cout<<"o";
            else cout<<".";
            if(board[j][i].hasFlag==1) cout<<"F";
            else cout<<".";
            cout<<"]";
        }
        cout<<endl;
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    return MinesweeperBoard::mine_count;
}

int MinesweeperBoard::countMines(int x, int y) const
{
    int amount=0;
    if (MinesweeperBoard::board[x][y].isRevealed==0)
        return -1;
    if(x>getBoardWidth() || y>getBoardHeight())
        return -1;
    else
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                if (MinesweeperBoard::board[x+i-1][y+j-1].hasMine==1 && (y+j-1)>=0 && (x+i-1)>=0)
                    amount++;
            }
        }
    return amount;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if(board[x][y].hasFlag==1)
        return true;
    else if(y > getBoardHeight() || x > getBoardWidth())
        return false;
    else if(board[x][y].hasFlag==0)
        return false;
    else if(board[x][y].isRevealed==1)
        return false;
    else
        return false;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{
    if (x > getBoardWidth() || y > getBoardHeight())
        return;
    if (board[x][y].isRevealed==1)
        return;
    if (state == (FINISHED_WIN || FINISHED_LOSS) )
        return;
    if (hasFlag(x,y) == true)
        MinesweeperBoard::board[x][y].hasFlag = false;
    else if (hasFlag(x,y) == false)
        MinesweeperBoard::board[x][y].hasFlag = true;
}

void MinesweeperBoard::revealField(int x, int y)
{
    if (board[x][y].isRevealed==1)
        return;
    if (x > getBoardWidth() || y > getBoardHeight())
        return;
    if (state == (FINISHED_WIN || FINISHED_LOSS) )
        return;
    if (board[x][y].hasFlag==1)
        return;
    if(board[x][y].isRevealed==0 && board[x][y].hasMine==0)
    {
        board[x][y].isRevealed=1;
        first_action = false;
    }
    if(board[x][y].isRevealed==0 && board[x][y].hasMine==1)
    {
        if(first_action==false)
        {
            board[x][y].isRevealed=1;
            state = FINISHED_LOSS;
        }
        if(first_action==true)
        {
            first_action = false;
            board[rand() % getBoardWidth()][rand() % getBoardHeight()].hasMine = true;
            board[x][y].isRevealed = true;
            board[x][y].hasMine = false;
        }
    }
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if(board[x][y].isRevealed==true)
        return true;
    else
        return false;
}

GameState MinesweeperBoard::getGameState() const
{
    if(state==FINISHED_LOSS)
    {
        return FINISHED_LOSS;
    }

    int mines=getMineCount();
    int unrevealed=0;
    for(int i=0; i<getBoardHeight(); i++)
    {
        for(int j=0; j<getBoardWidth(); j++)
        {
            if(board[i][j].hasMine==1 && board[i][j].isRevealed==1)
                return FINISHED_LOSS;
            if(board[i][j].hasMine==1 && board[i][j].isRevealed==0)
                mines--;
            if(board[i][j].isRevealed==0)
                unrevealed++;
        }
    }
    if(unrevealed==getMineCount() && mines==0)
        return FINISHED_WIN;
    return RUNNING;
}

char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if(x>getBoardWidth() || y>getBoardHeight())
        return '#';
    if(board[x][y].isRevealed==0 && board[x][y].hasFlag==1)
        return 'F';
    if(board[x][y].isRevealed==0 && board[x][y].hasFlag==0)
        return '_';
    if(board[x][y].isRevealed==1 && board[x][y].hasMine==1)
        return 'x';
    if(board[x][y].isRevealed==1 && countMines(x,y)==0)
        return ' ';
    if(board[x][y].isRevealed==1 && countMines(x,y)>0)
        return countMines(x,y)+'0';
    else
        return '.';
}