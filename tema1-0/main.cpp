#include <iostream>
#include <NrComplex.h>

using namespace std;

int main()
{
    NrComplex c1(1,2);

    cout << c1 << '\n';

   NrComplex  c2(c1);

   cout << c2 << '\n';

   NrComplex c3;
   c3 = c1 + c2;

   cout << c3 << '\n';

    return 0;
}
