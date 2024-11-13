#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;
class ANode
{
public:
	string authorName;
	ANode* next;
	ANode(string authorName)                              // a class anode to be used asa helper to create singly linked list
	{
		this->authorName = authorName;
		next = NULL;                             // constructor to initialize the authhor name
	}
};
class SinglyLinkedList
{
public:
	ANode* head;                            // a singly linked list class to store  the author names
	SinglyLinkedList()
	{
		head = NULL;
	}
	void insert(string authorName)
	{
		ANode* newNode = new ANode(authorName);
		if (head == NULL)                               // a funtion to insert author names 
		{
			head = newNode;
		}
		else
		{
			ANode* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
	void print()
	{
		ANode* temp = head;
		while (temp != NULL)
		{                                                   // a funtion to print the author names
			cout << temp->authorName << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	void headreset()
	{
		head = NULL;
	}
};


class Book
{
private:
	int issn;
	string title;
	SinglyLinkedList* authors;                              // a pointer to class singley linked list to access the author names
	int authorcount;                               // a book class containing all the information regrding a book 
	int ref;
	int issue;
public:
	Book()
	{
		issn = 0;                               //  a costructor to initialize the elements of a book
		title = "";
		authors = new SinglyLinkedList();
		authorcount = 0;
		ref = 0;
		issue = 0;
	}
	Book(int issn, string title, int ref, int issue, SinglyLinkedList* authors)
	{
		this->issn = issn;
		this->title = title;                     //  a parametrzied constructor of class book
		this->ref = ref;
		this->issue = issue;
		this->authors = authors;
	}
	void input() {
		{
			cout << "Enter ISSN: ";
			cin >> issn;                            // a funtion to take input 
			cout << "Enter Title: ";
			cin.ignore();
			getline(cin,title)   ;                 
		
			cout << "Enter No of Authors : ";
			cin >> authorcount;
			while (authorcount == 0) {
				cout << "Book cant have 0 author please enter author : ";
				cin >> authorcount;
			}

			string authorName;

			for (int i = 0; i < authorcount; i++)
			{
				cout << "Enter Author " << i + 1 << " : ";
				getline(cin,authorName);
				authors->insert(authorName);

			}

			cout << "Enter No of Reference Copies: ";
			cin >> ref;
			cout << "Enter No of Issue Copies: ";
			cin >> issue;
		}
	}

	void updatebook() {

		string t;
		cout << "Enter Title: ";
		cin.ignore();
		getline (cin,t);
		this->title = t;
		cout << "Do you also want to update authors 1 for yes 0 for no : " << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			cout << "Enter No of Authors : ";                        // updating the record of a perticular book thriugh its issn
			cin >> authorcount;

			authors->headreset();

			while (authorcount == 0) {
				cout << "Book cant have 0 author please enter author : ";
				cin >> authorcount;
			}

			string authorName;

			for (int i = 0; i < authorcount; i++)
			{
				cout << "Enter Author " << i + 1 << " : ";
				cin.ignore();
				getline(cin,authorName);
				authors->insert(authorName);

			}
		}

		cout << "Enter No of Reference Copies: ";
		cin >> ref;
		cout << "Enter No of Issue Copies: ";
		cin >> issue;
	}
	void display()
	{
		cout << "ISSN: " << issn << endl;
		cout << "Title: " << title << endl;
		cout << "Authors: ";
		authors->print();                               // displaying the information of books
	
		cout << "No of Reference Copies: " << ref << endl;
		cout << "No of Issue Copies: " << issue << endl;
	}
	void setIssn(int issn)
	{
		this->issn = issn;                             // setter to get issn
	}
	void setTitle(string title)
	{                                             // setter to get title of book
		this->title = title;
	}
	void setAuthor(SinglyLinkedList* author)
	{
		this->authors = author;                  // setter to get names of author
	}
	void setRef(int ref)
	{
		this->ref = ref;                             // setter to keep record of reference books
	}
	void setIssue(int issue)
	{                        // setter to keep record of issuable books
		this->issue = issue;
	}
	int getIssn()
	{
		return issn;
	}                                      // getter to set issn
	string getTitle()
	{
		return title;           // getter to set title
	}
	int getRef()
	{
		return ref;          // getter to set reference books
	}
	int getIssue()
	{
		return issue;                           // getter to set issuable books
	}
	int getAuthorCount()
	{
		return authorcount;                  // getter to set author count
	}

};
class hashitem 
	{
	public:
		int key;
		Book* book;                                      // a class hashitem to be used as a helper class for hash table
		hashitem* next;                        // a book pointer to access the information of a book
		hashitem(int key, Book* book)
		{
			this->key = key;
			this->book = book;
			next = NULL;
		}
	};
class HashTable
{
private:
	vector<hashitem*> hashTable;                           // vector having the information of issns
	int hashTableSize;
public:
	HashTable(int hashTableSize)
	{
		this->hashTableSize = hashTableSize;                // constructor
		hashTable.resize(hashTableSize);
	}
	int hashFunction(int key)
	{
		return key % hashTableSize;                          // funtion to determine the suitable place for a particular book
	}
	void insert(int key, Book* book)
	{
		int index = hashFunction(key);
		hashitem* newItem = new hashitem(key, book);                 // a function to insert the books by using key
		if (hashTable[index] == NULL)
		{
			hashTable[index] = newItem;
		}
		else
		{
			hashitem* temp = hashTable[index];
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newItem;
		}
	}
// display function which will print  all the books in the table
	void display()
	{
		for (int i = 0; i < hashTableSize; i++)
		{
			hashitem* temp = hashTable[i];
			while (temp != NULL)
			{
				cout << "Key(ISSN) : " << temp->key << endl;
				temp->book->display();
				temp = temp->next;
			}
		}
	}
	// search function which will search the book by its issn
	void search(int key)
	{
		int index = hashFunction(key);
		hashitem* temp = hashTable[index];
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				cout << "Book Found" << endl;
				temp->book->display();
				return;
			}
			temp = temp->next;
		}
		cout << "Book Not Found" << endl;
	}
	void DeleteABookRecord(int key)
	{
		int index = hashFunction(key);
		hashitem* temp = hashTable[index];
		hashitem* prev = NULL;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (prev == NULL)
				{
					hashTable[index] = temp->next;
				}
				else
				{
					prev->next = temp->next;
				}
				delete temp;
				cout << "Book Deleted" << endl;
				return;
			}
			prev = temp;
			temp = temp->next;
		}
		cout << "Book Not Found" << endl;
	}
	void update(int key)
	{
		int index = hashFunction(key);
		hashitem* temp = hashTable[index];
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				temp->book->updatebook();
				cout << "Book Updated" << endl;
				return;
			}
			temp = temp->next;
		}
		cout << "Book Not Found" << endl;
	}
	//function 1 Create a book record(C) - a new book record is created and added to the hashtable
	void createbook()
	{
		int issn;
		string title;
		int ref;
		int issue;
		int authorcount;
		SinglyLinkedList* authors = new SinglyLinkedList();
		cout << "Enter ISSN: ";
		cin >> issn;
		cout << "Enter Title: ";
		cin.ignore();
		getline(cin, title);
		cout << "Enter No of Authors : ";
		cin >> authorcount;
		cin.ignore();

		authors->headreset();

		while (authorcount == 0) {
			cout << "Book cant have 0 author please enter author : ";
			cin >> authorcount;
		}

		string authorName;

		for (int i = 0; i < authorcount; i++)
		{
			cout << "Enter Author " << i + 1 << " : ";
			getline(cin, authorName);
			authors->insert(authorName);

		}
		cout << "Enter No of Reference Copies: ";
		cin >> ref;
		cout << "Enter No of Issue Copies: ";
		cin >> issue;
		Book* book = new Book(issn, title, ref, issue, authors);
		insert(issn, book);
	}
	//function 2 Review a book record(R) --Given an ISSN display the complete book record
	void reviewbook(int issn)
	{
		search(issn);
	}
	
	};
	// a menu based main function to test the above functions
	int main()
	{
		HashTable* hashTable = new HashTable(10);
		int choice;
		int issn;
		
		cout <<              "                    ----------- Welcome to Library Managment System --------------" << endl;
         cout << endl;
         cout << "                    ----------- Choose from the following options  ---------------" << endl;
         cout << endl;


		
		
		
		
		do
		{
			cout << "1. Create a book record(C)" << endl;
			cout << "2. Review a book record(R)" << endl;
			cout << "3. Update a book record(U)" << endl;
			cout << "4. Delete a book record(D)" << endl;
			cout << "5. Display all books" << endl;
			cout << "6. Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			
			system ("cls");
			switch (choice)
			{
			case 1:
				hashTable->createbook();
				cout << endl;
				break;
			case 2:
				cout << "Enter ISSN: ";
				cin >> issn;
				hashTable->reviewbook(issn);
				cout << endl;
				break;
			case 3:
				cout << "Enter ISSN: ";
				cin >> issn;
				hashTable->update(issn);
				cout << endl;
				break;
			case 4:
				cout << "Enter ISSN: ";
				cin >> issn;
				hashTable->DeleteABookRecord(issn);
				cout << endl;
				break;
			case 5:
				hashTable->display();
				cout << endl;
				break;
			case 6:
				break;
			default:
				cout << "Invalid Choice" << endl;
			}
		} while (choice != 6);
		
		
	      cout << "                             ------------ THANK YOU :) ------------" << endl;
	      cout << endl;
		
		return 0;
	}
		
	
	
