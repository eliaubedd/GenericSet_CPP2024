PROGETTO C++ CORSO LAUREA DI INFORMATICA, MILANO BICOCCA

Il progetto richiede la progettazione e realizzazione di una classe che
implementa un Set di elementi generici T. Un Set è una collezione di dati che
NON può contenere duplicati: es. un set di interi S={1,6,4,9,7,10,12}.
Evitare le strutture a lista.

A parte i metodi essenziali per il suo corretto uso, la classe deve implementare
anche le seguenti funzionalità:
1. Deve esistere un metodo add per l’aggiunta di un elemento.
2. Deve esistere un metodo remove per la rimozione di un elemento.
3. Accesso, in sola lettura, all'i-esimo elemento tramite operator[ ]
4. Un metodo contains, che ritorna true se il set contiene un dato valore passato come parametro.
5. La classe deve essere dotata solo di const_iterator.
6. Deve essere possibile creare un Set a partire da una sequenza di dati
definita da una coppia generica di iteratori su tipi Q. Lasciate al
compilatore la gestione della compatibilità tra i tipi attraverso l'uso del
cast.
7. Deve essere possibile stampare il contenuto del set utilizzando
operator<<. Il formato di stampa deve essere il seguente: stampare
la dimensione del set e sulla stessa riga, separati da spazi, i valori
contenuti nel set (formattati liberamente) tra parentesi tonde. Ad
esempio, per il set S={1,6,4,9,7,10,12}, la stampa deve produrre la
stringa: “7 (1) (6) (4) (9) (7) (10) (12)”.
8. Implementare un metodo, tramite operator==, per confrontare due
set e ritorna true se i due set contengono gli stessi dati.
Implementare una funzione globale e generica filter_out che, dato un
Set generico S su tipi T e un predicato booleano generico P, ritorna un
nuovo set di tipi T ottenuto prendendo da S tutti gli elementi che soddisfano
il predicato P.
Implementare una funzione globale operator+ che, dati in input due Set
generici su tipi T, ritorna un Set di tipi T che contiene gli elementi di
entrambi i set (“concatenazione” di set).
