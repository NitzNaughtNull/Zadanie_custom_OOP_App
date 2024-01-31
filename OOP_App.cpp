#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Book {
private:
    std::string title;
    std::string author;
    int year;

public:
    Book(const std::string& title, const std::string& author, int year)
        : title(title), author(author), year(year) {}

    void displayInfo() const {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year << "\n\n";
    }

    std::string getTitle() const {
        return title;
    }

    void editBook(const std::string& newTitle, const std::string& newAuthor, int newYear) {
        title = newTitle;
        author = newAuthor;
        year = newYear;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const std::string& title) {
        auto it = std::remove_if(books.begin(), books.end(), [title](const Book& book) {
            return book.getTitle() == title;
        });

        books.erase(it, books.end());
    }

    void displayBooks() const {
        std::cout << "Library Contents:\n";
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void editBook(const std::string& title, const std::string& newTitle, const std::string& newAuthor, int newYear) {
        auto it = std::find_if(books.begin(), books.end(), [title](const Book& book) {
            return book.getTitle() == title;
        });

        if (it != books.end()) {
            it->editBook(newTitle, newAuthor, newYear);
            std::cout << "Book edited successfully.\n";
        } else {
            std::cout << "Book not found.\n";
        }
    }
};

int main() {
    Library library;

    Book book1("Mroczny tron", "Django Wexler", 2012);
    Book book2("Zwiadowcy", "John Flanagan", 2008);
    Book book3("1984", "George Orwell", 1949);
    Book book4("Czwarte skrzydlo", "Rebecca Varros", 2023);

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    int choice;
    do {
        library.displayBooks();

        std::cout << "Choose operation:\n";
        std::cout << "1. Add a new book\n";
        std::cout << "2. Remove a book\n";
        std::cout << "3. Edit a book\n";
        std::cout << "4. Exit\n";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string newTitle, newAuthor;
                int newYear;
                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, newTitle);
                std::cout << "Enter author: ";
                std::getline(std::cin, newAuthor);
                std::cout << "Enter year: ";
                std::cin >> newYear;

                Book newBook(newTitle, newAuthor, newYear);
                library.addBook(newBook);
                break;
            }
            case 2: {
                std::string titleToRemove;
                std::cout << "Enter title of the book to remove: ";
                std::cin.ignore();
                std::getline(std::cin, titleToRemove);

                library.removeBook(titleToRemove);
                break;
            }
            case 3: {
                std::string titleToEdit, newTitle, newAuthor;
                int newYear;

                std::cout << "Enter title of the book to edit: ";
                std::cin.ignore();
                std::getline(std::cin, titleToEdit);

                std::cout << "Enter new title: ";
                std::getline(std::cin, newTitle);
                std::cout << "Enter new author: ";
                std::getline(std::cin, newAuthor);
                std::cout << "Enter new year: ";
                std::cin >> newYear;

                library.editBook(titleToEdit, newTitle, newAuthor, newYear);
                break;
            }
            case 4:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
