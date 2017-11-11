#include "h_table.hpp"

#include <iostream>
#include <cassert>
#include <chrono>
//#include <cctype>
//#include <unordered_map>
//#include <boost/lexical_cast.hpp>

using namespace std;
using namespace ht;

//test functions
void Constructor(){
    IDictionary<string,int> d1;
    IDictionary<int,int> d2(20);
    IDictionary<float,string> d3{2};

    assert(d1.GetCount() == 0);
    assert(d1.GetCapacity() == 6);
    assert(d1.Table_size() == 8);
    assert(d2.Table_size() == 20);
    assert(d3.Table_size() == 8);
    assert(d3.GetCapacity() == 6);

    cout<<"1_OK"<<endl;
}

void Add(){
    IDictionary<string,int> d1;
    IDictionary<int,int> d2(20);
    IDictionary<float,string> d3{2};

    d1.Add("a",2);
    d1.Add("go",18);
    d1.Add("a",321);


    d2.Add(56,120);
    d2.Add(42,2130);
    d2.Add(41284,23);

    d3.Add(5612.72,"priv");
    d3.Add(42.3,"good");
    d3.Add(42.3,"realy");

    assert(d1["a"] == 2);
    assert(d1["go"] == 18);

    assert(d2[56] == 120);
    assert(d2[42] == 2130);
    assert(d2[41284] == 23);

    assert(d3[5612.72] == "priv");
    assert(d3[42.3] == "good");

    cout<<"2_OK"<<endl;
}

void Remove(){
    IDictionary<string,int> d1;
    IDictionary<int,int> d2(20);
    IDictionary<float,string> d3{2};

    d1.Add("a",2);
    d1.Add("go",18);
    d1.Add("a",321);


    d2.Add(56,120);
    d2.Add(42,2130);
    d2.Add(41284,23);

    d3.Add(5612.72,"priv");
    d3.Add(42.3,"good");
    d3.Add(42.3,"realy");

    d1.Remove("a");
    d2.Remove(42);
    d3.Remove(42.3);

    assert(d1.GetCount() == 1);
    assert(d2.GetCount() == 2);
    assert(d3.GetCount() == 1);

    cout<<"3_OK"<<endl;
}

void Rehash(){
    IDictionary<string,int> d1;

    assert(d1.Table_size() == 8);

    d1.Add("a",2);
    d1.Add("i",18);
    d1.Add("u",321);
    d1.Add("jk",2);
    d1.Add("o",18);
    d1.Add("g",321);
    d1.Add("s",2);
    d1.Add("go",18);

    assert(d1.Table_size() == 16);
    assert(d1.GetCount() == 8);
    assert(d1.GetCapacity() == (int)(2*16)/3+1);
    assert(d1["s"] == 2);
    assert(d1["go"] == 18);

    d1.Rehash(5); //nothing because 5 < 16
    d1.Rehash(20);

    assert(d1.Table_size() == 20);
    assert(d1.GetCount() == 8);
    assert(d1.GetCapacity() == (int)(2*20)/3+1);
    assert(d1["s"] == 2);
    assert(d1["o"] == 18);

    cout<<"4_OK"<<endl;
}

void Empty(){
    IDictionary<string,int> d1;

    assert(d1.empty() == true);
    d1.Add("s",2);
    assert(d1.empty() == false);

    cout<<"5_OK"<<endl;
}

void GetCount(){
    IDictionary<string,int> d1;

    assert(d1.GetCount() == 0);
    d1.Add("5",2);
    assert(d1.GetCount() == 1);

    cout<<"6_OK"<<endl;
}

