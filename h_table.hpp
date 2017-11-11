#pragma once
#include <cstddef>
#include <vector>
#include <iostream>
#include <forward_list>
#include <string>
#include <functional>
#include <stdexcept>

namespace ht{

//====================
// Hash functions
//====================

template<typename TKey,typename TValue>
struct IData{
    TKey key;
    TValue value;
    IData(TKey k,TValue v):key(k),value(v){}
};


template<typename TKey, typename TValue>
class IDictionary{

public:

    //====================
    // Member types
    //====================

    using reference = TValue&;
    using const_reference = const TValue&;
    using pointer = TValue*;
    using const_pointer = const TValue*;
    using size_type = std::size_t;

    //=====================
    // Member functions
    //=====================

    //Constructor
    IDictionary(size_type size = 8):N(0){

        //8 - this minimum size hash-table
        if(size < 8){
            M = 8;
        }else{
            M = size;
        }
        //p = q = 2
        C = (int)(M*2)/3+1; //capacity

        for(size_type i = 0; i < M; ++i){
            table.push_back(std::forward_list< IData<TKey,TValue> >());
        }
    }

    // NEED FORWARD ITERATOR
    //===================================
    //Copy Constructor
    IDictionary(const IDictionary&) = delete;

    //Copy-equal operator
    IDictionary& operator =(const IDictionary&) = delete;

    //Copy-equal move operator
    IDictionary& operator =(IDictionary&&) noexcept = delete;

    //move Constructor
    IDictionary(IDictionary&&) noexcept = delete;
    //===================================

    //hash function
    size_type Hash(TKey k){
        return (M % 2 == 0) ? std::hash<TKey>()(k) % (M-1) : std::hash<TKey>()(k) % M;
    }

    //Add
    void Add(TKey k, TValue v){
        size_type i = Hash(k);
        if(!GetFirst(k)){
            table[i].push_front(IData<TKey,TValue>(k,v));
            N++;
            //resize
            if(N == C){
                Rehash();
            }
        }
    }

    //Remove
    void Remove(TKey k){
        size_type i = Hash(k);
        if(GetFirst(k)){
            table[i].remove_if([k](IData<TKey,TValue> dat){return dat.key == k;});
            N--;
            //resize
            if(N <= C/2){
                Rehash();
            }
        }else{
            throw std::logic_error("not found");
        }
    }

    //Resize hash_table
    void Rehash(size_type new_size = 8){
        std::vector< std::forward_list< IData<TKey,TValue> > > t_table(table);
        size_type m = M;
        if(N == C){
            M *= 2;
        }
        else if(new_size > M || N < new_size){
            M = new_size;
        }
        else{
            if(N <= C/2){
                M /= 2;
            }
        }
        if(M < 8){
           M = m;
        }
        //if something change we rehash
        if(m != M){
            C = (int)(M*2)/3+1;
            N = 0;

            clear(m);

            for(size_type i = 0; i < M; ++i){
                table.push_back(std::forward_list< IData<TKey,TValue> >());
            }

            for(size_type i = 0; i < m; ++i){
                auto it = t_table[i].begin();
                while(it != t_table[i].end()){
                    Add(it->key,it->value);
                    it++;
                }
            }
        }
    }

    bool empty()const noexcept{
        return (N == 0) ? true : false;
    }

    void clear(size_type m) noexcept{
        for(size_type i = 0; i < m; ++i){
                table[i].clear();
            }
        table.clear();
    }

    //Count
    size_type GetCount() const noexcept{
        return N;
    }

    //Capacity
    size_type GetCapacity() const noexcept{
        return C;
    }

    //max size
    size_type Table_size() const noexcept{
        return M;
    }

    reference operator[](TKey k){
        return Get(k);
    }

    //Get
    TValue& Get(TKey key){
        if(GetFirst(key)){
            size_type i = Hash(key);
            auto it = table[i].begin();
            while(it != table[i].end()){
                if(it->key == key){
                    return it->value;
                }
                it++;
            }
        }
        else{
            throw std::logic_error("not found");
        }
    }

    //ContainsKey (hash search)
    //proportional quantity elements in list
    bool GetFirst(TKey key){
        size_type i = Hash(key);
        auto it = table[i].cbegin();
        while(it != table[i].cend()){
            if(it->key == key)
                return true;
            it++;
        }
        return false;
    }

    //consistent search
    //slow method
    bool GetFirst_con(TKey key){
        for(size_type i = 0; i < M; ++i){
            auto it = table[i].cbegin();
            while(it != table[i].cend()){
                if(it->key == key){
                    return true;
                }
                it++;
            }
        }
        return false;
    }

    //text information
    void print() const noexcept{
        for(size_type i = 0; i < M; ++i){
            auto it = table[i].cbegin();
            if(it != table[i].cend()) std::cout<<std::endl;
            while(it != table[i].cend()){
                std::cout<<it->key<<"=>"<<it->value<<' ';
                it++;
            }
        }
    }

    //Destructor
    ~IDictionary(){
        if(!empty())
            clear(M);
        table.shrink_to_fit();
    }

private:
    //quantity elements
    size_type N;

    //capacity
    size_type C;

    //table size
    size_type M;

    //hash table based on forward list
    std::vector< std::forward_list< IData<TKey,TValue> > > table;

};

}
