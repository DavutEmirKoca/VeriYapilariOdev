/**
* @file MatrisList.cpp
* @description Matrisleri tutan liste ve işlemleri
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/

#include "MatrisList.hpp"

MatrisList::MatrisList(){
    fstream matrisFile;
    head=NULL;
    isFileOpened=false;
    matrisFile.open("kayitlar.txt",ios::in);
    if(matrisFile.is_open()){
        isFileOpened=true;
        string line;
        Matris* currentMatris=head;
        while(getline(matrisFile,line)){
            while(line.length()>0&&(line[0]==' '||line[0]=='\r'||line[0]=='\t')){
                line.erase(0,1);
            }
            if(line=="") continue;
            size_t end=line.find(" ");
            if(end==string::npos) continue;
            int row=stoi(line.substr(0,end));
            line.erase(0,end+1);
            while(line.length()>0&&line[0]==' '){
                line.erase(0,1);
            }
            end=line.find(" ");
            if(end==string::npos) continue;
            int column=stoi(line.substr(0,end));
            line.erase(0,end+1);
            if(row<=0||column<=0) continue;
            Matris* newMatris=new Matris();
            newMatris->matrisGenerate(row,column,line);
            if(newMatris->isEmpty()){
                delete newMatris;
                continue;
            }
            if(head==NULL){
                head=currentMatris=newMatris;
            }
            else{
                currentMatris->next=newMatris;
                currentMatris=newMatris;
            }
        }
    }
    else{
        cout<<"Document cant be opened";
    }
    matrisFile.close();
}

void MatrisList::arithmeticOrder(){
    if(head==NULL||head->next==NULL) return;
    bool isChanged;
    do{
        isChanged=false;
        Matris* currentMatris=head;
        Matris* prevMatris=head;
        while(currentMatris->next!=NULL){
            if(currentMatris->arithmeticCalculate()<currentMatris->next->arithmeticCalculate()){
                isChanged=true;
                if(currentMatris==head){
                    head=currentMatris->next;
                    currentMatris->next=head->next;
                    head->next=currentMatris;
                    prevMatris=head;
                }
                else{
                    prevMatris->next=currentMatris->next;
                    currentMatris->next=prevMatris->next->next;
                    prevMatris->next->next=currentMatris;
                    prevMatris=prevMatris->next;
                }
            }
            else{
                prevMatris=currentMatris;
                currentMatris=currentMatris->next;
            }
        }
    }while(isChanged);
}

string MatrisList::formatAddressBox(string addressText){
    string formattedAddress=addressText;
    if(formattedAddress.length()>18){
        formattedAddress=formattedAddress.substr(formattedAddress.length()-18);
    }
    int totalSpace=18-formattedAddress.length();
    int leftSpace=totalSpace/2;
    int rightSpace=totalSpace-leftSpace;
    return "*"+string(leftSpace,' ')+formattedAddress+string(rightSpace,' ')+"* ";
}

string MatrisList::getMatrisRow(int matrisNo,int rowNo){
    if(rowNo==-1) return "";
    if(matrisNo==-1) return string(21,' ');
    Matris* matrisAddress=getMatrisAddress(matrisNo);
    if(matrisAddress==NULL) return string(21,' ');
    stringstream ss;
    switch(rowNo){
        case 0:
        case 6:
            return "******************** ";
        case 2:
        case 4:
            return "-------------------- ";
        case 1:{
            ss<<matrisAddress;
            return formatAddressBox(ss.str());
        }
        case 3:{
            double arithmeticAv=matrisAddress->arithmeticCalculate();
            string formattedArithmeticAverage=formatArithmeticAverage(arithmeticAv);
            return "*  "+formattedArithmeticAverage+"   * ";
        }
        case 5:{
            if(matrisAddress->next==NULL) return formatAddressBox("0");
            ss<<matrisAddress->next;
            return formatAddressBox(ss.str());
        }
        default:
            return string(21,' ');
    }
}

string MatrisList::formatArithmeticAverage(double arithmeticAv){
    string arithmeticAvString=to_string(arithmeticAv);
    size_t dotIndex=arithmeticAvString.find('.');
    string averageString;
    if(dotIndex!=string::npos){
        string leftPart=arithmeticAvString.substr(0,dotIndex);
        string rightPart=arithmeticAvString.substr(dotIndex,3);
        averageString=leftPart+rightPart;
    }
    else{
        averageString=arithmeticAvString;
    }
    if(averageString.length()>13){
        averageString=averageString.substr(0,13);
    }
    int totalSpace=13-averageString.length();
    int leftPartSpace=totalSpace/2;
    int rightPartSpace=totalSpace-leftPartSpace;
    return string(leftPartSpace,' ')+averageString+string(rightPartSpace,' ');
}

Matris* MatrisList::getMatrisAddress(int matrisNo){
    if(matrisNo<0) return NULL;
    Matris* matrisAddress=head;
    int i=0;
    while(i!=matrisNo&&matrisAddress!=NULL){
        matrisAddress=matrisAddress->next;
        i++;
    }
    return matrisAddress;
}

int MatrisList::getMatrisIndex(Matris* targetMatris){
    if(targetMatris==NULL) return -1;
    Matris* currentMatris=head;
    int matrisIndex=0;
    while(currentMatris!=NULL){
        if(currentMatris==targetMatris) return matrisIndex;
        currentMatris=currentMatris->next;
        matrisIndex++;
    }
    return -1;
}

void MatrisList::insertMatrisPrev(Matris* currentMatris){
    if(currentMatris==head){
        Matris* newMatris=new Matris();
        newMatris->matrisGenerate();
        head=newMatris;
        newMatris->next=currentMatris;
        return;
    }
    if(head==NULL) return;
    Matris* iterator=head;
    while(iterator!=NULL&&iterator->next!=currentMatris){
        iterator=iterator->next;
    }
    if(iterator==NULL) return;
    Matris* newMatris=new Matris();
    newMatris->matrisGenerate();
    iterator->next=newMatris;
    newMatris->next=currentMatris;
}

void MatrisList::insertMatrisNext(Matris* currentMatris){
    if(currentMatris==NULL){
        if(head==NULL){
            Matris* newMatris=new Matris();
            newMatris->matrisGenerate();
            head=newMatris;
        }
        return;
    }
    Matris* newMatris=new Matris();
    newMatris->matrisGenerate();
    Matris* currentNext=currentMatris->next;
    currentMatris->next=newMatris;
    newMatris->next=currentNext;
}

void MatrisList::deleteMatris(int matrisIndex){
    Matris* currentMatris=getMatrisAddress(matrisIndex);
    if(currentMatris==NULL) return;
    if(currentMatris==head){
        head=currentMatris->next;
        delete currentMatris;
    }
    else{
        Matris* deletedMatrisPrev=head;
        while(deletedMatrisPrev->next!=currentMatris){
            deletedMatrisPrev=deletedMatrisPrev->next;
        }
        deletedMatrisPrev->next=deletedMatrisPrev->next->next;
        delete currentMatris;
    }
}

MatrisList::~MatrisList(){
    if(isFileOpened||head!=NULL){
        ofstream matrisFile;
        matrisFile.open("kayitlar.txt",ios::out);
        Matris* currentMatris=head;
        while(currentMatris!=NULL&&matrisFile.is_open()){
            matrisFile<<currentMatris->matrisAsLine()<<endl;
            currentMatris=currentMatris->next;
        }
        matrisFile.close();
    }
    Matris* currentMatris=head;
    Matris* prevMatris=head;
    while(currentMatris!=NULL){
        currentMatris=currentMatris->next;
        delete prevMatris;
        prevMatris=currentMatris;
    }
}