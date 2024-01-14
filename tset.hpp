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
#include <fstream>

/**
  @brief Classe Set templata

  Classe generica che rappresenta una collezione di dati di 
  tipo T che non può contenere duplicati.
  L'uguaglianza tra elementi di tipo T viene effettuata tramite il funtore Equal che
  prende due valori a e b, e ritorna verso se a == b.
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
        Construttore di default che inizializza _darr
        ad un array dinamico vuoto.

        @post _size == 0
        @post _capacity == 0
        @post _darr == nullptr
    */
    tset() : _size(0), _capacity(0), _darr(nullptr){}

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

    }

    /**
        @brief Costruttore di copia (Copy constructor)

        3° METODO FONDAMENTALE DELLE CLASSI
        Crea un set a partire da un altro set

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

    }

    /**
        @brief Operatore di assegnamento

        4° METODO FONDAMENTALE DELLE CLASSI
        Operatore che compia il contenuto di set nel set corrente.

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

    }

    /**
        @brief Metodo per ottenere la dimensione corrente del Set.

        Questo metodo restituisce la dimensione corrente del Set, ovvero il numero di elementi presenti al suo interno.

        @return La dimensione corrente del Set come unsigned int.
    */
    size_type getSize() const{
        return _size;
    }

    /**
        @brief Metodo add

        Aggiunge un elemento al set mantenendo la proprietà del
        non contenere duplicati

        @param value valore da inserire nella lista

        @return true se l'elemento è stato inserito correttamente, false altrimenti
    
        @note Se `value_type` risulta essere un tipo custom, si assume che sia definito il costruttore di default.
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

            return true;
        }
        else{

            return false;
        }
    }

    /**
        @brief Metodo remove

        Rimuove un elemento dal set se presente.

        @param value valore da rimuovere dal set

        @return true se l'elemento è stato rimosso correttamente, false se l'elemento non è presente nel set
*/
    bool remove(const value_type &value){
        if(contains(value)){
            for(size_type i = 0; i < _size; ++i){
                if(_eql(_darr[i], value)){
                    for(size_type j = i; j < _size - 1; j++){
                        _darr[j] = _darr[j + 1];
                    } 
                }
            }

            _size--;
            return true;
        }

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
            return false;
        }
        else{
            for(size_type i = 0; i < _size; ++i){
                if(!_eql(_darr[i], set._darr[i])){
                    return false;
                }
            }
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
        os << set._size << " ";
        for(typename tset::size_type i = 0; i < set._size; ++i){
            os << "(" << set._darr[i] << ") ";
        }
        return os;
    }

    
    /**
        @brief Costruttore per creare un tset da una sequenza definita da una coppia di iteratori.
        
        Questo costruttore inizializza un oggetto tset con gli elementi presenti nella sequenza
        definita dall'intervallo specificato da due iteratori: begin e end.
        
        @tparam Q Tipo dell'iteratore utilizzato per la sequenza di dati.
        @param begin Iteratore che punta all'inizio della sequenza.
        @param end Iteratore che punta alla fine della sequenza.
        
        @throw Eccezione generica se si verifica un errore durante l'aggiunta degli elementi al tset.
        L'eccezione mantiene lo stato del tset invariato.
    */
    template <typename Q>
    tset(Q begin, Q end) : _darr(nullptr), _capacity(0), _size(0){
        Q curr = begin;
        try{
            for(; curr != end; ++curr){
                add(static_cast<T>(*curr));
            }
        }
        catch(...){
            delete begin;
            throw;
        }
    }

};

