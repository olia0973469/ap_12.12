#include <iostream>
#include <string>

using namespace std;

struct Student {
    string surname;
    int exam1;
    int exam2;
    int exam3;
    float average;

    Student(string s, int e1, int e2, int e3) {
        surname = s;
        exam1 = e1;
        exam2 = e2;
        exam3 = e3;
        average = (e1 + e2 + e3) / 3.0;
    }
};

struct Node {
    Student* data;
    Node* left;
    Node* right;

    Node(Student* s) {
        data = s;
        left = nullptr;
        right = nullptr;
    }
};

void insert(Node*& root, Student* student) {
    if (!root) {
        root = new Node(student);
        return;
    }
    if (student->surname < root->data->surname) {
        insert(root->left, student);
    }
    else {
        insert(root->right, student);
    }
}

Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* remove(Node*& root, string surname) {
    if (!root) return root;
    if (surname < root->data->surname) {
        root->left = remove(root->left, surname);
    }
    else if (surname > root->data->surname) {
        root->right = remove(root->right, surname);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data->surname);
    }
    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Name: " << root->data->surname << endl << " Grades: " << root->data->exam1 << " " << root->data->exam2 << " " << root->data->exam3 << endl << " Average: " << root->data->average << endl;
        inorder(root->right);
    }
}

void insertByAverage(Node*& root, Student* student) {
    if (!root) {
        root = new Node(student);
        return;
    }
    if (student->average < root->data->average) {
        insertByAverage(root->left, student);
    }
    else {
        insertByAverage(root->right, student);
    }
}

Node* sortedInsert(Node* root, Node* node) {
    if (!root) {
        return node;
    }

    if (node->data->average < root->data->average) {
        root->left = sortedInsert(root->left, node);
    }
    else {
        root->right = sortedInsert(root->right, node);
    }

    return root;
}

void inorderForSorting(Node* root, Node*& sortedRoot) {
    if (root != nullptr) {
        inorderForSorting(root->left, sortedRoot);
        sortedRoot = sortedInsert(sortedRoot, new Node(root->data));
        inorderForSorting(root->right, sortedRoot);
    }
}

Node* buildSortedTree(Node* root) {
    if (!root) {
        return nullptr;
    }

    Node* sortedRoot = nullptr;
    inorderForSorting(root, sortedRoot);

    return sortedRoot;
}

Node* sortedInsertByName(Node* root, Node* node) {
    if (!root) {
        return node;
    }

    if (node->data->surname < root->data->surname) {
        root->left = sortedInsertByName(root->left, node);
    }
    else {
        root->right = sortedInsertByName(root->right, node);
    }

    return root;
}

void inorderForSortingByName(Node* root, Node*& sortedRoot) {
    if (root != nullptr) {
        inorderForSortingByName(root->left, sortedRoot);
        sortedRoot = sortedInsertByName(sortedRoot, new Node(root->data));
        inorderForSortingByName(root->right, sortedRoot);
    }
}

Node* buildSortedTreeByName(Node* root) {
    if (!root) {
        return nullptr;
    }

    Node* sortedRoot = nullptr;
    inorderForSortingByName(root, sortedRoot);

    return sortedRoot;
}

Node* sortedInsertByExam1(Node* root, Node* node) {
    if (!root) {
        return node;
    }

    if (node->data->exam1 < root->data->exam1) {
        root->left = sortedInsertByExam1(root->left, node);
    }
    else {
        root->right = sortedInsertByExam1(root->right, node);
    }

    return root;
}

void inorderForSortingByExam1(Node* root, Node*& sortedRoot) {
    if (root != nullptr) {
        inorderForSortingByExam1(root->left, sortedRoot);
        sortedRoot = sortedInsertByExam1(sortedRoot, new Node(root->data));
        inorderForSortingByExam1(root->right, sortedRoot);
    }
}

Node* buildSortedTreeByExam1(Node* root) {
    if (!root) {
        return nullptr;
    }

    Node* sortedRoot = nullptr;
    inorderForSortingByExam1(root, sortedRoot);

    return sortedRoot;
}

int main() {
    Node* root = nullptr;

    insert(root, new Student("Biba", 85, 90, 92));
    insert(root, new Student("Boba", 78, 82, 80));
    insert(root, new Student("Ailliams", 90, 95, 88));

    cout << "Before sorting:" << endl;
    inorder(root);

    Node* sortedRoot = buildSortedTree(root);

    cout << "\nAfter sorting by average:" << endl;
    inorder(sortedRoot);

    Node* sortedRootBySurname = buildSortedTreeByName(root);

    cout << "\nAfter sorting by surname:" << endl;
    inorder(sortedRootBySurname);

    root = remove(root, "Biba");

    cout << "\nAfter removing 'Biba':" << endl;
    inorder(root);

    insert(root, new Student("Biba", 85, 90, 92));

    cout << "\nAfter adding 'Biba':" << endl;
    inorder(root);

    Node* sortedRootByExam1 = buildSortedTreeByExam1(root);

    cout << "\nAfter sorting by exam1:" << endl;
    inorder(sortedRootByExam1);

    return 0;
}
