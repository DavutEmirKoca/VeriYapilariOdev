/**
* @file Menu.cpp
* @description  ekrana yazdırma ve kotnrol alma sınıfı
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#include "Menu.hpp"
#include <cstdlib>

Menu::Menu(){
    matrisList=new MatrisList();  
    selectedMatris=0;
    mode=0;
    matrisGroup=0;
    columnDeleteIndex=-1;
    rowDeleteIndex=-1;
    errorMessage="";
}

void Menu::run(){
    controls();
}

void Menu::orderMatrisList(){
    Matris* selectedMatrisAddress=matrisList->getMatrisAddress(selectedMatris);
    matrisList->arithmeticOrder();
    if(selectedMatrisAddress!=NULL){
        int newMatrisIndex=matrisList->getMatrisIndex(selectedMatrisAddress);
        if(newMatrisIndex!=-1){
            selectedMatris=newMatrisIndex;
            matrisGroup=(selectedMatris/5)*5;
        }
    }
}

void Menu::screenRefresh(){
    screen="";
    Matris* selectedMatrisAddress=matrisList->getMatrisAddress(selectedMatris);
    int lastScreenRow=45;
    if(selectedMatrisAddress!=NULL){
        int endRow=2+((selectedMatris-matrisGroup)*8)+selectedMatrisAddress->row;
        if(rowDeleteIndex!=-1||columnDeleteIndex!=-1) endRow+=2;
        if(endRow>lastScreenRow) lastScreenRow=endRow;
    }
    for(int i=0;i<=lastScreenRow;i++){
        if(i==lastScreenRow){
            screen+=panels(43)+"\n";
            continue;
        }
        if(i>=2&&i<=8){
            Matris* currentMatris=matrisList->getMatrisAddress(matrisGroup);
            if(currentMatris!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup,i-2);
            else
                screen+=string(21,' ');
            if(currentMatris!=NULL&&matrisGroup==selectedMatris) screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=10&&i<=16){
            Matris* currentMatris=matrisList->getMatrisAddress(matrisGroup+1);
            if(currentMatris!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+1,i-10);
            else
                screen+=string(21,' ');
            if(currentMatris!=NULL&&matrisGroup+1==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=18&&i<=24){
            Matris* currentMatris=matrisList->getMatrisAddress(matrisGroup+2);
            if(currentMatris!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+2,i-18);
            else
                screen+=string(21,' ');
            if(currentMatris!=NULL&&matrisGroup+2==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=26&&i<=32){
            Matris* currentMatris=matrisList->getMatrisAddress(matrisGroup+3);
            if(currentMatris!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+3,i-26);
            else
                screen+=string(21,' ');
            if(currentMatris!=NULL&&matrisGroup+3==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=34&&i<=40){
            Matris* currentMatris=matrisList->getMatrisAddress(matrisGroup+4);
            if(currentMatris!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+4,i-34);
            else
                screen+=string(21,' ');
            if(currentMatris!=NULL&&matrisGroup+4==selectedMatris) screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        //matris node aralıkları
        else if(i>=41||((i%8==1)&&i>2)){
            screen+=string(29,' ');
        }
        
        if(selectedMatrisAddress!=NULL&&i>=2&&selectedMatris==0+matrisGroup){
            screen+=selectedMatrisAddress->getLine(i-2,columnDeleteIndex,rowDeleteIndex);
        }
        else if(selectedMatrisAddress!=NULL&&i>=10&&selectedMatris==1+matrisGroup){
            screen+=selectedMatrisAddress->getLine(i-10,columnDeleteIndex,rowDeleteIndex);
        }
        else if(selectedMatrisAddress!=NULL&&i>=18&&selectedMatris==2+matrisGroup){
            screen+=selectedMatrisAddress->getLine(i-18,columnDeleteIndex,rowDeleteIndex);
        }
        else if(selectedMatrisAddress!=NULL&&i>=26&&selectedMatris==3+matrisGroup){
            screen+=selectedMatrisAddress->getLine(i-26,columnDeleteIndex,rowDeleteIndex);
        }
        else if(selectedMatrisAddress!=NULL&&i>=34&&selectedMatris==4+matrisGroup){
            screen+=selectedMatrisAddress->getLine(i-34,columnDeleteIndex,rowDeleteIndex);
        }
        
        else if(i>=2)
            screen+=string(33,' ');

        if(i<7){
            screen+=panels(i);
        }   
        screen+="\n";
    }
    if(errorMessage!=""){
        screen+=errorMessage+"\n";
        errorMessage="";
    }
    if(mode==4) screen+="Degistirilecek satir ve sutun giriniz: ";
}

void Menu::printScreen(){
    orderMatrisList();
    screenRefresh();
    system("cls");
    cout<<screen;
}

string Menu::panels(int row){
    string subScreen="";
    switch(row){
        case 0:
            subScreen+="--------------------------------------------------"+string(12,' ');
            switch(mode){ 
                case 0: 
                    subScreen+="|---- Dugum gezilimi aktif ------------------|";
                    break;
                case 1:
                    subScreen+="|---- Dugum islemleri aktif -----------------|";
                    break;
                case 2:
                    subScreen+="|---- Satir silme aktif ---------------------|";
                    break;
                case 3:
                    subScreen+="|---- Sutun silme aktif ---------------------|";
                    break;
                case 4:
                    subScreen+="|---- Satir sutun degistirme aktif ----------|";
                    break;
            }
            break;
        case 1:
            switch(mode){
                case 2:
                case 0:
                    subScreen+=string(62,' ')+"|    w/s tuslari ile gezebilirsiniz          |";
                    break;
                case 1:
                    subScreen+=string(62,' ')+"|    1 tusu ile satir silin                  |";
                    break;
                case 3:
                    subScreen+=string(62,' ')+"|    a/d tuslari ile gezebilirsiniz          |";
                    break;
                case 4:
                    subScreen+=string(62,' ')+"|    satir sutun (orn: 1 2) giriniz          |";
                    break;
            }
            break;
        case 2:
            switch(mode){
                case 0:  
                    subScreen+="|    q tusu ile one dugum ekle               |";
                    break;
                case 1:  
                    subScreen+="|    2 tusu ile sutun silin                  |";
                    break;
                case 2:  
                    subScreen+="|    d tusu ile secili satiri silin          |";
                    break;
                case 3:  
                    subScreen+="|    f tusu ile secili sutunu silin          |";
                    break;
                case 4:
                    subScreen+="|    x tusu ile dugum gezimine gidin         |";
                    break;
            }
            break;
        case 3:
            switch(mode){
                case 0:
                    subScreen+="|    e tusu ile arkaya dugum ekle            |";
                    break;
                case 1:
                case 2:
                case 3:
                    subScreen+="|    x tusu ile dugum gezimine gidin         |";
                    break;
                case 4:
                    subScreen+="|--------------------------------------------|";
                    break;
            }
            break;
        case 4:
            switch(mode){
                case 0: 
                    subScreen+="|    f tusu ile dugum secilebilir            |";
                    break;
                case 1:
                    subScreen+="|    3 tusu ile satir sutun degistirilebilir |";
                    break; 
                case 2:
                case 3:
                    subScreen+="|--------------------------------------------|";
                    break;
            }
            break;
        case 5:
            switch(mode){
                case 1:
                    subScreen+="|--------------------------------------------|";
                    break;
                case 0:
                    subScreen+="|    x tusu ile programdan cikilabilir       |";
                    break;
            }
            break;
        case 6:
            switch(mode){
                case 0:
                    subScreen+="|--------------------------------------------|";
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

void Menu::controls(){
    char control=0;
    bool exit=0;
    do{
        int row=0;
        int col=0;
        screenRefresh();
        system("cls");
        cout<<screen;
        if(mode!=4){
            cin>>control;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                continue;
            }
        }
        else{
            cin>>row>>col;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                orderMatrisList();
                mode=0;
                continue;
            }
        }
        Matris* currentMatris=matrisList->getMatrisAddress(selectedMatris);
        switch(mode){
            case 0:
                switch(control){
                    case 'w':
                        if(matrisList->getMatrisAddress(selectedMatris-1)!=NULL){
                        selectedMatris--;
                        matrisGroup=(selectedMatris/5)*5;
                        }
                        break;
                    case 's':
                        if(matrisList->getMatrisAddress(selectedMatris+1)!=NULL){
                            selectedMatris++;
                            matrisGroup=(selectedMatris/5)*5;
                        }
                        break;
                    case 'q':
                        matrisList->insertMatrisPrev(currentMatris);
                        break;
                    case 'e':
                        matrisList->insertMatrisNext(currentMatris);
                        break;
                    case 'f':
                        if(currentMatris!=NULL){
                            mode=1;
                        }
                        break;
                    case 'x':
                        exit=1;
                        break;
                }
                break;
            case 1:
                if(currentMatris==NULL){
                    mode=0;
                    break;
                }
                switch(control){
                    case '1':
                        mode=2;
                        rowDeleteIndex=0;
                        break;
                    case '2':
                        columnDeleteIndex=0;
                        mode=3;
                        break;
                    case '3':
                        if(currentMatris->row!=currentMatris->column){
                            errorMessage="Hata: Kare matris olmadigi icin satir ve sutun degistirilemez.";
                            orderMatrisList();
                            mode=0;
                        }
                        else{
                            mode=4;
                        }
                        break;
                    case 'x':
                        orderMatrisList();
                        mode=0;
                        break;
                }
                break;
            case 2:
                if(currentMatris==NULL){
                    rowDeleteIndex=-1;
                    mode=0;
                    break;
                }
                switch(control){
                    case 'w':
                        if(rowDeleteIndex>0)
                        rowDeleteIndex--;
                        break;
                    case 's':
                        if(currentMatris->row-1>rowDeleteIndex)
                        rowDeleteIndex++;
                        break;
                    case 'd':
                        currentMatris->deleteRow(rowDeleteIndex);
                        if(currentMatris->row==0){
                            matrisList->deleteMatris(selectedMatris);
                            if(matrisList->getMatrisAddress(selectedMatris)==NULL&&selectedMatris>0){
                                selectedMatris--;
                            }
                            matrisGroup=(selectedMatris/5)*5;
                            rowDeleteIndex=-1;
                            orderMatrisList();
                            mode=0;
                        }
                        else if(rowDeleteIndex>currentMatris->row-1){
                            rowDeleteIndex=currentMatris->row-1;
                        }
                        break;
                    case 'x':
                        mode=0;
                        orderMatrisList();
                        rowDeleteIndex=-1;
                        break;
                }
                break;
            case 3:
                if(currentMatris==NULL){
                    columnDeleteIndex=-1;
                    mode=0;
                    break;
                }
                switch(control){
                    case 'a':
                        if(columnDeleteIndex>0)
                        columnDeleteIndex--;
                        break;
                    case 'd':
                        if(currentMatris->column-1>columnDeleteIndex)
                        columnDeleteIndex++;
                        break;
                    case 'f':
                        currentMatris->deleteColumn(columnDeleteIndex);
                        if(currentMatris->column==0){
                            matrisList->deleteMatris(selectedMatris);
                            if(matrisList->getMatrisAddress(selectedMatris)==NULL&&selectedMatris>0){
                                selectedMatris--;
                            }
                            matrisGroup=(selectedMatris/5)*5;
                            columnDeleteIndex=-1;
                            orderMatrisList();
                            mode=0;
                        }
                        else if(columnDeleteIndex>currentMatris->column-1){
                            columnDeleteIndex=currentMatris->column-1;
                        }
                        break;
                    case 'x':
                        mode=0;
                        columnDeleteIndex=-1;
                        orderMatrisList();
                        break;
                }
                break;
            case 4:
                if(currentMatris!=NULL){
                    currentMatris->switchRowColumn(row-1,col-1);
                    mode=1;
                }
                else{
                    mode=0;
                }
                break;
        }
    }while(!exit);
}

Menu::~Menu(){
    delete matrisList;
}