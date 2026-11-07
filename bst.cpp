// Esercitazione (90 minuti): refactoring di un BST, da struct a classi - classe 4C
// Nome/Codice: ______________________
//
// Trasforma la libreria del Binary Search Tree: la struct Node diventa una classe con
// attributi privati e le funzioni libere diventano metodi di una nuova classe BST.
// I nomi dei metodi sono quelli scritti qui sotto e usati da main.cpp: decidi tu
// parametri e tipo restituito, guardando anche come li usa main.cpp.
// NON modificare main.cpp. Consegna SOLO questo file (bst.cpp).
// Se un metodo non riesci a scriverlo, lascia almeno una versione vuota
// (che restituisce un valore qualsiasi) per far compilare il programma.

#include <iostream>
using namespace std;

// =====================================================================
// PARTE A - la classe Node (circa 15 minuti)
// =====================================================================

class Node {
private:
    // TODO 1 - gli attributi: la chiave (int) e i puntatori ai due figli.
    //          Usa gli stessi nomi della struct originale: data, left, right.

    int data;
    Node *rightChild;
    Node *leftChild;

public:
    // TODO 1 - costruttore Node
    //          Riceve la chiave. All'inizio il nodo non ha figli (entrambi i puntatori valgono nullptr).
    //          Dai al parametro un nome diverso da quello dell'attributo.

    Node(int k)
        : data(k), leftChild(nullptr), rightChild(nullptr) {

        }

    // TODO 2 - getData, getLeft, getRight
    //          Restituiscono la chiave, il figlio sinistro e il figlio destro.

    int getData() const {
        return data;
    }

    Node *getLeft() const {
        return leftChild;
    }

    Node *getRight() const {
        return rightChild;
    }

    // TODO 3 - setData, setLeft, setRight
    //          Modificano la chiave e collegano il figlio sinistro e il figlio destro.
    //          setLeft e setRight ricevono l'indirizzo di un nodo (o nullptr per scollegare).

    void setData(int value) {
        this -> data = value;
    }

    void setLeft(Node *n) {
        this -> leftChild = n;
    }

    void setRight(Node *n) {
        this -> rightChild = n;
    }

    // TODO 4 - isLeaf
    //          Dice se il nodo e' una foglia, cioe' se non ha nessun figlio.

    bool isLeaf() const {
        if (rightChild == nullptr && leftChild == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
};

// =====================================================================
// PARTE B - la classe BST: struttura, inserimento, ricerca, visita (circa 30 minuti)
// L'albero conosce solo la radice e il numero di nodi: da fuori non si vede nessun Node.
// =====================================================================

class BST {
private:
    Node* root;         // radice dell'albero, nullptr se l'albero e' vuoto
    int numNodi;        // numero di chiavi presenti

    // Qui puoi aggiungere funzioni di appoggio private (per esempio quelle ricorsive,
    // che hanno bisogno di ricevere un nodo come argomento).

    void inOrderRicorsivo(Node *node) const { 
        if (node == nullptr) return;

        inOrderRicorsivo(node -> getLeft());
        cout << node -> getData() << " ";
        inOrderRicorsivo(node -> getRight());
    }

    int heightRicorsivo(Node *root) const {
        if (root == nullptr) return 0;

        int heightSx = heightRicorsivo(root -> getLeft());
        int heightDx = heightRicorsivo(root -> getRight());

        if (heightDx > heightSx) {
            return 1 + heightDx;
        } else {
            return 1 + heightSx;
        }
    } 

    Node *trovaMinimo(Node *node) {
        if (node == nullptr) return nullptr;

        while (node -> getLeft() != nullptr) {
            node = node -> getLeft();
        }
        return node;
    }
 
    Node *removeRicorsivo(Node *node, int value, bool &removed) {
        if (node == nullptr) return nullptr;

        if (value < node->getData()) {
            node->setLeft(removeRicorsivo(node->getLeft(), value, removed));
        } else if (value > node->getData()) {
            node->setRight(removeRicorsivo(node->getRight(), value, removed));
        } else {
            removed = true;

            if (node->getLeft() == nullptr) {
                Node *temp = node->getRight();
                delete node;
                return temp;
            } else if (node->getRight() == nullptr) {
                Node *temp = node->getLeft();
                delete node;
                return temp;
            }

            Node *temp = trovaMinimo(node->getRight());
            node->setData(temp->getData()); 
            
            node->setRight(removeRicorsivo(node->getRight(), temp->getData(), removed));
        }
        return node;
    }

    int contaFoglieRicorsivo(Node *node) const {
        if (node == nullptr) return 0;
        
        if (node->isLeaf()) return 1;

        return contaFoglieRicorsivo(node->getLeft()) + contaFoglieRicorsivo(node->getRight());
    }  

    int contaIntervalloRicorsivo(Node *node, int min, int max) {
        if (node == nullptr) return 0;

        if (node -> getData() < min) {
            return contaIntervalloRicorsivo(node -> getRight(), min, max);
        }  
        
        if (node -> getData() > max) {
            return contaIntervalloRicorsivo(node -> getLeft(), min, max);
        }

        return 1 + contaIntervalloRicorsivo(node -> getLeft(), min, max) + contaIntervalloRicorsivo(node -> getRight(), min, max);
    }

    void svuotaRicorsivo(Node *node) {
        if (node == nullptr) return;

        svuotaRicorsivo(node -> getRight());
        svuotaRicorsivo(node -> getLeft());

        delete node;
    }

public:
    // TODO 5 - costruttore BST, isEmpty, size
    //          Il costruttore crea un albero vuoto. isEmpty dice se l'albero e' vuoto,
    //          size restituisce quante chiavi contiene.

    BST()
        : root(nullptr), numNodi(0) {}

    bool isEmpty() const {
        return root == nullptr;
    }

    int size() const {
        return numNodi;
    }

    // TODO 6 - insert
    //          Riceve una chiave e la inserisce al posto giusto creando un nuovo Node con new.
    //          Niente duplicati: se la chiave e' gia' presente non fa nulla.
    //          Dice se la chiave e' stata inserita.

    bool insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
            numNodi++;
            return true;
        }

        Node *father = nullptr;
        Node *current = root;

        while (current != nullptr) {
            father = current;

            if (value == current -> getData()) {
                return false;
            } else if (value < current -> getData()) {
                current = current -> getLeft();
            } else {
                current = current -> getRight();
            }
        }

        Node *newNode = new Node(value);
        if (value < father -> getData()) {
            father -> setLeft(newNode);
        } else {
            father -> setRight(newNode);
        }
        numNodi++;
        return true;
    }

