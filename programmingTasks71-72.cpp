#include <iostream>
#include <string>

template <typename T>
class Node {
    public:
        T key;
        Node* left;
        Node* right;

        Node(T _item) {
            key = _item;
            left = nullptr;
            right = nullptr;
        }
};

template <typename T>
class BinarySearchTree {
    public:
        Node<T>* root;

        BinarySearchTree() {
            root = nullptr;
        }

        Node<T>* insert(Node<T>* _node, T _key) {
            if (_node == nullptr) {
                return new Node<T>(_key);
            }

            if (_key < _node->key) {
                _node->left = insert(_node->left, _key);
            }
            else if (_key > _node->key) {
                _node->right = insert(_node->right, _key);
            }
            
            return _node;
        }

        void insertArray(T _elementsToInsert[], int _n) {
            for(int i = 0; i < _n; i++) {
                root = insert(root, _elementsToInsert[i]);
            }
        }
        
        void print(Node<T>* _root) {
            if (_root != nullptr) {
                print(_root->left);
                std::cout << _root->key << " ";
                print(_root->right);
            }
        }

        int countNodes(Node<T>* _node) {
            if (_node == nullptr) {
                return 0;
            }

            return countNodes(_node->left) + countNodes(_node->right) + 1;
        }

        int countLeaves(Node<T>* _node) {
            if(_node == NULL)     
                return 0; 
            if(_node->left == NULL && _node->right == NULL) 
                return 1;         
            else
                return countLeaves(_node->left)+ 
                    countLeaves(_node->right);
        }
};

void ProgrammingTask71() {
    std::cout << "\n--------------PT71--------------\n";
    BinarySearchTree<int> binarySearchTree;
    int elementsToInsert[] = {3, 4, 5, 1, 7, 6, 8, 2};
    binarySearchTree.insertArray(elementsToInsert, sizeof(elementsToInsert)/sizeof(elementsToInsert[0]));

    std::cout << "Elements in the order: ";
    binarySearchTree.print(binarySearchTree.root);
}

void ProgrammingTask72() {
    std::cout << "\n--------------PT72--------------\n";
    BinarySearchTree<int> binarySearchTree;
    int elementsToInsert[] = {7, 4, 3, 1, 6, 5, 8, 9, 10, 15, 12, 11, 14, 13, 18, 17, 16, 20, 19, 2};
    binarySearchTree.insertArray(elementsToInsert, sizeof(elementsToInsert)/sizeof(elementsToInsert[0]));

    std::cout << "Elements in the order: ";
    binarySearchTree.print(binarySearchTree.root);

    std::cout << "\nNumber of nodes: " << binarySearchTree.countNodes(binarySearchTree.root);
    std::cout << "\nNumber of leaves: " << binarySearchTree.countLeaves(binarySearchTree.root);
}

void ProgrammingTaskExtra() {
    std::cout << "\n--------------PT_E--------------\n";
    BinarySearchTree<std::string> binarySearchTree;
    std::string elementsToInsert[] = {"f", "j", "b", "o", "l", "g", "a", "i", "e", "n", "c", "h", "m", "d", "k"};
    binarySearchTree.insertArray(elementsToInsert, sizeof(elementsToInsert)/sizeof(elementsToInsert[0]));

    std::cout << "Elements in the order: ";
    binarySearchTree.print(binarySearchTree.root);

    std::cout << "\nNumber of nodes: " << binarySearchTree.countNodes(binarySearchTree.root);
    std::cout << "\nNumber of leaves: " << binarySearchTree.countLeaves(binarySearchTree.root);
}

int main() {
    ProgrammingTask71();
    ProgrammingTask72();
    ProgrammingTaskExtra();
    return 0;
}