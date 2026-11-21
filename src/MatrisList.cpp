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

string MatrisList::getMatrisRow(int matrisNo,int rowNo){
    if(rowNo==-1) return "";
    if(matrisNo==-1) return string(21,' ');
    Matris* matrisAddress=getMatrisAddress(matrisNo);
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
            string matrisAddressString=ss.str();
            return "*   "+matrisAddressString+"    * ";
        }
        case 3:{
            double arithmeticAv=matrisAddress->arithmeticCalculate();
            string formattedArithmeticAverage=formatArithmeticAverage(arithmeticAv);
            return "*  "+formattedArithmeticAverage+"   * ";
        }
        case 5:{
            ss<<matrisAddress->next;
            string matrisNextAddressString=ss.str();
            if(matrisNextAddressString=="0") return "*        0         * ";
            return "*   "+matrisNextAddressString+"    * ";
        }
        default:
            return string(21,' ');
    }
}

string MatrisList::formatArithmeticAverage(double arithmeticAv){
    string formattedArithmeticAverage="";
    string arithmeticAvString=to_string(arithmeticAv);
    string leftPart=arithmeticAvString.substr(0,arithmeticAvString.find('.'));
    string rightPart=arithmeticAvString.erase(0,arithmeticAvString.find('.')).erase(3);
    int rightPartNum=rightPart.length();
    int leftPartNum=leftPart.length();
    int occupiedSpace=leftPartNum+rightPartNum;
    int leftPartSpace=(13-occupiedSpace)/2;
    int rightPartSpace=(13-occupiedSpace)-leftPartSpace;
    for(int i=0;i<leftPartSpace;i++){
        formattedArithmeticAverage+=" ";
    }
    formattedArithmeticAverage+=leftPart+rightPart;
    for(int i=0;i<rightPartSpace;i++){
        formattedArithmeticAverage+=" ";
    }
    return formattedArithmeticAverage;
}

Matris* MatrisList::getMatrisAddress(int matrisNo) {
    if (matrisNo < 0) return NULL;
    Matris* matrisAddress = head;
    int i = 0;
    while (i != matrisNo && matrisAddress != NULL) {
        matrisAddress = matrisAddress->next;
        i++;
    }
    return matrisAddress;
}

void MatrisList::insertMatrisPrev(Matris* currentMatris){
    Matris* iterator=head;
    Matris* newMatris= new Matris();
    newMatris->matrisGenerate();
    if(currentMatris!=head){
        while(iterator->next!=currentMatris){
            iterator=iterator->next;
        }
        iterator->next=newMatris;
        newMatris->next=currentMatris;
    }
    else{
        head=newMatris;
        newMatris->next=currentMatris;
    }
}

void MatrisList::insertMatrisNext(Matris* currentMatris){
    Matris* newMatris=new Matris();
    newMatris->matrisGenerate();
    Matris* currentNext=currentMatris->next;
    currentMatris->next=newMatris;
    newMatris->next=currentNext;
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