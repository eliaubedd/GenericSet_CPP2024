#include "tset.hpp"
#include <iostream>

struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
    //return (a%2==0) && (b%2==1); // Esempio particolare di ordinamento
  }
};

struct is_even {
    bool operator()(int a) const {
        return a % 2 == 0;
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

void testFunzioniGlobali(){

  tset<int, equal_int> a;
  a.add(5);
  a.add(4);
  a.add(5);
  a.add(1);
  a.add(2);
  a.add(3);
  std::cout << "set a: " << a << std::endl;

  //filter out:
  tset<int, equal_int> b = filter_out(a, is_even());
  std::cout << "filter_out(t, is_even()): " << b << std::endl;

  //operator+
  tset<int, equal_int> c;
  c.add(21);
  c.add(4);
  c.add(56);
  c.add(5);
  c.add(7);
  c.add(0);
  c.add(3);
  std::cout << "set a: " << a << std::endl;
  std::cout << "set c: " << c << std::endl;
  tset<int, equal_int> d;
  d = a + c;
  std::cout << "set a+c: " << a+c << std::endl;

  //operator-
  std::cout << "set a-c: " << a-c << std::endl;
}

void testFunzioneSave(){
    tset<std::string, std::equal_to<std::string>> mySet;
    mySet.add("Ciao");
    mySet.add("come");
    mySet.add("va");
    mySet.add("oggi?");
  
    tset<std::string, std::equal_to<std::string>> mySet2;
    mySet.add("Buongiorno,");
    mySet.add("dove");
    mySet.add("stavi");
    mySet.add("ieri?");

    // Salvataggio del set nel file "output.txt"
    save(mySet2, "output.txt");
}

int main(int argc, char *argv[]){



    //testIterator();

    //testFunzioniGlobali();

    testFunzioneSave();




    return 0;
}