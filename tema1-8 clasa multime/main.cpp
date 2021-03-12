#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Multime{
    int *data, alocate, dim;

public:
    Multime();
    Multime(vector<int>);
    Multime(const Multime&);
    Multime& operator = (const Multime&);
    ~Multime();
    int get_size();
    vector<int> get_data();
    void vector_to_multime(vector<int>);
    friend ostream& operator << (ostream&, Multime&);
    Multime operator + (const Multime &);
    Multime operator * (const Multime &);
    Multime operator - (const Multime &);
    Multime& operator += (const int);
    friend Multime operator + (const Multime &,const int);
    friend Multime operator + (const int,const Multime &);
};

Multime::Multime(){
    dim = 0;
    alocate = 10;
    data = new int[alocate];
}

Multime::Multime(vector<int> x){
    dim = x.size();
    alocate = x.size();
    data = new int[alocate];
    vector_to_multime(x);
}

Multime::Multime(const Multime &m){
    dim = m.dim;
    alocate = m.alocate;
    data = new int[alocate];
    for (int i = 0; i < m.dim; i++)
        data[i] = m.data[i];
}

Multime& Multime::operator =(const Multime &m){
    if (&m != this){
        vector<int> m_data(m.dim);
        for (int i = 0; i < m.dim; i++)
            m_data[i] = m.data[i];
        this->vector_to_multime(m_data);
    }
    return *this;
}

Multime::~Multime(){
    delete []data;
}

int Multime::get_size(){
    return this->dim;
}

vector<int> Multime::get_data(){
    vector<int> r(this->dim);
    for (int i = 0; i < this->dim; i++)
        r[i] = this->data[i];
    return r;
}

void Multime::vector_to_multime(vector<int> v){
    if (v.size() == 0){
        dim = 0;
        return;
    }
    int maxim = v[0];
    for (int i = 1; i < v.size(); i++)
        if (v[i] > maxim)
            maxim = v[i];
    vector<int> frecv(maxim+1);
    int new_dim = 0;
    for (int i = 0; i < v.size(); i++){
        if (frecv[v[i]] == 0)
            new_dim ++;
        frecv[v[i]] = 1;
    }

    if (new_dim > alocate){
        //cout << " Aloca extra spatiu \n";
        alocate = new_dim;
        dim = new_dim;
        int *new_data = new int[alocate];
        int k = 0;
        for (int i = 0; i <= maxim; i++)
            if (frecv[i] == 1)
                new_data[k++] = i;
        delete []data;
        data = new_data;
    } else {
        //cout << " Spatiul este indeajuns \n";
        dim = new_dim;
        int k = 0;
        for (int i = 0; i <= maxim; i++)
            if (frecv[i] == 1)
                data[k++] = i;
    }
}

std::ostream& operator << (std::ostream& os, Multime& m){
    if (m.dim == 0){
        os << " Multimea este vida. \n";
        return os;
    }
    for (int i = 0; i < m.dim; i++)
        os << m.data[i] << ' ';
    os << '\n';
    return os;
}

std::istream& operator >> (istream &is, Multime &m){
    cout << "\n Introduceti nr de elemente: ";
    int nr;
    is >> nr;
    cout << "\n Introduceti " << nr << " numere: ";
    vector<int> elemente(nr);
    for (int &el: elemente){
        is >> el;
    }
    m.vector_to_multime(elemente);
    return is;
}

Multime& Multime::operator +=(const int new_val){
    vector<int> el(this->dim+1);
    for (int i = 0; i < this->dim; i++)
        el[i] = this->data[i];
    el[el.size()-1] = new_val;

    vector_to_multime(el);

    return *this;
}

Multime operator +(const Multime &m,const int new_val){
    Multime temp(m);

    vector<int> el(temp.dim+1);
    for (int i = 0; i <temp.dim; i++)
        el[i] = temp.data[i];
    el[el.size()-1] = new_val;

    temp.vector_to_multime(el);

    return temp;
}

Multime operator +(const int new_val,const Multime &m){
    Multime temp(m);

    vector<int> el(temp.dim+1);
    for (int i = 0; i <temp.dim; i++)
        el[i] = temp.data[i];
    el[el.size()-1] = new_val;

    temp.vector_to_multime(el);

    return temp;
}

Multime Multime::operator +(const Multime &m){
    vector<int> el_multimi;
    for (int i = 0; i < dim; i++)
        el_multimi.push_back(data[i]);
    for (int i = 0; i < m.dim; i++)
        el_multimi.push_back(m.data[i]);
    Multime m_reuniune(el_multimi);
    return m_reuniune;
}

Multime Multime::operator *(const Multime &m){
    vector<int> vec_intersectie;
    int maxim = data[0];
    for (int i = 1; i < dim; i++)
        if (data[i] > maxim)
            maxim = data[i];
    for (int i = 0; i < m.dim; i++)
        if (m.data[i] > maxim)
            maxim = m.data[i];
    vector<int> frecv(maxim+1);
    for (int i = 0; i < dim; i++)
        frecv[data[i]] ++;
    for (int i = 0; i < m.dim; i++)
        frecv[m.data[i]] ++;
    for (int i = 0; i <= maxim; i++){
        if (frecv[i] == 2)
            vec_intersectie.push_back(i);
    }
    Multime m_intersectie(vec_intersectie);
    return m_intersectie;
}

Multime Multime::operator -(const Multime &m){
    vector<int> vec_diferenta;
    int maxim = data[0];
    for (int i = 1; i < dim; i++)
        if (data[i] > maxim)
            maxim = data[i];
    vector<int> frecv(maxim+1);
    for (int i = 0; i < dim; i++)
        frecv[data[i]] ++;
    for (int i = 0; i < m.dim; i++)
        if (m.data[i] <= maxim)
            frecv[m.data[i]] --;
    for (int i = 0; i < dim; i++)
        if (frecv[data[i]] == 1)
            vec_diferenta.push_back(data[i]);

    Multime m_diferenta(vec_diferenta);
    return m_diferenta;
}

void play();

int main()
{
    //play();

    Multime m1(vector<int>{1,2,3});
    Multime m2 = m1 + m1;

    cout << m2;



    return 0;
    /*
    vector<int> v = {1,2,3};
    Multime m(vector<int>());
    Multime a(v);
    Multime b(v);
    Multime c(v);

    a = b = c = m;

    cout << m;

    m += 4;

    cout << (m+=4);
    */
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
        cout << "\n\n\n1 - creeaza multime\n2 - modifica multime\n3 - operatie intre multimi\n4 - afiseaza multimile\n0 - incheie programul\n";
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
            cout << " Introdu indexul pozitiei de modificat (" << 0 << '-' << multimi.size()-1 << ") :";
            int poz;
            cin >> poz;
            if (poz < 0 || poz >= multimi.size()){
                cout << " Index invalid!\n\n";
                break;
            }
            else{
                cin >> multimi[poz];
            }
            break;
        }
        case 3:
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
        case 4:
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
