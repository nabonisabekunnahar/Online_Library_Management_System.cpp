#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int id;
    bool available;

public:
    Book(const string& title, const string& author, int id, bool available)
        : title(title), author(author), id(id), available(available) {}

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    int getId() const {
        return id;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }

    void displayInfo() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ID: " << id << endl;
        cout << "Availability: " << (available ? "Available" : "Not Available") << endl;
        cout << "---------------------" << endl;
    }
};

class Library {
private:
    string Docfile;

public:
    Library(const string& Docfile)
        : Docfile(Docfile) {}

    // Add a book to the library
    void addBook() {
        string title, author;
        int id;
        bool available;

        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter book author: ";
        getline(cin, author);

        cout << "Enter book ID: ";
        cin >> id;

        cout << "Is the book available? (1 for available, 0 for not available): ";
        cin >> available;

        Book book(title, author, id, available);

        ofstream file(Docfile, ios::app);
        if (file.is_open()) {
            file << book.getTitle() << endl;
            file << book.getAuthor() << endl;
            file << book.getId() << endl;
            file << book.isAvailable() << endl;
            file.close();
            cout << "Book added successfully." << endl;
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Remove a book from the library
    void removeBook() {
        int id;
        cout << "Enter the ID of the book to remove: ";
        cin >> id;

        ifstream Listfile(Docfile);
        ofstream tempFile("temp.txt");
        if (Listfile.is_open() && tempFile.is_open()) {
            string line;
            bool found = false;
            while (getline(Listfile, line)) {
                string title = line;
                getline(Listfile, line);
                string author = line;
                getline(Listfile, line);
                int bookId = stoi(line);
                getline(Listfile, line);
                bool available = (line == "1");

                if (bookId == id) {
                    found = true;
                    continue; // Skip removing the book from temp file
                }

                tempFile << title << endl;
                tempFile << author << endl;
                tempFile << bookId << endl;
                tempFile << available << endl;
            }
            Listfile.close();
            tempFile.close();

            if (found) {
                remove(Docfile.c_str());
                rename("temp.txt", Docfile.c_str());
                cout << "Book removed successfully." << endl;
            } else {
                remove("temp.txt");
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Unable to open file for reading or writing." << endl;
        }
    }

    // Display all books in the library
    void displayAllBooks() {
        ifstream Listfile(Docfile);
        if (Listfile.is_open()) {
            string line;
            bool found = false;
            while (getline(Listfile, line)) {
                string title = line;
                getline(Listfile, line);
                string author = line;
                getline(Listfile, line);
                int id = stoi(line);
                getline(Listfile, line);
                bool available = (line == "1");

                Book book(title, author, id, available);
                book.displayInfo();

                found = true;
            }

            if (!found) {
                cout << "No books available in the library." << endl;
            }

            Listfile.close();
        } else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};

class Student {
private:
    string name;

public:
    Student(const string& name)
        : name(name) {}

    // Borrow a book from the library
    void borrowBook(const string& Docfile) {
        int id;
        cout << "Enter the ID of the book to borrow: ";
        cin >> id;

        ifstream Listfile(Docfile);
        ofstream tempFile("temp.txt");
        if (Listfile.is_open() && tempFile.is_open()) {
            string line;
            bool found = false;

            while (getline(Listfile, line)) {
                string title = line;
                getline(Listfile, line);
                string author = line;
                getline(Listfile, line);
                int bookId = stoi(line);
                getline(Listfile, line);
                bool available = (line == "1");

                if (bookId == id) {
                    found = true;
                    if (available) {
                        available = false;
                        cout << "Book borrowed successfully." << endl;
                    } else {
                        cout << "Book is not available for borrowing." << endl;
                    }
                }

                tempFile << title << endl;
                tempFile << author << endl;
                tempFile << bookId << endl;
                tempFile << available << endl;
            }
            Listfile.close();
            tempFile.close();

            if (found) {
                remove(Docfile.c_str());
                rename("temp.txt", Docfile.c_str());
            } else {
                remove("temp.txt");
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Unable to open file for reading or writing." << endl;
        }
    }

    // Return a borrowed book to the library
    void returnBook(const string& Docfile) {
        int id;
        cout << "Enter the ID of the book to return: ";
        cin >> id;

        ifstream Listfile(Docfile);
        ofstream tempFile("temp.txt");
        if (Listfile.is_open() && tempFile.is_open()) {
            string line;
            bool found = false;

            while (getline(Listfile, line)) {
                string title = line;
                getline(Listfile, line);
                string author = line;
                getline(Listfile, line);
                int bookId = stoi(line);
                getline(Listfile, line);
                bool available = (line == "1");

                if (bookId == id) {
                    found = true;
                    if (!available) {
                        available = true;
                        cout << "Book returned successfully." << endl;
                    } else {
                        cout << "Book is already available in the library." << endl;
                    }
                }

                tempFile << title << endl;
                tempFile << author << endl;
                tempFile << bookId << endl;
                tempFile << available << endl;
            }
            Listfile.close();
            tempFile.close();

            if (found) {
                remove(Docfile.c_str());
                rename("temp.txt", Docfile.c_str());
            } else {
                remove("temp.txt");
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Unable to open file for reading or writing." << endl;
        }
    }
};

int main() {
    Library library("books.txt");
    Student student("naboni");

    int choice;
    do {
        cout << "---------------------" << endl;
        cout << "Online Library Management System" << endl;
        cout << "---------------------" << endl;
        cout << "1. Librarian Menu" << endl;
        cout << "2. Student Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "---------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    int librarianChoice;
                    do {
                        cout << "---------------------" << endl;
                        cout << "Librarian Menu" << endl;
                        cout << "---------------------" << endl;
                        cout << "1. Add a book" << endl;
                        cout << "2. Remove a book" << endl;
                        cout << "3. Display all books" << endl;
                        cout << "4. Go back" << endl;
                        cout << "---------------------" << endl;
                        cout << "Enter your choice: ";
                        cin >> librarianChoice;

                        switch (librarianChoice) {
                            case 1:
                                library.addBook();
                                break;
                            case 2:
                                library.removeBook();
                                break;
                            case 3:
                                library.displayAllBooks();
                                break;
                            case 4:
                                cout << "Returning to main menu." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }

                        cout << endl;
                    } while (librarianChoice != 4);
                }
                break;
            case 2:
                {
                    int studentChoice;
                    do {
                        cout << "---------------------" << endl;
                        cout << "Student Menu" << endl;
                        cout << "---------------------" << endl;
                        cout << "1. Borrow a book" << endl;
                        cout << "2. Return a book" << endl;
                        cout << "3. Go back" << endl;
                        cout << "---------------------" << endl;
                        cout << "Enter your choice: ";
                        cin >> studentChoice;

                        switch (studentChoice) {
                            case 1:
                                student.borrowBook("books.txt");
                                break;
                            case 2:
                                student.returnBook("books.txt");
                                break;
                            case 3:
                                cout << "Returning to main menu." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }

                        cout << endl;
                    } while (studentChoice != 3);
                }
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 3);

    return 0;
}

