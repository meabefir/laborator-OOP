#include <iostream>
#include <vector>

using namespace std;

#define MAX_SIZE 100

class Multime{
    int data[MAX_SIZE];
    int max_size = MAX_SIZE;
    int _size;

public:
    Multime();
    Multime(vector<int>);
    Multime(const Multime&);
    ~Multime();

    // setere
    void set_data(vector<int> &); // transforma un vector in multime

    // gettere
    int get_size(); // returneaza nr de elemente curent al multimii
    int get_max_size(); // returneaza nr maxim de elemente ce se pot afla in multime

    //
    void insert(int); // insereaza un element in multime
    void remove(int); // sterge valoarea int din multime

    // input, output
    friend ostream& operator << (ostream &, Multime&); // afiseaza multimea
    friend istream& operator >> (istream &, Multime&); // citeste multime (nr de elemente + elemente)

    // operator overloading

    Multime& operator = (const Multime &);
    Multime& operator += (int); // insereaza un element
    friend Multime operator + (Multime,int); // insereaza un element
    friend Multime operator + (int, Multime); // insereaza un element
    Multime operator + (const Multime&); // reuniunea a 2 multimi
    Multime operator * (const Multime&); // intersectia a 2 multimi
    Multime operator - (const Multime&); // diferenta a 2 multimi
};

Multime::Multime(){
    this->_size = 0;
}

Multime::Multime(vector<int> v){
    this->set_data(v);
}

Multime::Multime(const Multime &m){
    this->_size = m._size;
    for (int i = 0; i < this->_size;i++)
        this->data[i] = m.data[i];
}

Multime::~Multime(){
    this->_size = 0;
}

int Multime::get_size(){
    return this->_size;
}

int Multime::get_max_size(){
    return this->max_size;
}

void Multime::insert(int x){
    if (this->_size == this->max_size){
        // multimea este plina
        return;
    }
    bool exista = false;
    for (int i = 0; i < this->_size; i++)
        if (this->data[i] == x){
            exista = true;
            break;
        }
    if (!exista){
        this->data[this->_size++] = x;
    }
}

void Multime::remove(int x){
    int poz = 0;
    for (poz = 0; poz < this->_size; poz++)
        if (this->data[poz] == x)
            break;
    if (poz == this->_size)
        return;
    if (poz == this->_size-1){
        this->_size--;
        return;
    }
    for (int i = poz; i < this->_size-1; i++)
        this->data[i] = this->data[i+1];
    this->_size --;
}

void Multime::set_data(vector<int> &v){
    if (v.size() == 0){
        this->_size = 0;
        return;
    }
    // maxim si vector de frecventa
    int maxim = v[0];
    for (int i = 1; i < v.size(); i++)
        if (v[i] > maxim)
            maxim = v[i];
    vector<int> freq(maxim+1,0);
    for (int i = 0; i < v.size(); i++)
        freq[v[i]] ++;

    int k = 0;
    for (int i = 0; i < freq.size() && k < this->max_size; i++)
        if (freq[i] > 0)
            this->data[k++] = i;
    this->_size = k;
}

ostream& operator << (ostream &os, Multime &m){
    if (m._size == 0){
        cout << " Multimea este vida!\n";
        return os;
    }
    for (int i = 0; i < m._size; i++)
        os << m.data[i] << ' ';
    os << '\n';
    return os;
}

istream& operator >> (istream &is, Multime &m){
    int n;
    cout << " Introduceti dimensiunea vectorului de citit: ";
    is >> n;
    cout << "\n Introduceti " << n << " elemente: ";
    vector<int> temp(n);
    for (auto &el: temp)
        is >> el;
    cout << "\n";
    m.set_data(temp);
    return is;
}

Multime& Multime::operator += (int x){
    this->insert(x);
    return *this;
}

Multime operator + (Multime m, int x){
    Multime temp(m);
    temp.insert(x);
    return temp;
}

Multime operator + (int x, Multime m){
    Multime temp(m);
    temp.insert(x);
    return temp;
}

Multime& Multime::operator = (const Multime &m){
    if (this != &m){
        this->_size = m._size;
        for (int i = 0; i < this->_size; i++)
            this->data[i] = m.data[i];
    }
    return *this;
}

Multime Multime::operator + (const Multime &m){
    vector<int> v_reuniune;
    for (int i = 0; i < this->_size; i++)
        v_reuniune.push_back(this->data[i]);
    for (int i = 0; i < m._size; i++)
        v_reuniune.push_back(m.data[i]);

    Multime m_reuniune(v_reuniune);
    return m_reuniune;
}

Multime Multime::operator * (const Multime &m){
    vector<int> v_intersectie;
    for (int i = 0; i < this->_size; i++)
        for (int j = 0; j < m._size; j++)
            if (this->data[i] == m.data[j]){
                v_intersectie.push_back(this->data[i]);
                break;
            }
    Multime m_intersectie(v_intersectie);
    return m_intersectie;
}

Multime Multime::operator - (const Multime &m){
    vector<int> v_dif;
    for (int i = 0; i < this->_size; i++){
        bool exista = false;
        for (int j = 0; j < m._size; j++)
            if (this->data[i] == m.data[j]){
                exista = true;
                break;
            }
        if (!exista)
            v_dif.push_back(this->data[i]);
    }

    Multime m_dif(v_dif);
    return m_dif;
}

