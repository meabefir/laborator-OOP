#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Multime{
    int *data, alocate, dim;

public:
    Multime(){
        dim = 0;
        alocate = 10;
        data = new int[alocate];
    }

    Multime(const Multime &m){
        cout << " Constr\n";
        dim = m.dim;
        alocate = m.alocate;
        data = new int[alocate];
        for (int i = 0; i < m.dim; i++)
            data[i] = m.data[i];
    }

    Multime operator =(const Multime &m){
        cout << " operator\n";
        vector<int> el;
        for (int i = 0; i < m.dim; i++)
            el.push_back(m.data[i]);
        vector_to_multime(el);
    }

    ~Multime(){
        delete []data;
    }

    void vector_to_multime(vector<int> v){
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
            cout << " Aloca extra spatiu \n";
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
            cout << " Spatiul este indeajuns \n";
            dim = new_dim;
            int k = 0;
            for (int i = 0; i <= maxim; i++)
                if (frecv[i] == 1)
                    data[k++] = i;
        }
    }

    friend std::ostream& operator << (std::ostream& os, Multime& m){
        if (m.dim == 0){
            cout << " Multimea este vida. \n";
            return os;
        }
        for (int i = 0; i < m.dim; i++)
            cout << m.data[i] << ' ';
        return os << '\n';
    }

    Multime operator +(Multime &m){
        vector<int> el_multimi;
        for (int i = 0; i < dim; i++)
            el_multimi.push_back(data[i]);
        for (int i = 0; i < m.dim; i++)
            el_multimi.push_back(m.data[i]);
        Multime m_reuniune;
        m_reuniune.vector_to_multime(el_multimi);
        return m_reuniune;
    }

    Multime operator *(Multime &m){
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
        Multime m_intersectie;
        m_intersectie.vector_to_multime(vec_intersectie);
        return m_intersectie;
    }

    Multime operator -(Multime &m){
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
        Multime m_diferenta;
        m_diferenta.vector_to_multime(vec_diferenta);
        return m_diferenta;
    }
};

int main()
{
    Multime a,b,c;

    vector<int> v{1,2,3,4,4,4,5,6,7,7,7,8};
    vector<int> v2{5,5,6,6,7,8,9,10,11,12,13,14,14};
    vector<int> v3{100,200,300,400};

    a.vector_to_multime(v);
    b.vector_to_multime(v2);
    c.vector_to_multime(v3);

    cout << a;
    cout << b;
    cout << c;

    Multime r = a - b;

    //Multime r = b + c * a;

    cout << r;

    return 0;
}
