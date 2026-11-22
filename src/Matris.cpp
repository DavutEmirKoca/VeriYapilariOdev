/**
* @file Matris.cpp
* @description Düğümleri tutan matris ve işlemleri
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#include "Matris.hpp"

Matris::Matris(){
    head=NULL;
    row=0;
    column=0;
    next=NULL;
}

void Matris::print(){
        if(head==NULL) {
            cout<<" ";
            return;
        };
        Node *currentNode=head;
        for (int i=0;i<row;i++)
        {
            for (int j=0;j<column;j++)
            {
                if(currentNode->data<10) cout << currentNode->data << "  ";
                else cout << currentNode->data << " ";
                currentNode=currentNode->next;
            };
            cout << endl;
        }
    }

string Matris::getLine(int row,int columnDelete=-1,int rowDelete=-1){ 
    Node *currentNode=head; 
    string rowString="";
    
   if(columnDelete!=-1){
        if(head==NULL||row<0||row>=this->row+2) return string(33,' ');
        if(row!=0&&row!=this->row+1){
            row--;
            for(int i=0;i<this->column*row&&currentNode!=NULL;i++){
                currentNode=currentNode->next;
            }
            for(int i=0;i<column&&currentNode!=NULL;i++){
                if(i==0) rowString+="  ";
                if(columnDelete==i) rowString+="|";
                rowString+=to_string(currentNode->data);
                if(currentNode->data<10) rowString+=" ";
                if(columnDelete==i) rowString+="|";
                else if(columnDelete!=i+1)rowString+=" ";
                currentNode=currentNode->next;
            }
        }
        else{
            for(int i=0;i<column;i++){
                if(i==columnDelete){
                    if(i==0)rowString+="  |--|";
                    else rowString+=" |--|";
                }
                else rowString+=string(3,' ');
            }
        }
    }
    else if(rowDelete!=-1){
        if(head==NULL||row<0||row>=this->row+2) return string(33,' ');

        if(row==rowDelete||row==rowDelete+2){
            int starCount=this->column*3+1;
            if(starCount>32) starCount=32;
            return " "+string(starCount,'*')+string(32-starCount,' ');
        }
        else if(row==rowDelete+1){
            for(int i=0;i<this->column*rowDelete&&currentNode!=NULL;i++){
                currentNode=currentNode->next;
            }
            for(int i=0;i<column&&currentNode!=NULL;i++){
                if(i==0) rowString+="  ";
                if(i!=0) rowString+=" ";
                rowString+=to_string(currentNode->data);
                if(currentNode->data<10) rowString+=" ";
                currentNode=currentNode->next;
            }
        }
        else if(row>rowDelete+2){
            for(int i=0;i<this->column*(row-2)&&currentNode!=NULL;i++){
                currentNode=currentNode->next;
            }
            for(int i=0;i<column&&currentNode!=NULL;i++){
                if(i==0) rowString+="  ";
                if(i!=0) rowString+=" ";
                rowString+=to_string(currentNode->data);
                if(currentNode->data<10) rowString+=" ";
                currentNode=currentNode->next;
            }
        }
        else{
            for(int i=0;i<this->column*row&&currentNode!=NULL;i++){
                currentNode=currentNode->next;
            }
            for(int i=0;i<column&&currentNode!=NULL;i++){
                if(i==0) rowString+="  ";
                if(i!=0) rowString+=" ";
                rowString+=to_string(currentNode->data);
                if(currentNode->data<10) rowString+=" ";
                currentNode=currentNode->next;
            }
        }
    }
    else{
        if(head==NULL||row<0||row>=this->row) return string(33,' ');
        for(int i=0;i<this->column*row&&currentNode!=NULL;i++){
            currentNode=currentNode->next;
        }
        for(int i=0;i<column&&currentNode!=NULL;i++){
            if(i==0) rowString+="  ";
            if(i!=0) rowString+=" ";
            rowString+=to_string(currentNode->data);
            if(currentNode->data<10) rowString+=" ";
            currentNode=currentNode->next;
        }
    }
    if(rowString.length()>33) rowString=rowString.substr(0,33);
    else if(rowString.length()<33) rowString+=string(33-rowString.length(),' ');
    return rowString;
}

double Matris::arithmeticCalculate()
    {
        int arithmetic=0;
        Node *currentNode=head;
        int length=0;
        while(currentNode!=NULL)
        {
            length++;
            arithmetic+=currentNode->data;
            currentNode=currentNode->next;
        }
        if(length==0) return 0;
        return arithmetic/(double)length;
    }
void Matris::matrisGenerate()
    {
        clearMatris();
        random_device rd;
        row=(rd()%9)+1;
        column=(rd()%9)+1;
        head=new Node();
        Node *currentNode=head;
        bool isSame=0;
        for(int i=0;i<row*column;i++)
        {
            currentNode->data=(rd()%100);
            Node *controlNode=head;
            while(controlNode!=currentNode)
            {
                if(controlNode->data==currentNode->data){
                    isSame=1;
                    break;
                }
                controlNode=controlNode->next;
            }
            if(isSame==1)
            {
                isSame=0;
                i--;
                continue;
            }
            if(currentNode->next==NULL&&row*column!=i+1) currentNode->next=new Node();
            currentNode=currentNode->next;
        }
    }

void Matris::matrisGenerate(int row,int column,string matris){
        clearMatris();
        if(row<=0||column<=0){
            return;
        }
        this->column=column;
        this->row=row;
        head=new Node();
        Node* currentNode=head;
        for(int i=0;i<row*column;i++){
            while(matris.length()>0&&(matris[0]==' '||matris[0]=='\r'||matris[0]=='\t')){
                matris.erase(0,1);
            }
            if(matris==""){
                clearMatris();
                return;
            }
            size_t end=matris.find(" ");
            if(end==string::npos){
                currentNode->data=stoi(matris);
                matris="";
            }
            else{
                currentNode->data=stoi(matris.substr(0,end));
                matris.erase(0,end+1);
            }
            if(row*column-1!=i){
                currentNode->next=new Node();
                currentNode=currentNode->next;
            }
        }
    }   

void Matris::deleteRow(int row){
    if(head==NULL||row<0||row>=this->row||this->column<=0) return;
    row+=1;
    Node* currentNode=head;
    for(int i=0;i<((row-1)*column-1)&&currentNode!=NULL;i++){
        currentNode=currentNode->next;
    }
    if(currentNode==NULL) return;
    Node* currentNextNode;
    Node* erasedNode;
    bool headDeleted=0;
    if(row!=1){
        currentNextNode=currentNode->next;
        erasedNode=currentNode->next;
    }
    else{
        currentNextNode=currentNode;
        erasedNode=currentNode;
        headDeleted=1;
    }
    for(int i=0;i<column&&currentNextNode!=NULL;i++){
        currentNextNode=currentNextNode->next;
        delete erasedNode;
        erasedNode=currentNextNode;
    }
    if(headDeleted){
        head=currentNextNode;
    }
    else{
        currentNode->next=currentNextNode;
    }
    
    this->row-=1;
    if(this->row==0){
        this->column=0;
    }
}

void Matris::deleteColumn(int column){
    if(head==NULL||this->row<=0||column<0||column>=this->column) return;
    column+=1;
    if(this->column==1){
        clearMatris();
        return;
    }
    Node* currentNode=head;
    for(int j=0;j<column-2&&currentNode!=NULL;j++){
        currentNode=currentNode->next;
    }
    for(int i=0;i<row;i++){
        if(currentNode==NULL) break;

        if(i==0&&column==1){
            head=currentNode->next;
            delete currentNode;
            currentNode=head;
        }
        else{
            if(currentNode->next==NULL) break;
            Node* erasedNode=currentNode->next;
            currentNode->next=erasedNode->next;
            delete erasedNode;
        }
        if(i==row-1){
            break;
        }
        if(column==1&&i==0){
            for(int j=0;j<this->column-2&&currentNode!=NULL;j++){
                currentNode=currentNode->next;
            }
        }
        else{
            for(int j=0;j<this->column-1&&currentNode!=NULL;j++){
                currentNode=currentNode->next;
            }
        }
    }

    this->column-=1;
}

string Matris::matrisAsLine(){
    string line="";
    line+=to_string(row)+" "+to_string(column)+" ";
    Node* currentNode=head;
    while(currentNode!=NULL){
        line+=to_string(currentNode->data)+" ";
        currentNode=currentNode->next;
    }  
    return line;
}

bool Matris::isEmpty(){
    if(head==NULL) return true;
    else return false;
}

void Matris::switchNodePlaces(int n1Row,int n1Col, int n2Row, int n2Col){
    if(head==NULL||n1Row>=row||n1Row<0||n1Col>=column||n1Col<0||n2Row>=row||n2Row<0||n2Col>=column||n2Col<0) return;
    int firstNodePos=((n1Row)*column)+n1Col;
    int secondNodePos=((n2Row)*column)+n2Col;
    Node* firstNode=head;
    Node* secondNode=head;
    for(int i=0;i<firstNodePos&&firstNode!=NULL;i++){
        firstNode=firstNode->next;
    }
    for(int i=0;i<secondNodePos&&secondNode!=NULL;i++){
        secondNode=secondNode->next;
    }
    if(firstNode==NULL||secondNode==NULL) return;
    int tmpData=firstNode->data;
    firstNode->data=secondNode->data;
    secondNode->data=tmpData;                                                                       
}

void Matris::switchRowColumn(int row,int column){
    if(head==NULL||this->row<=0||this->row!=this->column) return;
    if(row<0||row>=this->row||column<0||column>=this->column) return;
    int nodeIntersectionData=getNodeData(((row)*this->column)+column);
    for(int i=0;i<this->row;i++){
        if(i!=column){
            switchNodePlaces(row,i,i,column);
        }
        else{
            insertNodeData((i*this->column)+column,nodeIntersectionData);
        }
    }
}

void Matris::insertNodeData(int nodePlace,int data){
    if(head==NULL||nodePlace<0) return;
    Node* currentNode=head;
    for(int i=0;i<nodePlace&&currentNode!=NULL;i++){
        currentNode=currentNode->next;
    }
    if(currentNode==NULL) return;
    currentNode->data=data;
    return;
}

int Matris::getNodeData(int nodePlace){
    if(head==NULL||nodePlace<0) return 0;
    Node* currentNode=head;
    for(int i=0;i<nodePlace&&currentNode!=NULL;i++){
        currentNode=currentNode->next;
    }
    if(currentNode==NULL) return 0;
    return currentNode->data;
}

void Matris::clearMatris(){
    while(head!=NULL){
        Node* erasedNode=head;
        head=head->next;
        delete erasedNode;
    }
    row=0;
    column=0;
}

Matris::~Matris(){
    clearMatris();
}