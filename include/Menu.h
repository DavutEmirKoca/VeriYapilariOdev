#ifndef MENU_H
#define MENU_H
#include "MatrisList.h"

class Menu{
    private:
        MatrisList* matrisList;
        // 0 dugum gezilimi, 1 dugum islemleri, 2 satir silme, 3 sütun silme
        int mode;
        string screen;
        //creates the screen with current values
        void screenRefresh();
        //the indexOfSelectedMatris
        int selectedMatris;
        // for 0-4. matrises -> 0, for 5-9 matrises -> 5 and so on
        int matrisGroup;
        //the right menu
        string panels(int row);
        int rowToMatrisIndex(int i);
        int rowToMatrisRow(int row);
        //
        int columnDeleteIndex;
        int rowDeleteIndex;
        
    public:
        Menu();
        void printScreen();
    
};

#endif