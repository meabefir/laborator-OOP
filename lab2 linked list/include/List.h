#ifndef LIST_H
#define LIST_H

#include <iostream>

class List;

class Node{
    int info;
    Node* next;

public:
    Node(int, Node*);
    friend class List;
    friend std::ostream& operator <<(std::ostream&, Node&);
};

class List
{
    Node *first, *last;
    unsigned size;

public:
    List();
    List(unsigned s, int x);
    List(List &l);
    ~List();
    unsigned get_size();
    Node& get_at(unsigned i);
    Node& get_max();
    void push(int x);
    void delete_index(unsigned i);
    void delete_value(int x);
    void print();
    int get_first();
    int get_last();
};

#endif // LIST_H
