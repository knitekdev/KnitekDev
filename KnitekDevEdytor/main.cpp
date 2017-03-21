#include <iostream>
#include "edytor.hpp"

//#include "edytor.hpp"

using namespace std;

int main()
{
    int numer=0;
    cout<<"Podaj numer poziomu: ";
    cin>>numer;
    Edytor edytor;
    edytor.run(numer);
    cout<<"Zakonczono dzialanie programu"<<endl;
}
