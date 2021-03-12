#include <iostream>
#include "List.h"

using namespace std;

int main()
{
    List a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);
    a.push(6);
    a.push(7);

    a.print();

    a.delete_index(3);

    a.print();

    cout << a.get_at(2);

    a.delete_value(6);
    a.delete_value(1);
    a.delete_value(7);

    a.push(10);

    cout << a.get_first() << " first \n";

    a.push(10);
    cout << a.get_last() << " last \n";
    a.print();

    cout << a.get_max() << '\n';

    return 0;
}
