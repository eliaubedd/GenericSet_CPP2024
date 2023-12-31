/**
  @file tset.hpp

  @brief File header della classe tset templata

  File di dichiarazioni/definizioni della classe tset templata
*/

#ifndef TSET_HPP
#define TSET_HPP
#include <iostream>
#include <ostream>
#include <cassert>

/**
  @brief Classe Set templata

  Classe generica che rappresenta una collezione di dati di 
  tipo T che non può contenere duplicati ... RIGUARDA
*/
template <typename T, typename Equal>
class tset {

public:
    typedef unsigned int size_type; ///< Tipo di dato per la dimensione dell'array
    typedef T value_type; ///< Tipo di dato per il generico tipo T

private: 
    size_type _size; ///< Dimensione dell'array
    size_type _capacity; ///< Capacità dell'array
    value_type * _darr;  ///< Puntatore all'array di dati di tipo T

    Equal _eql; ///< funtore per l'uguaglianza tra dati T

public: 
    /**
        @brief Costruttore di default

        1° METODO FONDAMENTALE DELLE CLASSI
        Construttore di default che inizializza il 
        dbuffer ad un array dinamico vuoto.

        @post _size == 0
        @post _capacity == 0
        @post _darr == nullptr
    */
    tset() : _size(0), _capacity(0), _darr(nullptr){
        #ifndef NDEBUG 
        std::cout<<"tset::tset()"<<std::endl;
        #endif
    }

    /**
        @brief Distruttore

        2° METODO FONDAMENTALE DELLE CLASSI
        IL distruttore della classe rimuove le eventuali risorse
        richieste dall'oggetto.

        @post _size == 0
        @post _capacity == 0
        @post _darr == nullptrr
    */
    ~tset() {
        delete[] _darr;

        _darr = nullptr;
        _size = 0;
        _capacity = 0;

        #ifndef NDEBUG 
        std::cout<<"tset::~tset()"<<std::endl;
        #endif   
    }

    /**
        @brief Costruttore di copia (Copy constructor)

        3° METODO FONDAMENTALE DELLE CLASSI
        Crea un tset a partire da un altro tset

        @param other tset sorgente

        @post _size == other._size
        @post _capacity == other._capacity
        @post _darr[i] == other._darr[i]
    */
    tset(const tset &other) : _darr(nullptr), _size(0), _capacity(0){
        _darr = new value_type[other._capacity];

        try{
            for(size_type i = 0; i < other._size; ++i){
                _darr[i] = other._darr[i];
            }
        }
        catch(...){
            delete [] _darr;
            _darr = nullptr;
            throw;
        }

        _size = other._size;
        _capacity = other._capacity;
        

        #ifndef NDEBUG 
        std::cout<<"tset::tset(const tset &other)"<<std::endl;
        #endif
    }

    /**
        @brief Operatore di assegnamento

        4° METODO FONDAMENTALE DELLE CLASSI
        Operatore che compia il contenuto di un dbuffer
        nel dbuffer corrente.

        @param other tset sorgente

        @return reference a this

        @post _size == other._size
        @post _capacity == other._capacity
        @post _darr[i] == other._darr[i]
    */
    tset& operator=(const tset &other){
        if(this != &other){
            tset tmp(other);
            this -> swap(tmp);
        }

        #ifndef NDEBUG 
        std::cout<<"tset::operator=(const tset &other)"<<std::endl;
        #endif   

        return *this;
    }
    
    /**
        @brief Metodo swap

        Metodo che scambia lo stato di other con quello di this.

        @param other dbuffer con cui scambiare lo stato

        @post this->_size == other._size
        @post this->_buffer == other._buffer
        @post other._size == this->_size
        @post other._buffer == this->other._buffer
    */  
    void swap(tset &other){
        std::swap(this->_size, other._size);
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_darr, other._darr); 
        std::swap(this->_eql,other._eql);