    // TODO 7 - search
    //          Dice se una chiave e' presente nell'albero (non modifica l'albero).

    bool search(int value) {
        if (root == nullptr) {
            return false; 
        }

        Node *current = root;

        while (current != nullptr) {
            if (value == current -> getData()) {
                return true;
            } else if (value < current -> getData()) {
                current = current -> getLeft();
            } else {
                current = current -> getRight();
            }
        }
        return false;
    }

    // TODO 8 - inOrder
    //          Stampa su cout tutte le chiavi in ordine crescente (visita inorder),
    //          ciascuna seguita da uno spazio. Se l'albero e' vuoto non stampa nulla.
    //          Non va a capo: ci pensa il main.

    void inOrder() const {
        inOrderRicorsivo(root);
    }

    // TODO 9 - height
    //          Restituisce l'altezza dell'albero, cioe' il numero di nodi del cammino piu' lungo
    //          dalla radice a una foglia. Albero vuoto: 0.

    int height() const {
       return heightRicorsivo(root);
    }

    // TODO 10 - minimo, massimo
    //          Restituiscono la chiave piu' piccola e quella piu' grande.
    //          Per un albero vuoto restituiscono -1 (nell'esercizio le chiavi sono sempre positive).

    int massimo() const {
        if (isEmpty()) return -1;

        Node *current = root;

        while (current -> getRight() != nullptr) {
            current = current -> getRight();
        }
        return current -> getData();
    }

    int minimo() const {
        if (isEmpty()) return -1;

        Node *current = root;

        while (current -> getLeft() != nullptr) {
            current = current -> getLeft();
        }
        return current -> getData();
    }

    // =================================================================
    // PARTE C - cancellazione e memoria (circa 30 minuti)
    // =================================================================

    // TODO 11 - remove
    //          Elimina una chiave dall'albero e dice se esisteva. Gestisci i tre casi:
    //          nodo senza figli, con un figlio, con due figli (si sostituisce la chiave con
    //          quella del successore). Ogni nodo tolto va liberato con delete.

    bool remove(int value) {
        bool removed = false;
        root = removeRicorsivo(root, value, removed);

        if (removed) {
            numNodi--;
        } 
        return removed;
    }
    // TODO 12 - svuota
    //          Libera con delete tutti i nodi e riporta l'albero allo stato vuoto.
    //          Deve poter essere chiamata anche due volte di fila senza danni.

    void svuota() {
        svuotaRicorsivo(root);
        root = nullptr;
        numNodi = 0;
    }

    // TODO 13 - contaFoglie
    //          Restituisce quante foglie ha l'albero (usa isLeaf). Albero vuoto: 0.

    int contaFoglie() const {
       return contaFoglieRicorsivo(root);
    }


    // BONUS TODO 14 - contaIntervallo
    //          Riceve due chiavi low e high e restituisce quante chiavi dell'albero sono comprese
    //          tra low e high (estremi inclusi). Sfrutta la proprieta' del BST: non serve
    //          visitare i sottoalberi che non possono contenere chiavi dell'intervallo.

    int contaIntervallo(int min, int max) {
        return contaIntervalloRicorsivo(root, min, max);
    }

};

// =====================================================================
// PARTE D - domande e controllo finale (circa 15 minuti)
// Rispondi qui sotto, in due o tre righe ciascuna.
// =====================================================================
//
// 1) Perche' gli attributi di Node sono private? Cosa si guadagna rispetto alla struct,
//    in cui qualunque funzione poteva scrivere in data, left e right?
//    Risposta: Garantiscono l'incapsulamento proteggendo i dati da modifiche.
//
// 2) Nella struct la radice veniva passata come argomento a ogni funzione; nella classe
//    BST la radice e' un attributo. Cosa cambia per chi usa l'albero (guarda il main)?
//    Risposta: non serve più passare la radice a ogni funzione. 
//
// 3) Perche' di solito un metodo ricorsivo come insert o inOrder ha bisogno di una funzione di appoggio
//    privata che riceve un nodo, e non puo' essere scritto direttamente come metodo pubblico?
//    Risposta: perché solamente in private è possibile avere come parametro un tipo Node *
//
// 4) Chi e' responsabile di liberare i nodi creati con new? In quale momento lo si fa,
//    e cosa succederebbe se ci si dimenticasse?
//    Risposta: La classe BST è responsabile della memoria tramite i metodi remove, svuota 
//              Lo si fa quando si cancella un nodo, sennò porta al  memory leak.