void GetCapacity(){
    IDictionary<string,int> d1;

    //formula -> (int)(2*table_size)/3 + 1;

    d1.Add("a",2);
    d1.Add("go",18);
    d1.Add("ag",321);
    d1.Add("as",321);

    assert(d1.GetCapacity() == (int)(2*8)/3 + 1);

    d1.Add("ax",2);
    d1.Add("goh",18);
    d1.Add("agf",3231);
    d1.Add("asgb",321);

    //because p = q = 2
    assert(d1.GetCapacity() == (int)(2*2*8)/3 + 1);

    cout<<"7_OK"<<endl;
}

void Table_size(){
    IDictionary<string,int> d1;
    assert(d1.Table_size() == 8);
    d1.Rehash(45);
    assert(d1.Table_size() == 45);

    d1.Rehash(9);
    d1.Add("as",4);
    d1.Add("f",8);
    d1.Add("v",7);
    d1.Add("b",6);
    d1.Add("n",5);
    d1.Add("h",2);
    d1.Add("j",1);
    d1.Add("y",3);
    d1.Add("r",2);

    assert(d1.Table_size() == 18);

    cout<<"8_OK"<<endl;
}

void operator_Get(){
    IDictionary<string,int> d1;
    d1.Add("h",2);
    d1.Add("j",1);
    d1.Add("y",3);
    d1.Add("r",2);

    assert(d1["h"] == 2);
    assert(d1["y"] == 3);
    assert(d1["r"] == 2);

    cout<<"9_OK"<<endl;
}

void Get(){
   IDictionary<string,int> d1;
   d1.Add("h",2);
   d1.Add("j",1);
   d1.Add("y",3);
   d1.Add("r",2);

   assert(d1.Get("h") == 2);
   assert(d1.Get("r") == 2);
   assert(d1.Get("y") == 3);

   cout<<"10_OK"<<endl;
}

void GetFirst(){
   IDictionary<string,int> d1;
   d1.Add("h",2);
   d1.Add("j",1);
   d1.Add("y",3);
   d1.Add("y",2);
   d1.Add("g",6);

   assert(d1.GetFirst("g") == true);
   assert(d1.GetFirst("j") == true);
   assert(d1.GetFirst("ksa") == false);
   assert(d1.GetFirst("asg") == false);
   assert(d1.GetFirst("h") == true);

   cout<<"11_OK"<<endl;
}

void GetFirst_con(){
   IDictionary<string,int> d1;
   d1.Add("h",2);
   d1.Add("j",1);
   d1.Add("y",3);
   d1.Add("y",2);
   d1.Add("g",6);

   assert(d1.GetFirst_con("g") == true);
   assert(d1.GetFirst_con("j") == true);
   assert(d1.GetFirst_con("ksa") == false);
   assert(d1.GetFirst_con("asg") == false);
   assert(d1.GetFirst_con("h") == true);

   cout<<"12_OK"<<endl;
}

