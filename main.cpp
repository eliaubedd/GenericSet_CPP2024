#include "tset.hpp"
#include <iostream>

struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
    //return (a%2==0) && (b%2==1); // Esempio particolare di ordinamento
  }
};

int main(int argc, char *argv[]){

    tset<int, equal_int> t;
    t.add(5);
    t.add(4);
    t.add(5);
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(55);
    t.add(55);
    std::cout << t << std::endl;
    t.remove(5);
    t.remove(4);
    t.remove(56);
    t.remove(3);
    std::cout << t << std::endl;
    std::cout << t[2];

    tset<int, equal_int> t2;
    t2.add(1);
    t2.add(2);
    t2.add(55);
    t == t2;

    t2.remove(55);
    t == t2;
    t2.add(56);

    t == t2;




    return 0;
}