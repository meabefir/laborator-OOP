#include <iostream>

using namespace std;

class Nod{
    char info;
    Nod* next;

public:
    Nod(){
        info = 0;
        next = nullptr;
    }

    Nod(char c){
        info = c;
        next = nullptr;
    }

    ~Nod(){
        cout << "nod distrus \n";
        delete next;
    }

    void set_info(char c){
        info = c;
    }

    void set_next(Nod *n){
        next = n;
    }

    char get_info(){
        return info;
    }

    Nod* get_next(){
        return next;
    }

    char get_next_info(){
        if (next != nullptr)
            return next->info;
    }
};

class Stiva : public Nod{
    Nod* varf;

public:
    Stiva(){
        varf = nullptr;
    }
    ~Stiva(){
        delete varf;
    }
    Stiva(Stiva &s){
        s.varf = varf;
    }

    void push(Nod* n){
        n->set_next(varf);
        varf = n;
    }

    Nod* pop(){
        Nod* c_varf = varf;
        varf = varf->get_next();
        c_varf->set_next(nullptr);
        //char i_varf = c_varf->get_info();
        //delete c_varf;
        return c_varf;
    }

    char top(){
        return varf->get_info();
    }

    bool isempty(){
        if (varf == nullptr)
            return true;
        else
            return false;
    }

    friend operator<<(std::ostream& os,Stiva &s){
        while (!s.isempty()){
            cout << s.top() << ' ';
            s.pop();
        }
    }

    Stiva operator - (Stiva s){
        Stiva new_s;
        while (!(this->isempty() || s.isempty())){
            if (this->top() > s.top()){
                new_s.push(new Nod(this->varf->get_info()));
            } else {
                new_s.push(new Nod(s.varf->get_info()));
            }
        }
        return new_s;
    }
};

int main()
{
    Stiva s1;
    Stiva s2;

    s1.push(new Nod('e'));
    s1.push(new Nod('x'));
    s1.push(new Nod('a'));
    s1.push(new Nod('m'));
    s1.push(new Nod('e'));
    s1.push(new Nod('n'));

    s2.push(new Nod('p'));
    s2.push(new Nod('o'));
    s2.push(new Nod('o'));
    s2.push(new Nod('l'));
    s2.push(new Nod('a'));
    s2.push(new Nod('b'));
    s2.push(new Nod('o'));
    s2.push(new Nod('r'));
    s2.push(new Nod('a'));
    s2.push(new Nod('t'));
    s2.push(new Nod('o'));
    s2.push(new Nod('r'));

    cout << s1;
    cout << s2;

    Stiva s3;
    s3 = s1-s2;
    cout << '\n';
    cout << s3;

    return 0;
}
