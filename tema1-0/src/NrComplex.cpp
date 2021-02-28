#include "NrComplex.h"
#include <iostream>
#include <cmath>

using namespace std;

NrComplex::NrComplex()
{
    this->re = 0;
    this->im = 0;
}

NrComplex::NrComplex(double _re, double _im)
{
    this->re = _re;
    this->im = _im;
}

NrComplex::NrComplex(NrComplex &c){
    this->re = c.re;
    this->im = c.im;
}

NrComplex::~NrComplex()
{
}

void NrComplex::set(double _re, double _im){
    this->re = _re;
    this->im = _im;
}

void NrComplex::setRe(double _re){
    this->re = _re;
}

void NrComplex::setIm(double _im){
    this->im = _im;
}

double NrComplex::getRe(){
    return this->re;
}

double NrComplex::getIm(){
    return this->im;
}

double NrComplex::calcModul(){
    return sqrt(this->re*this->re+this->im*this->im);
}

NrComplex NrComplex::operator + (NrComplex& c){
    NrComplex suma(this->re+c.re, this->im+c.im);
    return suma;
}

NrComplex NrComplex::operator * (NrComplex& c){
    NrComplex tmp;
    tmp.re = this->re * c.re - this->im * c.im;
    tmp.im = this->re * c.im + this->im * c.re;
    return tmp;
}

NrComplex NrComplex::operator / (NrComplex& c){
    NrComplex tmp;
    double op2modul = c.re * c.re + c.im *c.im;
    tmp.re = (this->re * c.re + this->im *c.im)/op2modul;
    tmp.im = (this->re *c.im - this->im *c.re)/op2modul;
    return tmp;
}


std::ostream& operator << (std::ostream& os, NrComplex &c){
    return os << c.re << " + " << c.im << 'i';
}
