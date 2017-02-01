#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

//виды оберток

//перевод чего угодно в строку

template<typename t>
string to_string(t info)
{
    stringstream ss;
    ss<<info;
    return ss.str();
}

//из строки в любой тип
template<typename t>
void to_type(string joke,t &T)
{
    stringstream ss;
    ss<<joke;
    ss>>T;
}

template<typename t>
class flist
{
private:
    class node
    {
    public:
        t info;
        node* next;
        node(t k):info(k),next(nullptr){}
    };
    node* head = nullptr;
    node* current = nullptr;
public:

    flist()
    {
        head = current = nullptr;
    }

    flist(t data)
    {
        if(!head)
            {
                head = new node(data);
                current = head;
            }
    }

    void push_back(t data)
    {
        node* add = new node(data);

        if(!head){
            head = add;
            current = head;
            return;
        }
        if(!head->next){
            current = add;
            head->next = current;
            return;
        }
        else{
            current->next = add;
            current = current->next;
        }
    }

    void pop_back()
    {
        if(!head && !current)
            {
                cout<<"forward list is empty"<<endl;
                return;
            }
        if(current == head){
            delete head;
            delete current;
            head = current = nullptr;
            return;
        }
        else{
            node* prev = head;
            while(prev->next != current){
                prev = prev->next;
            }
            delete current;
            current = prev;
        }
    }

    node* find(t data)
    {
        node* ptr = head;
        if(!head && !current){
            goto m1;
        }
        while(ptr != current->next)
            {
                if(ptr->info == data){
                    return ptr;
                }
                ptr = ptr->next;
            }
        m1:
        return nullptr;
    }

    void pop(t data)
    {
        node* ptr = find(data);
        if(!ptr){
           cout<<"this element absent or forward list is empty"<<endl;
           return;
        }
        if(ptr == head){
            if(!head->next){
                pop_back();
            }
            else{
                ptr = ptr->next;
                delete head;
                head = ptr;
            }
        }
        else{
            if(!ptr->next){
                pop_back();
            }
            else{
                node* current = head;
                while(current->next != ptr)
                    {
                        current = current->next;
                    }
                current->next = ptr->next;
                delete ptr;
            }
        }
    }

    void print()
    {
        node* ptr = head;
        if(!head) return;
        while(ptr != current->next)
            {
                cout<<ptr->info<<endl;
                ptr = ptr->next;
            }
    }

    t h_inf()const
    {
        return head->info;
    }

    t get_data(t data)
    {
        node* ptr = find(data);
        return ptr->info;
    }

};

//Хэш таблица на основе односвязного списка
template<typename T>
class hash_table
{
private:
    const int ss;
    vector< flist<T> > mas;
    int hash_func(int data)
    {
        return (data%ss);
    }

    flist<T> h_find(T data)
    {
        return mas[hash_func(data)];
    }

public:

    hash_table(unsigned int s):ss(s)
    {
        for(int i = 0; i < ss; i++){
            mas.push_back(flist<T>());
        }
    }

    void push(T data)
    {
        int idx = hash_func(data);
        mas[idx].push_back(data);
    }

    T find(T data)
    {
        flist<T> ptr = h_find(data);
        return ptr.get_data(data);
    }

    void pop(T data)
    {
        flist<T> ptr = h_find(data);
        ptr.pop(data);
    }

    void print()
    {
        for(int i = 0; i < ss; i++){
            mas[i].print();
        }
    }
};

int main()
{

hash_table<int> mas(12);
for(int i = 0; i < 25; i++)
    {
        mas.push(rand()%25+100);
    }
    mas.print();


    return 0;
}
