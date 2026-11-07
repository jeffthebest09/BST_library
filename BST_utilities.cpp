#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int val;
    Node *leftChild;
    Node *rightChild;

    Node(int key)
    {
        val = key;
        leftChild = rightChild = nullptr;
    }
};

Node *insertNode(Node *&root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        return root;
    }    

    Node *father = nullptr;
    Node *current = root;

    while (current != nullptr)
    {
        father = current;

        if (val > current->val)
        {
            current = current->rightChild;
        }
        else if (val < current->val)
        {
            current = current->leftChild;
        }
        else 
        {
            return root;
        }
    }

    if (val < father->val)
    {
        father->leftChild = new Node(val);
    }
    else if (val > father->val)
    {
        father->rightChild = new Node(val);
    }

    return root;
}

Node *searchNode(Node *root, int searchedValue)
{   
    Node *current = root;

    while (current != nullptr)
    {
        if (current->val == searchedValue)
        {
            return current;
        }
        else if (searchedValue > current->val)
        {
            current = current->rightChild;
        }
        else 
        {
            current = current->leftChild;
        }
    }
    return nullptr;
}

Node *findMin(Node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node *current = root;

    while (current->leftChild != nullptr)
    {
        current = current->leftChild;
    }
    return current;
}

Node *findMax(Node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node *current = root;

    while (current->rightChild != nullptr)
    {
        current = current->rightChild;
    }
    return current;
}

int countNodes(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

int countLeaves(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->leftChild == nullptr && root->rightChild == nullptr)
    {
        return 1;
    }

    return countLeaves(root->leftChild) + countLeaves(root->rightChild);
}

int conuntInRange(Node *root, int min, int max)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->val < min)
    {
        return conuntInRange(root->rightChild, min, max);
    }
    else if (root->val > max)
    {
        return conuntInRange(root->leftChild, min, max);
    }

    return 1 + conuntInRange(root->leftChild, min, max) + conuntInRange(root->rightChild, min, max);
}

void preOrder(Node *root) // Radice, Sinistra, Destra
{
    if (root == nullptr) return;

    cout << root->val << " "; 
    preOrder(root->leftChild);
    preOrder(root->rightChild);
}

void inOrder(Node *root) // Sinistra, Radice, Destra (ordine crescente)
{
    if (root == nullptr) return;

    inOrder(root->leftChild);
    cout << root->val << " ";
    inOrder(root->rightChild);
}

void postOrder(Node *root) // Sinistra, Destra, Radice
{
    if (root == nullptr) return;

    postOrder(root->leftChild);
    postOrder(root->rightChild);
    cout << root->val << " ";
}

/*
Node *deleteNode(Node *root, int value)
{
    if (root == nullptr)
    {
        return root;
    }

    if (value < root -> val)
    {
        Node *needToBeDeleted = deleteNode(root -> leftChild, value);
        delete root -> leftChild;
        root -> leftChild = nullptr;
    }
    else if (value > root -> val)
    {
        Node *needToBeDeleted = deleteNode(root -> rightChild, value);
        delete root -> rightChild; 
        root -> rightChild = nullptr;
    }
    

}
*/



int main()
{
    Node *root = nullptr;

    insertNode(root, 23);
    insertNode(root, 32);
    insertNode(root, 424);
    insertNode(root, 1);
    insertNode(root, 21);
    insertNode(root, 42);
    insertNode(root, 22);
    insertNode(root, 98);
    insertNode(root, -5);

    int searchedNode;
    cout << "Insert the number you wanna search: ";
    cin >> searchedNode;

    Node *foundNode = searchNode(root, searchedNode);
    if (foundNode != nullptr)
    {
        cout << "Node found!" << endl;
    }
    else 
    {
        cout << "Node not found!" << endl;
    }
     
    Node *min = findMin(root);
    Node *max = findMax(root);
    int nodesNumber = countNodes(root);
    int leavesNumber = countLeaves(root);
    int maxRange = 40;
    int minRange = 10;
    int nodesInARange = conuntInRange(root, minRange, maxRange);

    if (root != nullptr)
    {
        // Dereferenziazione diretta min->val e max->val senza casting o conversione
        if (min != nullptr) cout << "The minimum number is: " << min->val << endl;
        if (max != nullptr) cout << "The maximum number is: " << max->val << endl;

        cout << "The number of nodes is: " << nodesNumber << endl;
        
        cout << "The number of leaves is: " << leavesNumber << endl;
        

        cout << "The number of nodes in the range [" << minRange << ", " << maxRange << "] is: " << nodesInARange << endl; 

        cout << "Binary Tree preOrder (root, leftChild, rightChild): ";
        preOrder(root);
        cout << endl;

        cout << "Binary Tree inOrder (leftChild, root, rightChild): ";
        inOrder(root);
        cout << endl;

        cout << "Binary Tree postOrder (leftChild, rightChild, root): ";
        postOrder(root);
        cout << endl;
    }

    return 0;
}