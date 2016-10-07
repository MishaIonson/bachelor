#include <iostream>
#include <conio.h>

#include "SerialClass.h"

Serial* SP;

using namespace std;

int main()
{
    char* buffer;
    char command;
    SP = new Serial("\\\\.\\COM8");
    if (SP->IsConnected())
        printf("Connected\n");
    buffer="u";
    SP->WriteData(buffer, 1);
    Sleep(500);

    while(true){
            puts("Press!");
            Sleep(500);
            if(kbhit()){
                command = getch();
                if(command == 'q'){
                    buffer="i";
                    SP->WriteData(buffer, 1);
                    Sleep(500);
                }
                else if(command == 'w'){
                    buffer="o";
                    SP->WriteData(buffer, 1);
                    Sleep(500);
                }
                else if(command == 'r')
                    break;

               /* buffer = "u";
                SP->WriteData(buffer, 1);
                Sleep(500);*/
            }
    }
    buffer="p";
    SP->WriteData(buffer, 1);
    Sleep(500);
    return 0;
}
