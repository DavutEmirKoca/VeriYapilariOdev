#include "MatrisList.h"
#include <random>
using namespace std;

int main()
{
    MatrisList* m=new MatrisList();
    m->arithmeticOrder();
    delete m;
    return 0;
}