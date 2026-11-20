#include "Matris.h"

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
        Node *currentNode = head;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if(currentNode->data<10) cout << currentNode->data << "  ";
                else cout << currentNode->data << " ";
                currentNode = currentNode->next;
            };
            cout << endl;
        }
    }

string Matris::getLine(int row,int columnDelete=-1,int rowDelete=-1){

    int totalCharacter=0;
    if(head==NULL||row<0||row>this->row) {
        return string(31,' ');
    }   
    Node *currentNode = head; 
    string rowString="";
    for(int i=0;i<this->column*row;i++){
        currentNode=currentNode->next;
    }
    for(int i=0;i<column;i++){
        if(i==0) rowString+="  ";
        if(columnDelete!=i&&i!=0) rowString+=" ";
        if(columnDelete==i) rowString+="|";
        rowString+=currentNode->data;
        if(currentNode->data<10) rowString+=" ";
        if(columnDelete==i) rowString+="|";
        currentNode=currentNode->next;
    }
    if(totalCharacter<31) rowString+=string(31-totalCharacter,' ');
    return rowString;
}

double Matris::arithmeticCalculate()
    {
        int arithmetic = 0;
        Node *currentNode = head;
        int length=0;
        while (currentNode!= NULL)
        {
            length++;
            arithmetic += currentNode->data;
            currentNode = currentNode->next;
        }
        if(length==0) return 0;
        return arithmetic/(double)length;
    }
void Matris::matrisGenerate()
    {
        random_device rd;
        row = (rd() % 9) + 1;
        column = (rd() % 9) + 1;
        head = new Node();
        Node *currentNode = head;
        bool isSame = 0;
        for (int i = 0; i < row * column; i++)
        {
            currentNode->data = (rd() % 100);
            Node *controlNode = head;
            while (controlNode != currentNode)
            {
                if (controlNode->data == currentNode->data){
                    isSame = 1;
                    break;
                }
                controlNode = controlNode->next;
            }
            if (isSame == 1)
            {
                isSame = 0;
                i--;
                continue;
            }
            if(currentNode->next==NULL&&row*column!=i+1) currentNode->next= new Node();
            currentNode=currentNode->next;
        }
    }

void Matris::matrisGenerate(int row, int column, string matris){
        this->column=column;
        this->row=row;
        head = new Node();
        Node* currentNode=head;
        for(int i=0;i<row*column;i++){
            size_t end=matris.find(" ");
            currentNode->data=stoi(matris.substr(0,end));
            if(end==string::npos){
                matris.erase(0,end);
            }
            else{
            matris.erase(0,end+1);
            }
            if(row*column-1!=i){
            currentNode->next=new Node();
            currentNode=currentNode->next;
            }
        }
        
    }   

void Matris::deleteRow(int row){
    row+=1;
    if(row<=0||this->row<row) throw "Row is out of range";
    Node* currentNode=head;
    for(int i=0;i<((row-1)*column-1);i++){
        currentNode=currentNode->next;
    }
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
    for(int i=0;i<column;i++){
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
}

void Matris::deleteColumn(int column){
    column+=1;
    if(column<=0||column>this->column) throw "Column is out of range";
    Node* currentNode=head;
    for(int j=0;j<column-2;j++){   
            currentNode=currentNode->next;
        }
    for(int i=0;i<row;i++){
        if(i==0&&column==1){
            head=currentNode->next;
            delete currentNode;
            currentNode=head;
        }
        else{
            Node* erasedNode=currentNode->next;
            currentNode->next=currentNode->next->next;
            delete erasedNode;
        }
        if(column==1&&i==0){
            for(int j=0;j<this->column-2;j++){
                currentNode=currentNode->next;
            }
        }
        else if(i==row-1){
            break;
        }
        else{
            for(int j=0;j<this->column-1;j++){
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
    if(n1Row>=row||n1Row<0||n1Col>=column||n1Col<0||n2Row>=row||n2Row<0||n2Col>=column||n2Col<0) return;
    int firstNodePos=((n1Row)*column)+n1Col;
    int secondNodePos=((n2Row)*column)+n2Col;
    Node* firstNode=head;
    Node* secondNode=head;
    for(int i=0;i<firstNodePos;i++){
        firstNode=firstNode->next;
    }
    for(int i=0;i<secondNodePos;i++){
        secondNode=secondNode->next;
    }
    int tmpData=firstNode->data;
    firstNode->data=secondNode->data;
    secondNode->data=tmpData;                                                                       
}

void Matris::switchRowColumn(int row,int column){
    if(this->row!=this->column) return;
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
    Node* currentNode=head;
    for(int i=0;i<nodePlace;i++){
        currentNode=currentNode->next;
    }
    currentNode->data=data;
    return;
}

int Matris::getNodeData(int nodePlace){
    Node* currentNode=head;
    for(int i=0;i<nodePlace;i++){
        currentNode=currentNode->next;
    }
    return currentNode->data;
}

Matris::~Matris(){
    for(int i=0;row>0;){
        deleteRow(i);
    }
}