void play();

int main()
{
    play();

    return 0;

    Multime m1(vector<int>{1,2,3,4,4,5});
    Multime m2(vector<int>{4,5,6,7,7});
    Multime m3(vector<int>{7,8,9,9,10,11,12});
    Multime m4 = m1 + m3 * m2;

    cout << m1;

    return 0;
}

void afiseaza_multimi(vector<Multime> &multimi){
    cout << "\n\n\n";
    for (int i = 0; i < multimi.size(); i++){
        cout << " " << i << ": " << multimi[i];
    }
    cout << "\n";
}

void play(){
    bool playing = true;
    vector<Multime> multimi;
    while (playing){
        cout << "\n\n\n1 - creeaza multime\n2 - sterge multime\n3 - modifica multime\n4 - operatie intre multimi\n5 - afiseaza multimile\n0 - incheie programul\n";
        int input;
        cout << "\nAlege optiune: ";
        cin >> input;
        cout << '\n';

        switch(input){
        case 1:
        {
            Multime new_m;
            cin >> new_m;
            multimi.push_back(new_m);

            cout << " Multime creata\n";
            break;
        }
        case 2:
        {
            afiseaza_multimi(multimi);
            cout << " Introdu indexul pozitiei de sters: ";
            int poz;
            cin >> poz;
            cout << '\n';
            if (poz < 0 || poz >= multimi.size()){
                cout << " Index invalid!\n\n";
                break;
            }
            multimi.erase(multimi.begin()+poz);
            cout << " Elementul de pe pozitia " << poz << " a fost sters!\n";
            break;
        }
        case 3:
        {
            afiseaza_multimi(multimi);
            cout << " Introdu indexul pozitiei de modificat (" << 0 << '-' << multimi.size()-1 << ") :";
            int poz;
            cin >> poz;
            if (poz < 0 || poz >= multimi.size()){
                cout << " Index invalid!\n\n";
                break;
            }
            else{
                int playing3 = true;
                while(playing3){
                    cout << "\n\n" << multimi[poz];
                    cout << "\n1 - atribuie vector\n2 - insereaza element\n3 - sterge element\n0 - inapoi";
                    int input_3;
                    cout << "\nAlege optiune: ";
                    cin >> input_3;
                    cout << '\n';
                    switch(input_3){
                    case 1:
                        cin >> multimi[poz];
                        break;
                    case 2:
                    {
                        int x;
                        cout << " Introdu valoarea de adaugat: ";
                        cin >> x;
                        cout << '\n';
                        multimi[poz].insert(x);
                        break;
                    }
                    case 3:
                    {
                        int x;
                        cout << " Introdu valoarea de sters: ";
                        cin >> x;
                        cout << '\n';
                        multimi[poz].remove(x);
                        break;
                    }
                    case 0:
                    {
                        playing3 = false;
                        break;
                    }
                    default:
                        cout << " Input gresit!\n";
                        break;
                    }



                    //cin >> multimi[poz];
                }
            }
            break;
        }
        case 4:
        {
            afiseaza_multimi(multimi);
            cout << " Introdu indexul celor 2 multimi (" << 0 << '-' << multimi.size()-1 << ") :";
            int poz1,poz2;
            cin >> poz1 >> poz2;
            if (poz1 < 0 || poz1 >= multimi.size() || poz2 < 0 || poz2 >= multimi.size()){
                cout << " Index invalid!\n\n";
                break;
            } else {
                cout << "\n\n1 - reuniune\n2 - intersectie\n3 - diferenta\n";
                int tip_operatie;
                cin >> tip_operatie;
                switch(tip_operatie){
                case 1:
                    {
                        Multime reuniune(multimi[poz1]+multimi[poz2]);
                        cout << " Reuniunea este:\n";
                        cout << reuniune;
                        cout << " Daca vreti sa adaugati multimea rezultata in vectorul de multimi introduceti 1, altfel introduceti 0: ";
                        int keep;
                        cin >> keep;
                        if (keep)
                            multimi.push_back(reuniune);
                        break;
                    }
                case 2:
                    {
                        Multime intersectie(multimi[poz1]*multimi[poz2]);
                        cout << " Intersectia este:\n";
                        cout << intersectie;
                        cout << " Daca vreti sa adaugati multimea rezultata in vectorul de multimi introduceti 1, altfel introduceti 0: ";
                        int keep;
                        cin >> keep;
                        if (keep)
                            multimi.push_back(intersectie);
                        break;
                    }
                case 3:
                    {
                        Multime diferenta(multimi[poz1]-multimi[poz2]);
                        cout << " Diferenta este:\n";
                        cout << diferenta;
                        cout << " Daca vreti sa adaugati multimea rezultata in vectorul de multimi introduceti 1, altfel introduceti 0: ";
                        int keep;
                        cin >> keep;
                        if (keep)
                            multimi.push_back(diferenta);
                        break;
                    }
                default:
                    cout << " Input invalid!\n\n";
                    break;
                }
            }
            break;
        }
        case 5:
        {
            afiseaza_multimi(multimi);
            break;
        }
        case 0:
            playing = false;
            break;
        default:
            cout << "Input gresit!\n\n\n\n";
            break;
        }
    }
}

