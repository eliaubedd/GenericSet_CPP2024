#include "tset.hpp"
#include <iostream>

struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
  }
};

struct is_even {
    bool operator()(int a) const {
        return a % 2 == 0;
    }
};

/**
 * @brief Test dei metodi su int set
 * 
 * Test dei metodi su int set
 * 
 */
void testIntSet(){
    tset<int, equal_int> t;

    std::cout << "************** Test metodi su un set di interi **************" << std::endl;

    std::cout << "Inserimento dei valori: 5, 4, 5, 1, 2, 55, 55" << std::endl;
    t.add(5);
    t.add(4);
    t.add(5);
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(55);
    t.add(55);

    std::cout << "Stampa del set con operator<< dopo add: " << std::endl;
    std::cout << t << std::endl;
    assert(t.getSize() == 6);
    assert(t.contains(5));
    assert(t.contains(4));
    assert(t.contains(1));
    assert(t.contains(2));
    assert(t.contains(3));
    assert(t.contains(55));

    std::cout << "Rimozione dei valori: 5, 4, 56, 3" << std::endl;
    t.remove(5);
    t.remove(4);
    t.remove(56);
    t.remove(3);

    std::cout << "Stampa del set con operator<< dopo remove: " << std::endl;
    std::cout << t << std::endl;
    assert(t.getSize() == 3);
    assert(!t.contains(5));
    assert(!t.contains(4));
    assert(!t.contains(56));
    assert(!t.contains(3));
  
    std::cout << "Stampa con iteratori: " << std::endl;
    tset<int, equal_int>::const_iterator ib, ie;
    for(ib=t.begin(),ie=t.end(); ib!=ie; ++ib){
        std::cout<<*ib<<std::endl;
    }

    std::cout << "Accesso all'iesimo elemento con operatore []: ";
    for(unsigned int i = 0; i < t.getSize(); ++i){
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Confronto con metodo == con set: {1, 2, 55}: ";
    tset<int, equal_int> t2;
    t2.add(1);
    t2.add(2);
    t2.add(55);
    std::cout << (t == t2) << std::endl;
    assert(t==t2);

    std::cout << "Confronto con metodo == con set: {1, 2, 56}: ";
    t2.remove(55);
    t2.add(56);
    std::cout << (t == t2) << std::endl;
    assert(!(t==t2));


    std::cout << "Costruzione set attraverso iteratori: " << std::endl;
    int array[] = {1, 2, 3, 4, 5, 4};
    tset<int, equal_int> tas(array, array+5);
    std::cout << tas << std::endl;
    assert(tas.getSize() == 5);
    assert(tas.contains(1));
    assert(tas.contains(2));
    assert(tas.contains(3));
    assert(tas.contains(4));
    assert(tas.contains(5));
}

struct equal_string {
  bool operator()(const std::string &a, const std::string &b) const {
    return (a==b);
  } 
};

/**
 * @brief Test dei metodi su std::string set
 * 
 * Test dei metodi su std::string set
 * 
 */
void testStringSet(){
  tset<std::string, equal_string> ts;

    std::cout << "************** Test metodi su un set di string **************" << std::endl;

    std::cout << "Inserimento dei valori: 'ciao', 'come', 'stai', 'oggi', 'ciao'" << std::endl;
    ts.add("ciao");
    ts.add("come");
    ts.add("stai");
    ts.add("oggi");
    ts.add("ciao");

    std::cout << "Stampa del set con operator<< dopo add: " << std::endl;
    std::cout << ts << std::endl;
    assert(ts.getSize() == 4);
    assert(ts.contains("ciao"));
    assert(ts.contains("come"));
    assert(ts.contains("stai"));
    assert(ts.contains("oggi"));
 

    std::cout << "Rimozione dei valori: 'ciao', 'stai'" << std::endl;
    ts.remove("ciao");
    ts.remove("stai");
  

    std::cout << "Stampa del set con operator<< dopo remove: " << std::endl;
    std::cout << ts << std::endl;
    assert(ts.getSize() == 2);
    assert(!ts.contains("ciao"));
    assert(!ts.contains("stai"));
  
    std::cout << "Stampa con iteratori: " << std::endl;
    tset<std::string, equal_string>::const_iterator ib, ie;
    for(ib=ts.begin(),ie=ts.end(); ib!=ie; ++ib){
        std::cout<<*ib<<std::endl;
    }

    std::cout << "Accesso all'iesimo elemento con operatore []: ";
    for(unsigned int i = 0; i < ts.getSize(); ++i){
        std::cout << ts[i] << " ";
    }
    std::cout << std::endl;
    
    
    std::cout << "Confronto con metodo == con set: {'come', 'oggi'}: ";
    tset<std::string, equal_string> t2;
    t2.add("come");
    t2.add("oggi");
    std::cout << (ts == t2) << std::endl;
    assert(ts==t2);

    std::cout << "Confronto con metodo == con set: {'come', 'ieri'}: ";
    t2.remove("oggi");
    t2.add("ieri");
    std::cout << (ts == t2) << std::endl;
    assert(!(ts==t2));


    std::cout << "Costruzione set attraverso iteratori: " << std::endl;
    std::string array[] = {"ciao", "come", "stai", "oggi"};
    tset<std::string, equal_string> tas(array, array+4);
    std::cout << tas << std::endl;
    assert(tas.getSize() == 4);
    assert(tas.contains("ciao"));
    assert(tas.contains("come"));
    assert(tas.contains("stai"));
    assert(tas.contains("oggi"));
}

//TEST POINT 
struct point {
  int x; ///< coordinata x del punto
  int y; ///< coordinata y del punto

  point() : x(0), y(0) {}
  point(int xx, int yy) : x(xx), y(yy) {}
};

/**
  Ridefinizione dell'operatore di stream << per un point.
  Necessario per l'operatore di stream della classe ordered_list.
*/
std::ostream &operator<<(std::ostream &os, const point &p) {
  std::cout<<"("<<p.x<<","<<p.y<<")";
  return os;
}

struct equal_point {
  bool operator()(const point &p1, const point &p2) const {
    return (p1.x==p2.x) && (p1.y==p2.y);
  } 
};

/**
 * @brief Test dei metodi su point set
 * 
 * Test dei metodi su point set
 * 
 */
void testPointSet(){

    tset<point, equal_point> tp;

    std::cout << "************** Test metodi su un set di point **************" << std::endl;
    
    std::cout<<"Insertimento dei valori (1,5), (3,4), (5,1), (0,0), (5,1)"<<std::endl;
    tp.add(point(1,5));
    tp.add(point(3,4));
    tp.add(point(5,1));
    tp.add(point(0,0));
    tp.add(point(5,1));

    std::cout << "Stampa del set con operator<< dopo add: " << std::endl;
    std::cout << tp << std::endl;
    assert(tp.getSize() == 4);
    assert(tp.contains(point(1,5)));
    assert(tp.contains(point(3,4)));
    assert(tp.contains(point(5,1)));
    assert(tp.contains(point(0,0)));

    std::cout<<"Rimozione dei valori (1,5), (0,0)" << std::endl;
    tp.remove(point(1,5));
    tp.remove(point(0,0));
    assert(tp.getSize() == 2);
    assert(!(tp.contains(point(1,5))));
    assert(!(tp.contains(point(0,0))));

    std::cout << "Stampa del set con operator<< dopo remove: " << std::endl;
    std::cout << tp << std::endl;
    

    std::cout << "Stampa con iteratori: " << std::endl;
    tset<point, equal_point>::const_iterator ib, ie;
    for(ib=tp.begin(),ie=tp.end(); ib!=ie; ++ib){
        std::cout<<*ib<<std::endl;
    }

    std::cout << "Accesso all'iesimo elemento con operatore []: ";
    for(unsigned int i = 0; i < tp.getSize(); ++i){
        std::cout << tp[i] << " ";
    }
    std::cout << std::endl;
       
    tset<point, equal_point> tp2;
    tp2.add(point(1,5));
    tp2.add(point(3,4));
    tp2.add(point(5,1));
    tp2.add(point(0,0));
    tp2.add(point(5,1));

    std::cout << "Confronto con metodo == con set: (1,5), (3,4), (5,1), (0,0): ";
    std::cout << (tp == tp2) << std::endl;
    assert(!(tp == tp2));

    tp2.remove(point(1,5));
    tp2.remove(point(0,0));
    std::cout << "Confronto con metodo == con set: (3,4), (5,1): ";
    std::cout << (tp == tp2) << std::endl;
    assert(tp == tp2);

    std::cout << "Costruzione set attraverso iteratori: " << std::endl;
    point array[] = {point(1,1), point(4,2), point(0,0), point(5,4), point(0,0)};
    tset<point, equal_point> tas(array, array+5);
    std::cout << tas << std::endl;
    assert(tas.getSize() == 4);
    assert(tas.contains(point(1,1)));
    assert(tas.contains(point(4,2)));
    assert(tas.contains(point(0,0)));
    assert(tas.contains(point(5,4)));
}

/**
 * @brief Test dei metodi di iteratori
 * 
 * Test dei metodi di iteratori
 * 
 */
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

/**
 * @brief Test dei metodi delle funzioni globali
 * 
 * Test dei metodi delle funzioni globali
 * 
 */
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

/**
 * @brief Test funzione save
 * 
 * Test funzione save
 * 
 */
void testFunzioneSave(){
    tset<std::string, std::equal_to<std::string>> mySet;
    mySet.add("Ciao");
    mySet.add("come");
    mySet.add("va");
    mySet.add("oggi?");
  
    tset<std::string, std::equal_to<std::string>> mySet2;
    mySet2.add("Buongiorno,");
    mySet2.add("dove");
    mySet2.add("stavi");
    mySet2.add("ieri?");

    // Salvataggio del set nel file "output.txt"
    save(mySet2, "output.txt");
}

int main(int argc, char *argv[]){

    testIntSet();

    testStringSet();

    testPointSet();

    testIterator();

    testFunzioniGlobali();

    testFunzioneSave();

    return 0;
}