int main()
{

try{

//cout<<"test time"<<endl;
 Constructor();
 Add();
 Remove();
 Rehash();
 GetCapacity();
 Table_size();
 operator_Get();
 Get();
 GetFirst();
 GetFirst_con();
 cout<<endl;


//command interface
/*cout<<"COMMAND LINE>>:"<<endl;
cout<<endl<<endl<<endl<<endl;
char ch;

cout<<"table-size: "<<endl;
string ss;
cin>>ss;
IDictionary<string,int> dict(boost::lexical_cast<size_t>(ss));

do{
    cout<<endl<<"write number:"<<endl;
    cout<<"1 - Add element"<<endl;
    cout<<"2 - Remove element"<<endl;
    cout<<"3 - Print all table"<<endl;
    cout<<"4 - GetCount (quantity elements)"<<endl;
    cout<<"5 - GetCapacity"<<endl;
    cout<<"6 - Get key element"<<endl;
    cout<<"7 - GetFirst (search key element)"<<endl;
    cout<<"8 - Rehash table"<<endl;
    cout<<"9 - Table-size"<<endl;
    cout<<"a - Add massive in table"<<endl;
    cout<<"b - compare two search algorithms"<<endl;
    cout<<"0 - END"<<endl<<endl;
    cin>>ch;
    switch(ch){
    case '1':{
        cout<<"write key (string) => ";
        string key;
        cin>>key;
        string value;
        cout<<"and write value (int) => ";
        cin>>value;
        dict.Add(key,boost::lexical_cast<int>(value));
        break;
    }
    case '2':{
        cout<<"remove element by key (string) => ";
        string key;
        cin>>key;
        dict.Remove(key);
        cout<<'['<<key<<']'<<" - delete"<<endl;
        break;
    }
    case '3':{
        cout<<endl;
        dict.print();
        cout<<endl;
        break;
    }
    case '4':{
        cout<<endl;
        cout<<"Count : "<<dict.GetCount()<<endl;
        cout<<endl;
        break;
    }
    case '5':{
        cout<<endl;
        cout<<"Capacity : "<<dict.GetCapacity()<<endl;
        cout<<endl;
        break;
    }
    case '6':{
        cout<<endl;
        cout<<"write key (string) => ";
        string key;
        cin>>key;
        cout<<"Element : "<<dict[key]<<endl;
        cout<<endl;
        break;
    }
    case '7':{
        cout<<"you can write < 1 > if want use consistent search"<<endl;
        cout<<"or write < 2 > and use hash search"<<endl;
        char p;
        cin>>p;
        string key;
        switch(p){
        case'1':{
            cout<<"you choose consistent search : "<<endl;
            cout<<"write key (string) => ";
            cin>>key;
            auto start_time = std::chrono::steady_clock::now();
            dict.GetFirst_con(key);
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
            std::cout << elapsed_ns.count() << " ns\n";
            break;
        }
        case '2':{
            cout<<"you choose hash search : "<<endl;
            cout<<"write key (string) => ";
            cin>>key;
            auto start_time = std::chrono::steady_clock::now();
            dict.GetFirst(key);
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
            std::cout << elapsed_ns.count() << " ns\n";
            break;
        }
       }
        break;
    }
    case '8':{
        cout<<"write new size hash-table"<<endl;
        string ss;
        cin>>ss;
        dict.Rehash(boost::lexical_cast<size_t>(ss));
        cout<<endl;
        break;
    }
    case '9':{
        cout<<endl;
        cout<<"size : "<<dict.Table_size()<<endl;
        cout<<endl;
        break;
    }
    case 'a':{
        cout<<"if you want add massive write ranges : "<<endl;
        string left,right,kol;
        cout<<"h < f(x) < p"<<endl;
        cout<<"h = ";
        cin>>left;
        cout<<"p = ";
        cin>>right;
        cout<<"and his quantity : 10";
        vector<int> mas_val;
        for(int i = 0; i < 10; ++i){
            mas_val.push_back((std::rand()%boost::lexical_cast<int>(right)+boost::lexical_cast<int>(left)));
        }
        vector<string> mas_key = {"a","b","c","d","h","y","q","i","p","x"};
        for(int i = 0; i < 10; ++i){
            dict.Add(mas_key[i],mas_val[i]);
        }
        break;
    }
    case 'b':{
        cout<<"write key (string) => ";
        string key;
        cin>>key;

        //consistent search
        auto start_time1 = std::chrono::steady_clock::now();
        dict.GetFirst_con(key);
        auto end_time1 = std::chrono::steady_clock::now();
        auto elapsed_ns1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time1 - start_time1);
        std::cout <<"first =>"<< elapsed_ns1.count() << " ns\n";

        //hash search

        auto start_time2 = std::chrono::steady_clock::now();
        dict.GetFirst(key);
        auto end_time2 = std::chrono::steady_clock::now();
        auto elapsed_ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time2 - start_time2);
        std::cout <<"second =>"<< elapsed_ns2.count() << " ns\n";
    }
}
}while(ch != '0');
*/
}catch(exception& oop){
    cout<<oop.what()<<endl;
}

    return 0;
}
