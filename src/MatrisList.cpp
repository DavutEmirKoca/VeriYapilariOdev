#include "MatrisList.h"

MatrisList::MatrisList(){
    fstream matrisFile;
    head=NULL;
    matrisFile.open("kayitlar.txt", ios::in);
    if(matrisFile.is_open()){
        string line;
        Matris* currentMatris=head;
        while(getline(matrisFile,line)){
            size_t end=line.find(" ");
            int row=stoi(line.substr(0,end));
            line.erase(0,end+1);
            end=line.find(" ");
            int column=stoi(line.substr(0,end));
            line.erase(0,end+1);
            Matris* newMatris=new Matris();
            newMatris->matrisGenerate(row,column,line);
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
    isChanged=0;
    Matris* currentMatris=head;
    Matris* prevMatris=head;
    while(currentMatris->next!=NULL){
        if(currentMatris->arithmeticCalculate()<currentMatris->next->arithmeticCalculate()){
            isChanged=1;
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
        if(currentMatris!=prevMatris)prevMatris=prevMatris->next;
        currentMatris=currentMatris->next;
    }
}while(isChanged==1);
}

void MatrisList::print(){
}

MatrisList::~MatrisList(){
    ofstream matrisFile;
    matrisFile.open("kayitlar.txt",ios::out);
    Matris* currentMatris=head;
    while(currentMatris!=NULL&&matrisFile.is_open()){
        matrisFile<<currentMatris->matrisAsLine()<<endl;
        currentMatris=currentMatris->next;
    }
    matrisFile.close();
    currentMatris=head;
    Matris* prevMatris=head;
    while(currentMatris!=NULL){
        currentMatris=currentMatris->next;
        delete prevMatris;
        prevMatris=currentMatris;
    }
}