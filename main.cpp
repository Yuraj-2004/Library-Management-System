#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    int pages;
    float price;
    bool isIssued; // Added to track if a book is issued

    Book(string t = "", string a = "", int p = 0, float pr = 0.0)
        : title(t), author(a), pages(p), price(pr), isIssued(false) {} // Initialize isIssued to false
};

class Library {
private:
    static const int MAX_BOOKS = 100; // Maximum number of books
    Book books[MAX_BOOKS]; // Array of Book objects
    int count; // Current number of books

public:
    Library() : count(0) {} // Initialize count to 0

    void addBook(const Book& book) {
        if (count < MAX_BOOKS) {
            books[count] = book; // Add the book to the array
            count++;
            cout << "Book added successfully!" << endl;
        } else {
            cout << "Library is full, cannot add more books." << endl;
        }
    }

    void displayBooks() {
        if (count == 0) {
            cout << "No books in the library." << endl;
            return;
        }
        cout << "Books in the Library:" << endl;
        for (int i = 0; i < count; i++) {
            cout << "Title: " << books[i].title 
                 << ", Author: " << books[i].author 
                 << ", Pages: " << books[i].pages 
                 << ", Price: $" << books[i].price 
                 << ", Issued: " << (books[i].isIssued ? "Yes" : "No") << endl; // Display issued status
        }
    }

    void searchBook(const string& title) {
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                cout << "Book found: " << endl;
                cout << "Title: " << books[i].title 
                     << ", Author: " << books[i].author 
                     << ", Pages: " << books[i].pages 
                     << ", Price: $" << books[i].price 
                     << ", Issued: " << (books[i].isIssued ? "Yes" : "No") << endl; // Display issued status
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void listBooksByAuthor(const string& author) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (books[i].author == author) {
                cout << books[i].title << ", " << books[i].author 
                     << ", Pages: " << books[i].pages 
                     << ", Price: $" << books[i].price 
                     << ", Issued: " << (books[i].isIssued ? "Yes" : "No") << endl; // Display issued status
                found = true;
            }
        }
        if (!found) {
            cout << "No books found by author " << author << "." << endl;
        }
    }

    int getBookCount() const {
        return count;
    }

    void issueBook(const string& title) {
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                if (!books[i].isIssued) {
                    books[i].isIssued = true; // Mark book as issued
                    cout << "Book '" << title << "' has been issued." << endl;
                } else {
                    cout << "Book '" << title << "' is already issued." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void returnBook(const string& title) {
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                if (books[i].isIssued) {
                    books[i].isIssued = false; // Mark book as not issued
                    cout << "Book '" << title << "' has been returned." << endl;
                } else {
                    cout << "Book '" << title << "' was not issued." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }
};

void adminMenu(Library& library) {
    int choice;
    do {
        cout << "\nAdmin Menu" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. List Books by Author" << endl;
        cout << "4. Count Books in Library" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                int pages;
                float price;
                cout << "Enter title: ";
                cin.ignore(); // Clear newline character from input buffer
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter pages: ";
                cin >> pages;
                cout << "Enter price: ";
                cin >> price;
                library.addBook(Book(title, author, pages, price));
                break;
            }
            case 2:
                library.displayBooks();
                break;
            case 3: {
                string author;
                cout << "Enter author name: ";
                cin.ignore();
                getline(cin, author);
                library.listBooksByAuthor(author);
                break;
            }
            case 4:
                cout << "Total books in library: " << library.getBookCount() << endl;
                break;
            case 5:
                cout << "Exiting admin menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

void studentMenu(Library& library) {
    int choice;
    do {
        cout << "\nStudent Menu" << endl;
        cout << "1. Search Book" << endl;
        cout << "2. Issue Book" << endl; // New option for issuing a book
        cout << "3. Return Book" << endl; // New option for returning a book
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title;
                cout << "Enter title to search: ";
                cin.ignore();
                getline(cin, title);
                library.searchBook(title);
                break;
            }
            case 2: {
                string title;
                cout << "Enter title to issue: ";
                cin.ignore();
                getline(cin, title);
                library.issueBook(title); // Call the issueBook function
                break;
            }
            case 3: {
                string title;
                cout << "Enter title to return: ";
                cin.ignore();
                getline(cin, title);
                library.returnBook(title); // Call the returnBook function
                break;
            }
            case 4:
                cout << "Exiting student menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}

int main() {
    Library library;
    int userType;

    do {
        cout << "Welcome to the Library Management System" << endl;
        cout << "Select User Type: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Student" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                adminMenu(library);
                break;
            case 2:
                studentMenu(library);
                break;
            case 3:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid user type selected. Please try again." << endl;
        }
    } while (userType != 3);

    return 0;
}