//FUNZIONI GLOBALI
/**
    @brief Filtra gli elementi di un set basandosi su un predicato fornito.

    La funzione filter_out GLOBALE prende un set generico e un predicato e restituisce un nuovo set
    contenente gli elementi del set originale che soddisfano il predicato fornito.

    @tparam T Tipo degli elementi nel set.
    @tparam Equal funtore per il confronto di uguaglianza tra elementi.
    @tparam Pred Predicato utilizzato per filtrare gli elementi del set.

    @param s Set da cui filtrare gli elementi.
    @param p Predicato utilizzato per decidere quali elementi includere nel set risultante.

    @return Un nuovo set contenente gli elementi di 's' che soddisfano il predicato 'p'.
 */
template <typename T, typename Equal, typename Pred>
tset<T, Equal> filter_out(const tset<T,Equal> &s, Pred p){
    tset<T, Equal> temp;
    for(unsigned int i = 0; i < s.getSize(); ++i){
        if(p(s[i])){
            temp.add(s[i]);
        }
    }

    return temp;
}

/**
  @brief Concatena due set senza duplicati.

  Questa funzione prende due set di tipi generici T e li concatena, creando un nuovo set
  che contiene tutti gli elementi di entrambi i set di input, senza duplicati.

  @tparam T Tipo generico degli elementi nel set.
  @tparam Equal Oggetto funtore o funzione che verifica l'uguaglianza tra gli elementi.
  @param a Primo set da concatenare.
  @param b Secondo set da concatenare.
  @return tset<T, Equal> Nuovo set contenente gli elementi dei due set di input senza duplicati.

  @note La funzione crea un nuovo set in cui vengono inseriti gli elementi di 'a' seguiti dagli elementi
        di 'b' che non sono già presenti in 'a', evitando duplicati.
*/
template <typename T, typename Equal>
tset<T, Equal> operator+(tset<T, Equal> a, tset<T, Equal> b){
    tset<T, Equal> temp;
    for(unsigned int i = 0; i < a.getSize(); ++i){
        temp.add(a[i]);
    }
    for(unsigned int i = 0; i < b.getSize(); ++i){
        temp.add(b[i]);
    }

    return temp;
}

/**
    @brief Operatore di differenza tra set.

    Restituisce un nuovo set che contiene gli elementi presenti sia nel primo set 'a' che nel secondo set 'b'.

    @tparam T Tipo degli elementi nel set.
    @tparam Equal funtore di uguaglianza per confrontare gli elementi.

    @param a Primo set su cui viene verificato il contenuto.
    @param b Secondo set usato per identificare gli elementi comuni.

    @return Set contenente gli elementi presenti sia nel set 'a' che nel set 'b'.

    @note La funzione utilizza il funtore di uguaglianza 'Equal' per confrontare gli elementi all'interno dei set.
*/
template <typename T, typename Equal>
tset<T, Equal> operator-(tset<T, Equal> a, tset<T, Equal> b){
    tset<T, Equal> temp;
    for(unsigned int i = 0; i < b.getSize(); ++i){
        if(a.contains(b[i])){
            temp.add(b[i]);
        }
    }

    return temp;
}

/**
  @brief Salva il contenuto di un set di stringhe in un file.

  Questa funzione prende un set di stringhe e un nome di file e salva il
  contenuto del set nel file specificato. Ogni stringa del set viene scritta
  nel file seguita da un carattere di nuova riga ('\n').

  @tparam Equal Un tipo di funtore per confrontare le stringhe nel set.
  @param s Il set di stringhe da salvare nel file.
  @param file Il nome del file nel quale salvare il contenuto del set.

  @throw Eccezione generica se si verifica un errore durante l'apertura o la
         scrittura nel file. L'eccezione mantiene lo stato del set invariato.
*/
template <typename Equal>
void save(const tset<std::string, Equal>& s, const std::string& file) {

    try{
        std::ofstream outputFile(file);
        for(unsigned int i = 0; i < s.getSize(); ++i){
            outputFile << s[i] << "\n";
        }
        outputFile.close();
        std::cout << "file aggiornato." << std::endl;
    }
    catch(...){
        std::cerr << "impossibile aprire il file." << std::endl;
        throw;
    }
}

#endif