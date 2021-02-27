#include <iostream>

class NrComplex
{
    double re;
    double im;

public:
    NrComplex();
    NrComplex(double, double);
    NrComplex(NrComplex &);

    ~NrComplex();

    void set(double, double);
    void setRe(double);
    void setIm(double);

    double getRe();
    double getIm();

    double calcModul();

    NrComplex operator + (NrComplex&);
    NrComplex operator * (NrComplex&);
    NrComplex operator / (NrComplex&);

    //friend std::ostream& operator << (std::ostream&, NrComplex&);
    friend std::ostream& operator<<(std::ostream&,NrComplex&);
};
