#include "Menu.h"

Menu::Menu(){
    matrisList=new MatrisList();  
}

void Menu::screenRefresh(){
    screen="";
    for(int i=0;i<44;i++){
        //screen+=matrisList->getMatrisRow(rowToMatrisIndex(i),);
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
            subScreen+="--------------------------------------------------"+whiteSpace(12);
            if(mode==0) subScreen+="|---- Dugum gezilimi aktif -----------|";
            break;
        case 1:
            if(mode==0)subScreen+=whiteSpace(62)+"|    w/s tuslari ile gezebilirsiniz   |";
            break;
        case 2:
            if(mode==0) subScreen+="|    q tusu ile one dugum ekle        |";
            break;
        case 3:
            if(mode==0) subScreen+="|    e tusu ile arkaya dugum ekle     |";
            break;
        case 4:
            if(mode==0) subScreen+="|    f tusu ile dugum secilebilir     |";
            break;
        case 5:if(mode==0) subScreen+="|-------------------------------------|";
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
}

string Menu::whiteSpace(int amount){
    string whiteSpace="";
    for(int i=0;i<amount;i++) whiteSpace+=" ";
    return whiteSpace;
}