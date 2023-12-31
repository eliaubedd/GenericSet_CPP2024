#include "tset.hpp"
#include <iostream>

struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
    //return (a%2==0) && (b%2==1); // Esempio particolare di ordinamento
  }
};

void testACaso(){
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
}

void testIterator() {
    tset<int, equal_int> mySet;

    // Aggiungi alcuni valori al set
    mySet.add(5);
    mySet.add(3);
    mySet.add(8);

    std::cout << "Contenuto del set tramite iteratore:" << std::endl;
    for (tset<int, equal_int>::const_iterator it = mySet.begin(); it != mySet.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Verifica di disuguaglianza tra iteratori
    tset<int, equal_int>::const_iterator it1 = mySet.begin();
    tset<int, equal_int>::const_iterator it2 = mySet.begin();
    ++it2; // Incremento it2 per renderlo diverso da it1

    std::cout << "it1 != it2: " << (it1 != it2) << std::endl;

    // Verifica di uguaglianza tra iteratori
    tset<int, equal_int>::const_iterator it3 = mySet.begin();
    tset<int, equal_int>::const_iterator it4 = mySet.begin();

    std::cout << "it3 == it4: " << (it3 == it4) << std::endl;
}


int main(int argc, char *argv[]){



    testIterator();




    return 0;
}