//Liam Lees
//oct 2 2024
//Prof. M.
//CS 240, TTH 530-645

#include <iostream>
#include <string>
using namespace std;

// board class
class MonopolyBoard {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolyBoard(string propertyName, string propertyColor, int value, int rent) {
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }
//is equal
    bool isEqual(MonopolyBoard other) {
        return propertyName == other.propertyName;
    }
//printing
    void print() {
        cout << "Property Name: " << propertyName << ", color: " << propertyColor
             << ", cost: " << value << ", Rent: " << rent;
        cout << endl;
        cout << endl;
    }
};

// Template node class
template <typename T> class Node {
public:
    T data;
    Node* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// Template linked list class
template <typename T> class CircularLinkedList {
private:
    Node<T>* headNode;

public:
    CircularLinkedList() {
        headNode = nullptr;
    }

    // insert at head
    void insertAtHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (headNode == nullptr) {
            headNode = newNode;
            headNode->nextNode = headNode;
        } else {
            Node<T>* temp = headNode;
            while (temp->nextNode != headNode) {
                temp = temp->nextNode;
            }
            temp->nextNode = newNode;
            newNode->nextNode = headNode;
            headNode = newNode;
        }
    }

    // tail insert
    void insertAtTail(T value) {
        if (headNode == nullptr) {
            insertAtHead(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        Node<T>* temp = headNode;
        while (temp->nextNode != headNode) {
            temp = temp->nextNode;
        }


        temp->nextNode = newNode;
        newNode->nextNode = headNode;
    }

    // insert at specific pos.
    void insertAtPosition(int position, T value) {

        Node<T>* newNode = new Node<T>(value);
        Node<T>* temp = headNode;
        for (int i = 1; i < position - 1 && temp->nextNode != headNode; ++i) {
            temp = temp->nextNode;
        }
        newNode->nextNode = temp->nextNode;
        temp->nextNode = newNode;
    }

    // head deletion
    void deleteAtHead() {
        if (headNode == nullptr) {
            return;
        }
        Node<T>* temp = headNode;
        if (headNode->nextNode == headNode) {
            delete headNode;
            headNode = nullptr;
        } else {
            Node<T>* tail = headNode;
            while (tail->nextNode != headNode) {
                tail = tail->nextNode;
            }
            headNode = headNode->nextNode;
            tail->nextNode = headNode;
            delete temp;
        }
    }

    // tail deletion
    void deleteAtTail() {
        if (headNode == nullptr) {
            return;
        }
        if (headNode->nextNode == headNode) {
            deleteAtHead();
            return;
        }
        Node<T>* temp = headNode;
        while (temp->nextNode->nextNode != headNode) {
            temp = temp->nextNode;
        }
        delete temp->nextNode;
        temp->nextNode = headNode;
    }

    // delete at specific pos.
    void deleteAtPosition(int position) {

        Node<T>* temp = headNode;
        for (int i = 1; i < position - 1; ++i) {
            temp = temp->nextNode;
        }
        Node<T>* toDelete = temp->nextNode;
        temp->nextNode = temp->nextNode->nextNode;
        delete toDelete;
    }

    // search
    bool search(string propertyName) {
        if (headNode == nullptr) return false;

        Node<T>* temp = headNode;
        do {
            if (temp->data.propertyName == propertyName) {
                temp->data.print();
                return true;
            }
            temp = temp->nextNode;
        } while (temp != headNode);
        cout << "not found" << endl;
        return false;
    }

    // print
    void printList() {
        if (headNode == nullptr) return;
        Node<T>* temp = headNode;
        do {
            temp->data.print();
            temp = temp->nextNode;
        } while (temp != headNode);
    }
};


int main() {
    CircularLinkedList<MonopolyBoard> list;

    //sample data
    list.insertAtHead(MonopolyBoard("A", "Red", 1, 1));
    list.insertAtTail(MonopolyBoard("B", "White", 2, 2));
    list.insertAtTail(MonopolyBoard("C", "Black", 3, 3));
    list.insertAtTail(MonopolyBoard("D", "Blue", 4, 4));

    cout << "All properties: ";
    list.printList();

    // search for prop.
    cout << "Search for prop.";
    string propName;
    cin >> propName;
    list.search(propName);

    // delete property @ head
    cout << "Delete at head " << propName << endl;
    list.deleteAtHead();
    list.printList();

    //insert at spec. pos.
    cout << "Insert at pos. ...";
    list.insertAtPosition(2, MonopolyBoard("E", "Green", 5, 5));
    list.printList();

    //delete at spec. pos.
    cout << "Delete at pos. ...." << endl;
    list.deleteAtPosition(3);
    list.printList();

    // delete at tail
    cout << "Delete at tail" << endl;
    list.deleteAtTail();
    list.printList();

    return 0;
}

