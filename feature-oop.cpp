// Esercitazione (90 minuti): refactoring di un BST, da struct a classi - classe 4C
// Nome/Codice: Kaiyi
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

    Node(int key)
    {
        data = key;
        rightChild = leftChild = nullptr;
    }

    // TODO 2 - getData, getLeft, getRight
    //          Restituiscono la chiave, il figlio sinistro e il figlio destro.

    int getData() const
    {
        return data;
    }

    Node *getLeft() const 
    {
        return leftChild;
    }

    Node *getRight() const
    {
        return rightChild;
    }

    // TODO 3 - setData, setLeft, setRight
    //          Modificano la chiave e collegano il figlio sinistro e il figlio destro.
    //          setLeft e setRight ricevono l'indirizzo di un nodo (o nullptr per scollegare).

    void setData(int value)
    {
        data = value;
    }

    void setLeft(Node *lC)
    {
        leftChild = lC; 
    }

    void setRight(Node *rC)
    {
        rightChild = rC;
    }
    
    

    // TODO 4 - isLeaf
    //          Dice se il nodo e' una foglia, cioe' se non ha nessun figlio.

    bool isLeaf()
    {
        if (rightChild == nullptr && leftChild == nullptr)
        {
            return true;
        }
        else 
        {
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


public:
    // TODO 5 - costruttore BST, isEmpty, size
    //          Il costruttore crea un albero vuoto. isEmpty dice se l'albero e' vuoto,
    //          size restituisce quante chiavi contiene.

    BST()
    {
        root = nullptr;
        numNodi = 0;
    }

    bool isEmpty()
    {
        if (root == nullptr)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    int size()
    {
        return numNodi;
    }

    // TODO 6 - insert
    //          Riceve una chiave e la inserisce al posto giusto creando un nuovo Node con new.
    //          Niente duplicati: se la chiave e' gia' presente non fa nulla.
    //          Dice se la chiave e' stata inserita.

    bool insert(int value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            numNodi++;
            return true;
        }

        Node *current = root;
        Node *father = nullptr;

        while(current != nullptr)
        {
            if (value == current -> getData())
            {
                return false;
            }

            father = current;

            if (value > current -> getData())
            {
                current = current -> getRight();
            }
            else 
            {
                current = current -> getLeft();
            }
        }

        Node *newNode = new Node(value);
        if (value > father -> getData())
        {
            father -> setRight(newNode);
        }
        else 
        {
            father -> setLeft(newNode);
        }

        numNodi++;
        return true;
    }

    // TODO 7 - search
    //          Dice se una chiave e' presente nell'albero (non modifica l'albero).

    bool search(int searchedValue) 
    {
        Node *current = root;

        while (current != nullptr)
        {
            if (searchedValue == current -> getData())
            {
                return true;
            }
            else if (searchedValue > current -> getData())
            {
                current = current -> getRight();
            }
            else 
            {
                current = current -> getLeft();
            }
        }
        return false;
    }

    // TODO 8 - inOrder
    //          Stampa su cout tutte le chiavi in ordine crescente (visita inorder),
    //          ciascuna seguita da uno spazio. Se l'albero e' vuoto non stampa nulla.
    //          Non va a capo: ci pensa il main.

    void inOrder(Node *n)
    {
        cout << n -> getLeft() << " ";
        inOrder(n);
        cout << n -> getRight() << " ";
    }

    // TODO 9 - height
    //          Restituisce l'altezza dell'albero, cioe' il numero di nodi del cammino piu' lungo
    //          dalla radice a una foglia. Albero vuoto: 0.

    int height()
    {

    }

    // TODO 10 - minimo, massimo
    //          Restituiscono la chiave piu' piccola e quella piu' grande.
    //          Per un albero vuoto restituiscono -1 (nell'esercizio le chiavi sono sempre positive).

    int minimo()
    {
        if (root == nullptr)
        {
            return -1;
        }
        
        Node *current = root;
        while (current -> getLeft() != nullptr)
        {
            current = current -> getLeft();
        }
        return current -> getData();
    }

    int massimo()
    {
        if (root == nullptr)
        {
            return -1;
        }

        Node *current = root;

        while (current -> getRight() != nullptr)
        {
            current = current -> getRight();
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

    bool remove(int value)
    {
        Node *current = root;
        Node *father = nullptr;

        while (current != nullptr && current -> getData() != value)
        {
            father = current;

            if (value > current -> getData())
            {
                current = current -> getRight();
            }
            else 
            {
                current = current -> getLeft();
            }
        }

        if (current == nullptr)
        {
            return false;
        }

        if (current -> getLeft() != nullptr && current -> getRight() != nullptr)
        {
            Node *succ = current -> getRight();
            Node *fatherSucc = current;

            while (succ -> getLeft() != nullptr)
            {
                fatherSucc = succ;
                succ = succ -> getLeft();
            }

            current -> setData(succ -> getData());

            father = fatherSucc;
            current = succ;
        }

        Node *figlio;

        if (current -> getLeft() != nullptr)
        {
            figlio = current -> getLeft();
        }
        else 
        {
            figlio = current -> getRight();
        }

        if (father == nullptr)
        {
            root = figlio;
        }
        else if (father -> getLeft() == current)
        {
            father -> setRight(figlio);
        }
        else 
        {
            father -> setRight(figlio);
        }

        delete current;
        numNodi--;

        return true;
    }

    // TODO 12 - svuota
    //          Libera con delete tutti i nodi e riporta l'albero allo stato vuoto.
    //          Deve poter essere chiamata anche due volte di fila senza danni.

    void svuota()
    {
        while(root != nullptr)
        {
            remove (root -> getData());
        }
    }

    // TODO 13 - contaFoglie
    //          Restituisce quante foglie ha l'albero (usa isLeaf). Albero vuoto: 0.

    int countLeaves(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root -> getLeft() == nullptr && root -> getRight() == nullptr)
        {
            return 1;
        }

        return countLeaves(root -> getLeft()) + countLeaves(root -> getRight());
}

    // BONUS TODO 14 - contaIntervallo
    //          Riceve due chiavi low e high e restituisce quante chiavi dell'albero sono comprese
    //          tra low e high (estremi inclusi). Sfrutta la proprieta' del BST: non serve
    //          visitare i sottoalberi che non possono contenere chiavi dell'intervallo.


    int conuntInRange(Node *root, int min, int max)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root -> getData() < min)
        {
            return conuntInRange(root -> getRight(), min, max);
        }
        else if (root -> getData() > max)
        {
            return conuntInRange(root -> getLeft(), min, max);
        }

        return 1 + conuntInRange(root -> getLeft(), min, max) + conuntInRange(root->getRight(), min, max);
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
//    Risposta: 
//
// 4) Chi e' responsabile di liberare i nodi creati con new? In quale momento lo si fa,
//    e cosa succederebbe se ci si dimenticasse?
//    Risposta: La classe BST è responsabile della memoria tramite i metodi remove, svuota 
//    Lo si fa quando si cancella un nodo, sennò porta al  memory leak.

