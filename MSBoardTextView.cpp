#include "MSBoardTextView.h"
#include <stdlib.h>
using std::cout;
using std::endl;
using std::cin;

MSBoardTextView::MSBoardTextView(MinesweeperBoard & bboard) : board(bboard){}

void MSBoardTextView::display()
{
    for(int y=0; y<board.getBoardHeight(); y++)
    {
        if(y==0)
        {
            cout<<"  ";
            for(int i=0; i<board.getBoardWidth(); i++)
            {
                cout << i ;
                if(i<10)
                    cout<<"  ";
                else
                    cout<<" ";
            }
            cout<<endl;
        }
        cout<<y<<" ";
        for(int x=0; x<board.getBoardWidth(); x++)
        {
            cout<<"[";
            cout<<board.getFieldInfo(x,y);
            cout<<"]";
        }
    cout<<endl;
    }
}

void MSBoardTextView::main()
{
    int choice,x,y,exit=0;
    while(exit==0)
    {
        display();
        cout<<endl;
        cout << "***********************" << endl;
        cout << "1 - Reveal Field" << endl;
        cout << "2 - Toggle Flag" << endl;
        cout << "3 - Exit Game" << endl;
        cout << "***********************" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "x: ";
            cin >> x;
            cout << "y: ";
            cin >> y;
            board.revealField(x, y);
            gamestate();
        }
        if (choice == 2)
        {
            cout << "x: ";
            cin >> x;
            cout << "y: ";
            cin >> y;
            board.toggleFlag(x, y);
            gamestate();
        }
        if (choice == 3)
        {
            exit = 1;
        }
    }
    return;
}

void MSBoardTextView::gamestate()
{
    if(board.getGameState()==FINISHED_WIN)
    {
        cout<<"FINISHED_WIN"<<endl;
        exit(0);
    }
    if(board.getGameState()==FINISHED_LOSS)
    {
        cout<<"FINISHED_LOSS"<<endl;
        exit(0);
    }
}


