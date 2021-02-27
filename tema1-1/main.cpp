#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

bool show_destr = false;

class NrComplex
{
    double re;
    double im;

    friend class VectorComplex;

public:
    NrComplex()
    {
        this->re = 0;
        this->im = 0;
    }
    NrComplex(double _re, double _im)
    {
        this->re = _re;
        this->im = _im;
    }
    NrComplex(NrComplex &c)
    {
        this->re = c.re;
        this->im = c.im;
    }

    ~NrComplex()
    {
        if (show_destr)
            cout << "destroyed complex nr" << '\n';
    }

    void set(double _re, double _im)
    {
        this->re = _re;
        this->im = _im;
    }

    void setRe(double _re)
    {
        this->re = _re;

    }
    void setIm(double _im)
    {
        this->im = _im;

    }

    double getRe()
    {
        return this->re;
    }
    double getIm()
    {
        return this->im;
    }

    double calcModul()
    {
        return sqrt(this->re*this->re+this->im*this->im);
    }

    NrComplex operator + (NrComplex& c)
    {
        NrComplex suma(this->re+c.re, this->im+c.im);
        return suma;
    }

    NrComplex operator * (NrComplex& c)
    {
        NrComplex tmp;
        tmp.re = this->re * c.re - this->im * c.im;
        tmp.im = this->re * c.im + this->im * c.re;
        return tmp;
    }

    NrComplex operator / (NrComplex& c)
    {
        NrComplex tmp;
        double op2modul = c.re * c.re + c.im *c.im;
        tmp.re = (this->re * c.re + this->im *c.im)/op2modul;
        tmp.im = (this->re *c.im - this->im *c.re)/op2modul;
        return tmp;
    }

    bool operator < (NrComplex& c){
        return this->calcModul() < c.calcModul();
    }

    //friend std::ostream& operator << (std::ostream&, NrComplex&);
    friend std::ostream& operator<<(std::ostream& os,NrComplex& c){
        return os << c.re << " + " << c.im << 'i' << '\n';
    }
};

class VectorComplex:NrComplex{
    NrComplex* data;
    int _size;

public:
    VectorComplex(){
        this->_size = 0;
        this->data = nullptr;
    }

    VectorComplex(NrComplex& c, int _s){
        this->_size = _s;
        data = new NrComplex[this->_size];

        for (int i = 0; i < this->_size; i++)
            this->data[i] = c;
    }

    VectorComplex(VectorComplex& v){
        this->_size = v._size;
        this->data = new NrComplex[this->_size];

        for (int i = 0; i < this->_size; i++)
            this->data[i] = v.data[i];
    }

    ~VectorComplex(){
        delete []this->data;
        if (show_destr)
            cout << "deleted vector" << '\n';
    }

    int get_size(){
        return this->_size;
    }

    double* calc_module(){
        double* module = new double[this->_size];
        for (int i = 0; i < this->_size; i++)
            module[i] = this->data[i].calcModul();
        return module;
    }

    NrComplex& operator [](int poz){
        return this->data[poz];
    }

    friend std::ostream& operator << (std::ostream& os, VectorComplex& v){
        for (int i = 0; i < v._size; i++)
            os << v.data[i];
        return os;
    }

    void sort_by_module(){
        //cout << this->data << ' ' << this->data+this->_size << '\n';
        //sort(this->data, this->data+this->_size);
        for (int i = 0; i < _size-1; i++)
            for (int j = i + 1; j < _size; j++)
                if (data[j] < data[i]){
                    NrComplex aux = data[i];
                    data[i] = data[j];
                    data[j] = aux;
                }
    }

    NrComplex calc_suma(){
        NrComplex suma;
        for (int i = 0; i < this->_size; i++)
            suma = suma + this->data[i];
        return suma;
    }
};

int main()
{

    NrComplex c1(2,3);
    NrComplex c2(4,6);

    VectorComplex v1(c1,5);

    v1[2] = c2;
    v1[3] = c2;

    NrComplex suma;
    suma = v1.calc_suma();

    cout << v1;

    cout << suma;

    v1.sort_by_module();

    cout << v1;
    /*
    double* module = v1.calc_module();
    for (int i = 0; i < v1.get_size(); i++)
        cout << module[i] << ' ';
    */

    cout << "\n\n end of program";

    return 0;
}
