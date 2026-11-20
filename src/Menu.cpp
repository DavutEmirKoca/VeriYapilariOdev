#include "Menu.h"

Menu::Menu(){
    matrisList=new MatrisList();  
    matrisGroup=0;
    columnDeleteIndex=-1;
    rowDeleteIndex=-1;
}

void Menu::screenRefresh(){
    screen="";
    for(int i=0;i<44;i++){
        screen+=matrisList->getMatrisRow(rowToMatrisIndex(i),rowToMatrisRow(i));
        //sorunlu satır
        if(rowToMatrisIndex(i)<0){
            screen+=string(20,' ');
        }else{
            //screen+=matrisList->getMatrisAddress(rowToMatrisIndex(i))->getLine(i,columnDeleteIndex,rowDeleteIndex);
        }
        screen+=panels(i);
        screen+="\n";
    }
}

void Menu::printScreen(){
    matrisList->arithmeticOrder();
    screenRefresh();
    cout<<screen;
}

string Menu::panels(int row){
    string subScreen="";
    switch(row){
        case 0:
            subScreen+="--------------------------------------------------"+string(12,' ');
            switch(mode){ 
                case 0: 
                    subScreen+="|---- Dugum gezilimi aktif -----------|";
                    break;
                case 1:
                    subScreen+="|---- Dugum islemleri aktif ----------|";
                    break;
                case 2:
                    subScreen+="|---- Satir silme aktif --------------|";
                    break;
                case 3:
                    subScreen+="|---- Sutun silme aktif --------------|";
                    break;
            }
            break;
        case 1:
            switch(mode){
                case 2:
                case 0:
                    subScreen+=string(62,' ')+"|    w/s tuslari ile gezebilirsiniz   |";
                    break;
                case 1:
                    subScreen+=string(62,' ')+"|    1 tusu ile satir silin           |";
                    break;
                case 3:
                    subScreen+=string(62,' ')+"|    a/d tuslari ile gezebilirsiniz   |";
                    break;
            }
            break;
        case 2:
            switch(mode){
                case 0:  
                    subScreen+="|    q tusu ile one dugum ekle        |";
                    break;
                case 1:  
                    subScreen+="|    2 tusu ile sutun silin           |";
                    break;
                case 2:  
                    subScreen+="|    d tusu ile secili satiri silin   |";
                    break;
                case 3:  
                    subScreen+="|    f tusu ile secili sutunu silin   |";
                    break;
            }
            break;
        case 3:
            switch(mode){
                case 0:
                    subScreen+="|    e tusu ile arkaya dugum ekle     |";
                    break;
                case 1:
                case 2:
                case 3:
                    subScreen+="|    x tusu ile dugum gezimine gidin  |";
                    break;
            }
            break;
        case 4:
            switch(mode){
                case 0: 
                    subScreen+="|    f tusu ile dugum secilebilir     |";
                    break;
                case 1: 
                case 2:
                case 3:
                    subScreen+="|-------------------------------------|";
                    break;
            }
            break;
        case 5:
            switch(mode){
                case 0:
                    subScreen+="|-------------------------------------|";
                    break;
            }
            break;
        case 43:
            subScreen+="--------------------------------------------------";
            break;
        default:
            subScreen="";
    }
    return subScreen;
}

int Menu::rowToMatrisIndex(int i){
    if(i<2||i%8==1||i>42) return -1;
    if(i>=2&&i<=8) return 0+matrisGroup;
    if(i>=10&&i<=16) return 1+matrisGroup;
    if(i>=18&&i<=24) return 2+matrisGroup;
    if(i>=26&&i<=34) return 3+matrisGroup;
    if(i>=36&&i<=42) return 4+matrisGroup;
    return -1;
}

int Menu::rowToMatrisRow(int row){
    if(row<2||row%8==1||row>42) return -1;
    if(row>=2&&row<=8) return row-2;
    if(row>=10&&row<=16) return row-10;
    if(row>=18&&row<=24) return row-18;
    if(row>=26&&row<=34) return row-26;
    if(row>=36&&row<=42) return row-34;
    return -1;
}

