#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Recursive insertion
Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        cout << "Duplicate value is not allowed.\n";

    return root;
}

// Recursive searching
bool search(Node* root, int value) {
    if (root == nullptr)
        return false;

    if (root->data == value)
        return true;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

// Find minimum node in a subtree
Node* findMin(Node* root) {
    if (root == nullptr || root->left == nullptr)
        return root;

    return findMin(root->left);
}

// Recursive deletion: leaf, one child, two children
Node* deleteNode(Node* root, int value) {
    if (root == nullptr)
        return nullptr;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        // Case 1: No child (leaf)
        if (root->left == nullptr &&
            root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // Case 2: Only right child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: Only left child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right,
            temp->data);
    }

    return root;
}

// Inorder: Left, Root, Right
void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Preorder: Root, Left, Right
void preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder: Left, Right, Root
void postorder(Node* root) {
    if (root == nullptr)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Free dynamically allocated nodes
void destroyTree(Node* root) {
    if (root == nullptr)
        return;

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

int main1() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\n===== BST MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Preorder Traversal\n";
        cout << "6. Postorder Traversal\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            root = insert(root, value);
            break;

        case 2:
            cout << "Enter value to delete: ";
            cin >> value;

            if (search(root, value)) {
                root = deleteNode(root, value);
                cout << "Value deleted.\n";
            }
            else {
                cout << "Value not found.\n";
            }
            break;

        case 3:
            cout << "Enter value to search: ";
            cin >> value;

            if (search(root, value))
                cout << "Value exists in BST.\n";
            else
                cout << "Value not found.\n";
            break;

        case 4:
            if (root == nullptr)
                cout << "Tree is empty.\n";
            else {
                cout << "Inorder: ";
                inorder(root);
                cout << endl;
            }
            break;

        case 5:
            if (root == nullptr)
                cout << "Tree is empty.\n";
            else {
                cout << "Preorder: ";
                preorder(root);
                cout << endl;
            }
            break;

        case 6:
            if (root == nullptr)
                cout << "Tree is empty.\n";
            else {
                cout << "Postorder: ";
                postorder(root);
                cout << endl;
            }
            break;

        case 7:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    destroyTree(root);
    return 0;
}