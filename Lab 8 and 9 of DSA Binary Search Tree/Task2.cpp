#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    int id;
    string name;
    double price;
    Node* left;
    Node* right;

    Node(int i, string n, double p) {
        id = i;
        name = n;
        price = p;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int id,
    string name, double price) {
    if (root == nullptr)
        return new Node(id, name, price);

    if (id < root->id)
        root->left = insert(root->left, id, name, price);
    else if (id > root->id)
        root->right = insert(root->right, id, name, price);
    else
        cout << "Product ID already exists.\n";

    return root;
}

Node* search(Node* root, int id) {
    if (root == nullptr || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);

    return search(root->right, id);
}

Node* findMin(Node* root) {
    if (root == nullptr || root->left == nullptr)
        return root;

    return findMin(root->left);
}

Node* findMax(Node* root) {
    if (root == nullptr || root->right == nullptr)
        return root;

    return findMax(root->right);
}

Node* deleteProduct(Node* root, int id) {
    if (root == nullptr)
        return nullptr;

    if (id < root->id) {
        root->left = deleteProduct(root->left, id);
    }
    else if (id > root->id) {
        root->right = deleteProduct(root->right, id);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);

        root->id = temp->id;
        root->name = temp->name;
        root->price = temp->price;

        root->right = deleteProduct(root->right,
            temp->id);
    }

    return root;
}

// Ascending order by Product ID
void displayProducts(Node* root) {
    if (root == nullptr)
        return;

    displayProducts(root->left);

    cout << "ID: " << root->id
        << " | Name: " << root->name
        << " | Price: " << fixed
        << setprecision(2) << root->price << '\n';

    displayProducts(root->right);
}

void destroyTree(Node* root) {
    if (root == nullptr)
        return;

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int choice, id;
    string name;
    double price;

    do {
        cout << "\n===== PRODUCT MENU =====\n";
        cout << "1. Insert Product\n";
        cout << "2. Search Product\n";
        cout << "3. Display Products\n";
        cout << "4. Delete Product\n";
        cout << "5. Minimum Product ID\n";
        cout << "6. Maximum Product ID\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Product ID: ";
            cin >> id;

            if (search(root, id) != nullptr) {
                cout << "Product ID already exists.\n";
                break;
            }

            cout << "Enter product name: ";
            getline(cin >> ws, name);

            cout << "Enter price: ";
            cin >> price;

            if (price < 0) {
                cout << "Price cannot be negative.\n";
                break;
            }

            root = insert(root, id, name, price);
            cout << "Product inserted.\n";
            break;

        case 2: {
            cout << "Enter Product ID: ";
            cin >> id;

            Node* result = search(root, id);

            if (result != nullptr) {
                cout << "Product found: "
                    << result->name
                    << ", Price: " << result->price << '\n';
            }
            else {
                cout << "Product not found.\n";
            }
            break;
        }

        case 3:
            if (root == nullptr)
                cout << "No products available.\n";
            else
                displayProducts(root);
            break;

        case 4:
            cout << "Enter discontinued Product ID: ";
            cin >> id;

            if (search(root, id) != nullptr) {
                root = deleteProduct(root, id);
                cout << "Product deleted.\n";
            }
            else {
                cout << "Product not found.\n";
            }
            break;

        case 5: {
            Node* mn = findMin(root);
            if (mn)
                cout << "Minimum Product ID: " << mn->id << '\n';
            else
                cout << "No products available.\n";
            break;
        }

        case 6: {
            Node* mx = findMax(root);
            if (mx)
                cout << "Maximum Product ID: " << mx->id << '\n';
            else
                cout << "No products available.\n";
            break;
        }

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