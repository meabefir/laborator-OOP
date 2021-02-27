#include <iostream>
#include <NrComplex.h>

using namespace std;

int main()
{
    NrComplex c1(1,2);

    cout << c1 << '\n';

   NrComplex  c2(c1);

   cout << c2 << '\n';

    return 0;
}
