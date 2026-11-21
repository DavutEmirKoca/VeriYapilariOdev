#include "Menu.h"

Menu::Menu(){
    matrisList=new MatrisList();  
    selectedMatris=0;
    mode=0;
    matrisGroup=0;
    columnDeleteIndex=-1;
    rowDeleteIndex=-1;
    controls();
}

void Menu::screenRefresh(){
    screen="";
    for(int i=0;i<44;i++){     
        if(i>=2&&i<=8){
            if(matrisList->getMatrisAddress(matrisGroup)!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup,i-2);
            else
                screen+=string(21,' ');
            if(matrisGroup==selectedMatris) screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=10&&i<=16){
            if(matrisList->getMatrisAddress(matrisGroup+1)!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+1,i-10);
            else
                screen+=string(21,' ');
            if(matrisGroup+1==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=18&&i<=24){
            if(matrisList->getMatrisAddress(matrisGroup+2)!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+2,i-18);
            else
                screen+=string(21,' ');
            if(matrisGroup+2==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=26&&i<=32){
            if(matrisList->getMatrisAddress(matrisGroup+3)!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+3,i-26);
            else
                screen+=string(21,' ');
            if(matrisGroup+3==selectedMatris) 
                screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i>=34&&i<=40){
            if(matrisList->getMatrisAddress(matrisGroup+4)!=NULL)
                screen+=matrisList->getMatrisRow(matrisGroup+4,i-34);
            else
                screen+=string(21,' ');
            if(matrisGroup+4==selectedMatris) screen+="<-"+string(6,' ');
            else
                screen+=string(8,' ');
        }
        else if(i==43){
            screen+=panels(i);
        }
        //matris node aralıkları
        else if(i==41||i==42||((i%8==1))&&i>2){
            screen+=string(29,' ');
        }
        
        if(i>=2&&selectedMatris==0+matrisGroup){
            screen+=matrisList->getMatrisAddress(0+matrisGroup)->getLine(i-2,columnDeleteIndex,rowDeleteIndex);
        }
        else if(i>=10&&selectedMatris==1+matrisGroup){
            screen+=matrisList->getMatrisAddress(1+matrisGroup)->getLine(i-10,columnDeleteIndex,rowDeleteIndex);
        }
        else if(i>=18&&selectedMatris==2+matrisGroup){
            screen+=matrisList->getMatrisAddress(2+matrisGroup)->getLine(i-18,columnDeleteIndex,rowDeleteIndex);
        }
        else if(i>=26&&selectedMatris==3+matrisGroup){
            screen+=matrisList->getMatrisAddress(3+matrisGroup)->getLine(i-26,columnDeleteIndex,rowDeleteIndex);
        }
        else if(i>=34&&selectedMatris==4+matrisGroup){
            screen+=matrisList->getMatrisAddress(4+matrisGroup)->getLine(i-34,columnDeleteIndex,rowDeleteIndex);
        }
        
        else if(i>=2)
            screen+=string(33,' ');

        if(i<6){
            screen+=panels(i);
        }   
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

void Menu::controls(){
    char control;
    do{
        screenRefresh();
        cout<<screen;
        cin>>control;
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
                        matrisList->insertMatrisPrev(matrisList->getMatrisAddress(selectedMatris));
                        break;
                    case 'e':
                        matrisList->insertMatrisNext(matrisList->getMatrisAddress(selectedMatris));
                        break;
                    case 'f':
                        mode=1;
                        break;
                }
                break;
            case 1:
                switch(control){
                    case '1':
                        mode=2;
                        break;
                    case '2':
                        mode=3;
                        break;
                    case 'x':
                        mode=0;
                        break;
                }
                break;
            case 2:
                switch(control){
                    case 'w':
                        rowDeleteIndex--;
                        break;
                    case 's':
                        rowDeleteIndex++;
                        break;
                    case 'd':

                        break;
                    case 'x':
                        mode=0;
                        break;
                }
                break;
            case 3:
                
                break;
        }
    }while(control!='u');
}

Menu::~Menu(){
    delete matrisList;
}