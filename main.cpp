#include <iostream>
#include "GameWindow.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

    std::cout<<"\n\n\t\t\t\t\t  ~~ WELCOME TO CONSOLE CHESS GAME ~~\n\n\n"<<std::endl;
    std::cout<<"Instructions:\n"<<std::endl;


    std::cout<<"Player (Multiplayer) should type the coordinates of the pieces and the position desired...\n"<<std::endl;
    std::cout<<"FYI: Knight piece is represented as 'H'\n"<<std::endl;
    std::cout<<"\t\t\t\t\t\tby Yusuf Erman ERGOZ\n"<<std::endl;
    ofstream chss;
    chss.open ("who_won.txt");
    chss << "Welcome to console chess game!\t\t\t\t\t\t\tWritten by Yusuf Erman ERGÖZ\nThe results will be saved here:\n";
    chss.close();

    system("pause");

    system("cls");

    GameWindow window;
    return 0;
}
