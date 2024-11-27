#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;

class ANode {
public:
    string authorName;
    ANode* next;
    ANode(string authorName) {
        this->authorName = authorName;
        next = NULL;
    }
};

class SinglyLinkedList {
public:
    ANode* head;
    SinglyLinkedList() {
        head = NULL;
    }
    void insert(string authorName) {
        ANode* newNode = new ANode(authorName);
        if (head == NULL) {
            head = newNode;
        }
        else {
            ANode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void print() {
        ANode* temp = head;
        while (temp != NULL) {
            cout << temp->authorName << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void headreset() {
        head = NULL;
    }
};

class Book {
private:
    int issn;
    string title;
    SinglyLinkedList* authors;
    int authorcount;
    int ref;
    int issue;
public:
    Book() {
        issn = 0;
        title = "";
        authors = new SinglyLinkedList();
        authorcount = 0;
        ref = 0;
        issue = 0;
    }
    Book(int issn, string title, int ref, int issue, SinglyLinkedList* authors) {
        this->issn = issn;
        this->title = title;
        this->ref = ref;
        this->issue = issue;
        this->authors = authors;
    }
    void input() {
        cout << "Enter ISSN: ";
        cin >> issn;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter No of Authors: ";
        cin >> authorcount;
        while (authorcount == 0) {
            cout << "Book can't have 0 author. Please enter author: ";
            cin >> authorcount;
        }
        string authorName;
        for (int i = 0; i < authorcount; i++) {
            cout << "Enter Author " << i + 1 << ": ";
            cin.ignore();
            getline(cin, authorName);
            authors->insert(authorName);
        }
        cout << "Enter No of Reference Copies: ";
        cin >> ref;
        cout << "Enter No of Issue Copies: ";
        cin >> issue;
    }
    void updatebook() {
        string t;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, t);
        this->title = t;
        cout << "Do you also want to update authors? (1 for yes, 0 for no): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Enter No of Authors: ";
            cin >> authorcount;
            authors->headreset();
            while (authorcount == 0) {
                cout << "Book can't have 0 author. Please enter author: ";
                cin >> authorcount;
            }
            string authorName;
            for (int i = 0; i < authorcount; i++) {
                cout << "Enter Author " << i + 1 << ": ";
                cin.ignore();
                getline(cin, authorName);
                authors->insert(authorName);
            }
        }
        cout << "Enter No of Reference Copies: ";
        cin >> ref;
        cout << "Enter No of Issue Copies: ";
        cin >> issue;
    }
    void display() {
        cout << "ISSN: " << issn << endl;
        cout << "Title: " << title << endl;
        cout << "Authors: ";
        authors->print();
        cout << "No of Reference Copies: " << ref << endl;
        cout << "No of Issue Copies: " << issue << endl;
    }
    int getIssn() {
        return issn;
    }
};

class BSTNode {
public:
    Book* book;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Book* book) {
        this->book = book;
        left = right = NULL;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Book* book) {
        if (node == NULL) {
            return new BSTNode(book);
        }
        if (book->getIssn() < node->book->getIssn()) {
            node->left = insert(node->left, book);
        }
        else if (book->getIssn() > node->book->getIssn()) {
            node->right = insert(node->right, book);
        }
        return node;
    }

    void display(BSTNode* node) {
        if (node != NULL) {
            display(node->left);
            node->book->display();
            display(node->right);
        }
    }

    BSTNode* search(BSTNode* node, int issn) {
        if (node == NULL || node->book->getIssn() == issn) {
            return node;
        }
        if (issn < node->book->getIssn()) {
            return search(node->left, issn);
        }
        else {
            return search(node->right, issn);
        }
    }

    BSTNode* deleteNode(BSTNode* root, int issn) {
        if (root == NULL) return root;
        if (issn < root->book->getIssn()) {
            root->left = deleteNode(root->left, issn);
        }
        else if (issn > root->book->getIssn()) {
            root->right = deleteNode(root->right, issn);
        }
        else {
            if (root->left == NULL) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }
            BSTNode* temp = minValueNode(root->right);
            root->book = temp->book;
            root->right = deleteNode(root->right, temp->book->getIssn());
        }
        return root;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

public:
    BST() {
        root = NULL;
    }

    void insert(Book* book) {
        root = insert(root, book);
    }

    void display() {
        display(root);
    }

    void search(int issn) {
        BSTNode* node = search(root, issn);
        if (node != NULL) {
            cout << "Book Found:" << endl;
            node->book->display();
        }
        else {
            cout << "Book Not Found" << endl;
        }
    }

    void deleteRecord(int issn) {
        root = deleteNode(root, issn);
    }
};

int main() {

    BST* bst = new BST();
    int choice;
    cout << "                    ----------- Welcome to Library Managment System --------------" << endl;
    cout << endl;
    cout << "                    ----------- Choose from the following options  ---------------" << endl;
    cout << endl;

    do {
        cout << "1. Create a book record(C)" << endl;
        cout << "2. Review a book record(R)" << endl;
        cout << "3. Update a book record(U)" << endl;
        cout << "4. Delete a book record(D)" << endl;
        cout << "5. Display all books" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Book* book = new Book();
            book->input();
            bst->insert(book);
            break;
        }
        case 2: {
            int issn;
            cout << "Enter ISSN: ";
            cin >> issn;
            bst->search(issn);
            break;
        }
        case 3: {
            int issn;
            cout << "Enter ISSN: ";
            cin >> issn;
            bst->search(issn);
            break;
        }
        case 4: {
            int issn;
            cout << "Enter ISSN: ";
            cin >> issn;
            bst->deleteRecord(issn);
            break;
        }
        case 5:
            bst->display();
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);
    cout << "                             ------------ THANK YOU :) ------------" << endl;
    cout << endl;
    return 0;
}
