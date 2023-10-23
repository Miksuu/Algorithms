#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(new Node{ 0, nullptr }) {}

    void InsertAtBeginning(int _value) {
        Node* newNode = new Node{ _value, nullptr };
        newNode->next = head->next;
        head->next = newNode;
    }

    void InsertToBack(int _value) {
        Node* newNode = new Node{ _value, nullptr };
        Node* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    bool InsertAfter(int _afterValue, int _valueToInsert) {
        Node* temp = head->next;

        while (temp != nullptr) {
            if (temp->data == _afterValue) {
                Node* newNode = new Node{ _valueToInsert, temp->next };
                temp->next = newNode;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    bool InsertAt(int _n, int _value) {
        Node* temp = head;
        int count = 0;

        while (temp != nullptr && count < _n) {
            ++count;
            temp = temp->next;
        }
        if (count == _n) {
            Node* newNode = new Node{ _value, temp->next };
            temp->next = newNode;

            return true;
        }

        return false;
    }

    void Print() {
        Node* temp = head->next;

        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }

        std::cout << "\n";
    }

    bool Find(int _value) {
        Node* temp = head->next;

        while (temp != nullptr) {
            if (temp->data == _value) {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    bool Delete(int _value) {
        Node* temp = head;

        while (temp->next != nullptr) {
            if (temp->next->data == _value) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    bool IsEmpty() {
        return head->next == nullptr;
    }

    int CountNodes() {
        int count = 0;
        Node* temp = head->next;

        while (temp != nullptr) {
            ++count;
            temp = temp->next;
        }

        return count;
    }

    bool DeleteElementAt(int _elementToDelete) {
        Node* temp = head;
        int count = 0;

        while (temp->next != nullptr && count < _elementToDelete) {
            ++count;
            temp = temp->next;
        }

        if (count == _elementToDelete && temp->next != nullptr) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return true;
        }
        return false;
    }

    void ClearAllItemsInTheList() {
        Node* temp = head->next;

        while (temp != nullptr) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }

        head->next = nullptr;
    }

    void Reverse() {
        Node* prev = nullptr;
        Node* current = head->next;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head->next = prev;
    }

private:
    Node* head;
};

void ProgrammingTask51() {
    std::cout << "\n--------------PT51--------------\n";

    LinkedList list;

    for (int i = 1; i <= 99; ++i) {
        list.InsertAtBeginning(i);
    }

    std::cout << "Linked list content: ";
    list.Print();

    std::cout << "Find(42): " << (list.Find(42) ? "true" : "false") << "\n";
    std::cout << "Find(66): " << (list.Find(66) ? "true" : "false") << "\n";
    std::cout << "Find(100): " << (list.Find(100) ? "true" : "false") << "\n";

    std::cout << "Delete(77): " << (list.Delete(77) ? "true" : "false") << "\n";
    std::cout << "Delete(21): " << (list.Delete(21) ? "true" : "false") << "\n";
    std::cout << "Delete(-1): " << (list.Delete(-1) ? "true" : "false") << "\n";

    for (int i = 1; i <= 99; ++i) {
        list.Delete(i);
    }

    std::cout << "Find(42): " << (list.Find(42) ? "true" : "false") << "\n";

    std::cout << "List empty: " << (list.IsEmpty() ? "Yes" : "No") << "\n";
}

void ProgrammingTask52() {
    std::cout << "\n--------------PT52--------------\n";

    LinkedList list;

    std::cout << "Number of nodes: " << list.CountNodes() << "\n";

    for (int i = 1; i <= 99; ++i) {
        list.InsertAtBeginning(i);
    }

    std::cout << "Number of nodes: " << list.CountNodes() << "\n";

    std::cout << "DeleteAt(77): " << (list.DeleteElementAt(77) ? "true" : "false") << "\n";
    std::cout << "DeleteAt(21): " << (list.DeleteElementAt(21) ? "true" : "false") << "\n";
    std::cout << "DeleteAt(-1): " << (list.DeleteElementAt(-1) ? "true" : "false") << "\n";

    std::cout << "Number of nodes: " << list.CountNodes() << "\n";

    list.ClearAllItemsInTheList();

    std::cout << "Number of nodes: " << list.CountNodes() << "\n";

    std::cout << "List empty: " << (list.IsEmpty() ? "Yes" : "No") << "\n";
}

LinkedList ProgrammingTask53() {
    std::cout << "\n--------------PT53--------------\n";

    LinkedList list;

    for (int i = 10; i <= 90; i += 10) {
        list.InsertToBack(i);
    }
    std::cout << "List after InsertToBack: ";
    list.Print();

    list.InsertAfter(20, 25);
    list.InsertAfter(25, 26);
    list.InsertAfter(90, 91);
    list.InsertAfter(100, 101); // Nothing happens?
    std::cout << "List after InsertAfter inserts: ";
    list.Print();

    list.InsertAt(1, 15);
    list.InsertAt(10, 99);
    list.InsertAt(0, 1);
    list.InsertAt(999, 999);
    std::cout << "List after InsertAt inserts: ";
    list.Print();

    return list;
}


void ProgrammingTask54(LinkedList _list) {
    std::cout << "\n--------------PT54--------------\n";

    _list.Reverse();

    std::cout << "List after the Reverse() function: ";
    _list.Print();
}

int main() {
    ProgrammingTask51();
    ProgrammingTask52();
    LinkedList savedLinkedList = ProgrammingTask53();
    ProgrammingTask54(savedLinkedList);

    return 0;
}