#include <iostream>
#include <algorithm>

using namespace std;

class Vector{
    int *data;
    int _size;

public:
    Vector(int c, int _s){
        this->_size = _s;
        this->data = new int[_s];

        for (int i = 0; i < this->_size; i++)
            this->data[i] = c;
    }

    Vector(){}

    Vector(Vector &v){
        this->_size = v._size;
        this->data = new int[this->_size];
        for (int i = 0; i < this->_size; i++)
            this->data[i] = v.data[i];
    }

    ~Vector(){
        delete []this->data;
        cout << "destructed\n";
    }

    void operator = (Vector v){
        delete []this->data;
        this->_size = v._size;
        this->data = new int[this->_size];
        for (int i = 0; i < this->_size; i++)
            this->data[i] = v.data[i];
    }

    void update(int c, int _s){
        delete []this->data;
        this->_size = _s;
        this->data = new int[this->_size];
        for (int i = 0; i < this->_size; i++)
            this->data[i] = c;
    }

    friend std::ostream& operator<<(std::ostream& os,Vector &v){
        for (int i = 0; i < v._size; i++)
            cout << v.data[i] << ' ';
        cout << '\n';
    }

    int suma(){
        int s = 0;
        for (int i = 0; i < this->_size; i++)
            s += this->data[i];
        return s;
    }

    int& operator [](int poz){
        return data[poz];
    }

    int maxim(){
        int _max = this->data[0];
        for (int i = 1; i < this->_size; i++)
            if (this->data[i] > _max)
                _max = this->data[i];
        return _max;
    }

    int maxim_poz(){
        int _max = this->data[0];
        int _poz = 0;
        for (int i = 1; i < this->_size; i++)
            if (this->data[i] > _max){
                _max = this->data[i];
                _poz = i;
            }
        return _poz;
    }

    void sorteaza(){
        sort(data,data+_size);
    }
};

int main()
{

    Vector a(10,10);
    a[2] = 2;
    a[3] = 13;
    cout << a;

    cout << a.suma() << '\n';
    cout << a.maxim() << '\n';
    cout << a.maxim_poz() << '\n';

    a.sorteaza();

    cout << a;

    return 0;
}
