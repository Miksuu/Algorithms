#include <iostream>

class Node {
    public:
        int key;
        Node* left;
        Node* right;

        Node(int _item) {
            key = _item;
            left = nullptr;
            right = nullptr;
        }
};

class BinarySearchTree {
    public:
        Node* root;

        BinarySearchTree() {
            root = nullptr;
        }

        Node* insert(Node* _node, int _key) {
            if (_node == nullptr) {
                return new Node(_key);
            }

            if (_key < _node->key) {
                _node->left = insert(_node->left, _key);
            }
            else if (_key > _node->key) {
                _node->right = insert(_node->right, _key);
            }
            
            return _node;
        }

        void insertArray(int _elementsToInsert[], int _n) {
            for(int i = 0; i < _n; i++) {
                root = insert(root, _elementsToInsert[i]);
            }
        }
        
        void print(Node* _root) {
            if (_root != nullptr) {
                print(_root->left);
                std::cout << _root->key << " ";
                print(_root->right);
            }
        }

        int countNodes(Node* _node) {
            if (_node == nullptr) {
                return 0;
            }

            return countNodes(_node->left) + countNodes(_node->right) + 1;
        }

        int countLeaves(Node* _node) {
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
    BinarySearchTree binarySearchTree;
    int elementsToInsert[] = {3, 4, 5, 1, 7, 6, 8, 2};
    binarySearchTree.insertArray(elementsToInsert, sizeof(elementsToInsert)/sizeof(elementsToInsert[0]));

    std::cout << "Elements in the order: ";
    binarySearchTree.print(binarySearchTree.root);
}

void ProgrammingTask72() {
    std::cout << "\n--------------PT72--------------\n";
    BinarySearchTree binarySearchTree;
    int elementsToInsert[] = {7, 4, 3, 1, 6, 5, 8, 9, 10, 15, 12, 11, 14, 13, 18, 17, 16, 20, 19, 2};
    binarySearchTree.insertArray(elementsToInsert, sizeof(elementsToInsert)/sizeof(elementsToInsert[0]));

    std::cout << "Elements in the order: ";
    binarySearchTree.print(binarySearchTree.root);

    std::cout << "\nNumber of nodes: " << binarySearchTree.countNodes(binarySearchTree.root);
    std::cout << "\nNumber of leaves: " << binarySearchTree.countLeaves(binarySearchTree.root);
}

int main() {
    ProgrammingTask71();
    ProgrammingTask72();
    return 0;
}