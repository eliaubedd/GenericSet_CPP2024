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
    

    return 0;
}