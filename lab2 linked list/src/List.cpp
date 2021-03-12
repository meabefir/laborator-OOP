#include "List.h"
#include <iostream>

Node::Node(int i, Node *n): info(i), next(n){

}

List::List(): first(nullptr), last(nullptr), size(0)
{

}

std::ostream& operator << (std::ostream& os, Node& n){
    return os << n.info << '\n';
}

List::List(unsigned s, int x): size(s) {
    first = last = new Node(x,nullptr);

    for (int i = 1; i < s; i ++){
        Node *aux = new Node(x,nullptr);
        last->next = aux;
        last = aux;
    }

    /*
    for (int i = 0; i < s; i ++){
        this->push(x);
    }
    */
}

void List::push(int x){
    if (this->size == 0){
        first = last = new Node(x,nullptr);
    } else {
        Node *aux = new Node(x, nullptr);
        this->last->next = aux;
        this->last = aux;
    }
    this->size++;
}

List::List(List &l){
    Node *aux = l.first;
    while (aux != nullptr){
        this->push(aux->info);
        aux = aux->next;
    }
}

List::~List()
{
    Node *aux = first;
    while (aux != nullptr){
        Node *next = aux->next;
        delete aux;
        aux = next;
    }
    size = 0;
    first = last = nullptr;
}

void List::delete_index(unsigned i){
    if (this->size < i || i < 1){
        return;
    }
    if (i == 1){
        Node *to_delete = first;
        first = first->next;
        delete to_delete;
        this->size --;
        return;
    }
    Node *aux = first;
    int j = 0;
    while (j < i-2){
        aux = aux->next;
        j ++;
    }
    Node *to_delete = aux->next;
    aux->next = aux->next->next;
    delete to_delete;
    if (i == this->size){
        this->last = aux;
    }
    this->size --;

    if (this->size == 0)
        first = last = nullptr;
}

void List::delete_value(int x){
    Node* aux = this->first;
    Node* prev;
    while (aux != nullptr && aux->info != x){
        prev = aux;
        aux = aux->next;
    }
    if (aux == nullptr)
        return;
    if (aux == this->first){
        Node* to_delete = this->first;
        this->first = this->first->next;
        delete to_delete;
    } else {
        if (aux == this->last){
            this->last = prev;
        }
        Node* to_delete = aux;
        prev->next = to_delete->next;
        delete to_delete;
    }
    this->size --;

    if (this->size == 0){
        first = last = nullptr;
    }
}

void List::print(){
    if (this->size == 0){
        std::cout << " List is empty!\n";
        return;
    }
    Node *aux = this->first;
    while (aux != nullptr){
        std::cout << aux->info << ' ';
        aux = aux->next;
    }
    std::cout << '\n';
}

unsigned List::get_size(){
    return this->size;
}

Node& List::get_at(unsigned i){
    if (i > this->size || i < 1)
        throw("bad index");
    Node* aux = this->first;
    unsigned j = 1;
    while (j < i){
        aux = aux->next;
        j++;
    }
    return *aux;
}

Node& List::get_max(){
    Node* aux = this->first;
    Node* maxim_p = aux;
    int maxim = aux->info;
    aux = aux->next;

    while (aux != nullptr){
        if (aux->info > maxim){
            maxim = aux->info;
            maxim_p = aux;
        }
        aux = aux->next;
    }
    return *maxim_p;
}

int List::get_first(){
    return first->info;
}

int List::get_last(){
    return last->info;
}

