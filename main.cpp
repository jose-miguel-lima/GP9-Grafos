#include <iostream>
#include "No.h"
#include "Aresta.h"


using namespace std;

int main(){
    
    cout << "Olá!"<<endl;

    No* no = new No(1);
    cout << no->foiVisitado() << endl;

return 0;
}