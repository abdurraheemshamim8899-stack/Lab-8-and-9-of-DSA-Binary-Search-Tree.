#include <iostream>
#include <string>
using namespace std;

struct Node {
    int alertID;
    string alertType;
    int severity;
    Node* left;
    Node* right;

    Node(int id, string type, int level) {
        alertID = id;
        alertType = type;
        severity = level;
        left = right = nullptr;
    }
};

// Recursive insertion
Node* insert(Node* root, int id,
    string type, int severity) {
    if (root == nullptr)
        return new Node(id, type, severity);

    if (id < root->alertID) {
        root->left = insert(root->left,
            id, type, severity);
    }
    else if (id > root->alertID) {
        root->right = insert(root->right,
            id, type, severity);
    }
    else {
        cout << "Duplicate Alert ID rejected.\n";
    }

    return root;
}

// Recursive search
Node* search(Node* root, int id) {
    if (root == nullptr || root->alertID == id)
        return root;

    if (id < root->alertID)
        return search(root->left, id);

    return search(root->right, id);
}

// Find minimum node
Node* findMin(Node* root) {
    if (root == nullptr || root->left == nullptr)
        return root;

    return findMin(root->left);
}

// Recursive deletion
Node* deleteAlert(Node* root, int id) {
    if (root == nullptr)
        return nullptr;

    if (id < root->alertID) {
        root->left = deleteAlert(root->left, id);
    }
    else if (id > root->alertID) {
        root->right = deleteAlert(root->right, id);
    }
    else {
        // No left child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // No right child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Two children
        Node* temp = findMin(root->right);

        root->alertID = temp->alertID;
        root->alertType = temp->alertType;
        root->severity = temp->severity;

        root->right = deleteAlert(root->right,
            temp->alertID);
    }

    return root;
}

// Inorder traversal: ascending Alert ID
void displayAlerts(Node* root) {
    if (root == nullptr)
        return;

    displayAlerts(root->left);

    cout << "Alert ID: " << root->alertID
        << " | Type: " << root->alertType
        << " | Severity: " << root->severity
        << '\n';

    displayAlerts(root->right);
}

// Display alerts meeting the severity threshold
void severityReport(Node* root, int threshold) {
    if (root == nullptr)
        return;

    severityReport(root->left, threshold);

    if (root->severity >= threshold) {
        cout << "Alert ID: " << root->alertID
            << " | Type: " << root->alertType
            << " | Severity: " << root->severity
            << '\n';
    }

    severityReport(root->right, threshold);
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
    int choice, id, severity, threshold;
    string type;

    // Initial alerts in the required insertion order
    root = insert(root, 50, "Malware", 9);
    root = insert(root, 30, "Failed Login", 4);
    root = insert(root, 70, "Unauthorized Access", 8);
    root = insert(root, 20, "Failed Login", 3);
    root = insert(root, 40, "Malware", 7);
    root = insert(root, 60, "Unauthorized Access", 6);
    root = insert(root, 80, "Malware", 10);

    do {
        cout << "\n===== SOC ALERT MENU =====\n";
        cout << "1. Insert Alert\n";
        cout << "2. Search Alert\n";
        cout << "3. Display All Alerts\n";
        cout << "4. Severity Report\n";
        cout << "5. Delete Alert\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Alert ID: ";
            cin >> id;

            if (search(root, id) != nullptr) {
                cout << "Duplicate Alert ID rejected.\n";
                break;
            }

            cout << "Enter alert type: ";
            getline(cin >> ws, type);

            cout << "Enter severity (1-10): ";
            cin >> severity;

            if (severity < 1 || severity > 10) {
                cout << "Invalid severity level.\n";
                break;
            }

            root = insert(root, id, type, severity);
            cout << "Alert inserted successfully.\n";
            break;

        case 2: {
            cout << "Enter Alert ID to search: ";
            cin >> id;

            Node* result = search(root, id);

            if (result != nullptr) {
                cout << "Alert found.\n";
                cout << "Alert ID: " << result->alertID << '\n';
                cout << "Type: " << result->alertType << '\n';
                cout << "Severity: " << result->severity << '\n';
            }
            else {
                cout << "Alert not found.\n";
            }
            break;
        }

        case 3:
            if (root == nullptr)
                cout << "No alerts available.\n";
            else
                displayAlerts(root);
            break;

        case 4:
            cout << "Enter severity threshold (1-10): ";
            cin >> threshold;

            if (threshold < 1 || threshold > 10) {
                cout << "Invalid threshold.\n";
                break;
            }

            cout << "\nAlerts meeting the threshold:\n";
            severityReport(root, threshold);
            break;

        case 5:
            cout << "Enter Alert ID to delete: ";
            cin >> id;

            if (search(root, id) != nullptr) {
                root = deleteAlert(root, id);
                cout << "Alert deleted successfully.\n";
            }
            else {
                cout << "Alert not found.\n";
            }
            break;

        case 6:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    destroyTree(root);
    return 0;
}