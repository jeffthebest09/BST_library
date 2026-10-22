#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *rightChild;
    Node *leftChild;

    Node(int key)
    {
        val = key;
        rightChild = leftChild = nullptr;
    }
};

Node *insert(Node *root, int val)
{
    if (root == nullptr)
    {
        return new Node(val);
    }

    Node *father = nullptr;
    Node *current = root;

    while (current != nullptr)
    {
        father = current;

        if (val < current -> val)
        {
            current = current -> leftChild;
        }
        else if (val > current -> val)
        {
            current = current -> rightChild;
        }
        else 
        {
            return root;
        }
    }

    if (val < father -> val)
    {
        father -> leftChild = new Node(val);
    }
    else 
    {
        father -> rightChild = new Node(val);
    }

    return root;
}

Node *searchNode(Node *root, int valDaCercare)
{
    Node * current = root;

    while (current != nullptr)
    {
        if (valDaCercare > current ->val)
        {
            current = current -> rightChild;
        }
        else if (valDaCercare < current -> val)
        {
            current = current -> leftChild;
        }
        else if (valDaCercare == current -> val)
        {
            return current;
        }
    }
    return nullptr;
}

int main()
{
    Node *root = nullptr;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);


    int searchedValue = 0;
    cout << "Insert the node that you wanna search: ";
    cin >> searchedValue;

    Node *foundValue = searchNode(root, searchedValue);
    if (foundValue != nullptr)
    {
        cout << "Value found" << endl;
    }
    else 
    {
        cout << "Value not found" << endl;
    }

    return 0;
}