        #ifndef NDEBUG 
        std::cout<<"void swap(tset &other)"<<std::endl;
        #endif  
    }

    /**
        @brief Metodo add

        Aggiunge un elemento al set mantenendo la proprietà del
        non contenere duplicati

        @param value valore da inserire nella lista

        @return true se l'elemento è stato inserito correttamente, false altrimenti
    */
    bool add(const value_type &value){
        if(!contains(value)){
            if(_size == _capacity){
                _capacity += 5;
                value_type* newDarr = new value_type[_capacity];

                try{
                    for(size_type i = 0; i < _size; ++i){
                        newDarr[i] = _darr[i];
                    }
                }
                catch(...){
                    delete [] newDarr;
                    newDarr = nullptr;
                    throw;
                }

                delete [] _darr;
                _darr = newDarr;
            }
            _darr[_size++] = value;

            #ifndef NDEBUG 
            std::cout<<"bool add(true)"<<std::endl;
            #endif 

            return true;
        }
        else{
            #ifndef NDEBUG 
            std::cout<<"bool add(false)"<<std::endl;
            #endif 
            return false;
        }
    }

    bool remove(const value_type &value){
        if(contains(value)){
            for(size_type i = 0; i < _size; ++i){
                if(_eql(_darr[i], value)){
                    for(size_type j = i; j < _size - 1; j++){
                        _darr[j] = _darr[j + 1];
                    } 
                }
            }
            #ifndef NDEBUG 
            std::cout<<"bool remove(true)"<<std::endl;
            #endif 
            _size--;
            return true;
        }
        #ifndef NDEBUG 
        std::cout<<"bool remove(false)"<<std::endl;
        #endif 
        return false;
    }

    /**
        @brief Operatore getter di una elemento del Set

        @param index dell'elemento da leggere
        @return reference all'intero da leggere
    
        @pre index<_size
    */
    const value_type& operator[](size_type index) const{
        assert(index < _size);
        return _darr[index];
    }

    /**
       @brief Verifica se l'elemento è presente nel set.
      
       Controlla se l'elemento passato come parametro è presente nel set.
     
       @param value Elemento da cercare nel set.
       @return true se l'elemento è presente, altrimenti false.
    */
    bool contains(const value_type &value) const{
        for(size_type i = 0; i < _size; ++i){
            if(_eql(_darr[i], value)){
                return true;
            }
        }
        return false;
    }

    /**
        @brief Operatore di uguaglianza ==
        
        Confronta due oggetti tset per verificare l'uguaglianza.
        
        @param other Altro oggetto tset da confrontare.
        @return true se i due set sono uguali, altrimenti false.
    */

    bool operator==(const tset &set) const{
        if(_size != set._size){

            #ifndef NDEBUG 
            std::cout<<"bool ==(false)"<<std::endl;
            #endif 

            return false;
        }
        else{
            for(size_type i = 0; i < _size; ++i){
                if(!_eql(_darr[i], set._darr[i])){

                    #ifndef NDEBUG 
                    std::cout<<"bool ==(false)"<<std::endl;
                    #endif 

                    return false;
                }
            }
            #ifndef NDEBUG 
            std::cout<<"bool ==(true)"<<std::endl;
            #endif 

            return true;
        }
    }


	class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : ptr(nullptr) {}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr) {}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
            return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return ptr;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
            ++ptr;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			++ptr;
            return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return !(other == *this);
		}

	private:
		//Dati membro
        const value_type* ptr;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class tset;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const value_type* p) : ptr(p) {}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_darr);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_darr + _size);
	}

    /**
        @brief Operatore di stream

        Ridefinizione dell'operatore di stream per inviare su
        ostream il contenuto di un Set

        @param os stream di output
        @param set Set da stampare

        @return reference allo stream di output 
    */
    friend std::ostream& operator<<(std::ostream &os, const tset &set){
        os << set._size << " " << set._capacity << " ";
        for(typename tset::size_type i = 0; i < set._size; ++i){
            os << "(" << set._darr[i] << ") ";
        }
        return os;
    }

};





/*
    //////////////
    ////TO DO////
    /////////////

    - Distruttore, svuota la lista?
    - riguarda commento per documentazione della classe.
    - aggiunta _eql al copy constructor?
    - togliere set._capacity dall'ostream (riga 224)
    - rimuovere

*/

#endif