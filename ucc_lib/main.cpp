#include "lib.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<book> allBooks;
    vector<User*> allUsers;

    cout << ">>> Cargando datos de prueba..." << endl;
    allBooks.push_back(book(101, "Cien Anos de Soledad", "Gabriel Garcia Marquez", 1967, "Realismo Magico"));
    allBooks.push_back(book(102, "El Senor de los Anillos", "J.R.R. Tolkien", 1954, "Fantasia"));
    allBooks.push_back(book(103, "1984", "George Orwell", 1949, "Distopia"));
    allBooks.push_back(book(104, "Un Mundo Feliz", "Aldous Huxley", 1932, "Distopia"));
    allBooks.push_back(book(105, "Fisica Universitaria", "Sears y Zemansky", 2009, "Ciencia"));
    allUsers.push_back(new Student(2001, 3));
    allUsers.push_back(new Teacher(3001, "Ciencias de la Computacion"));
    allUsers.push_back(new Student(2002, 1));
    allBooks[1].lendBook(2001, "2023-05-10"); allBooks[1].returnBook("2023-06-01");
    allBooks[1].lendBook(3001, "2023-08-15"); allBooks[1].returnBook("2023-09-01");
    allBooks[1].lendBook(2002, "2024-02-20"); allBooks[1].returnBook("2024-03-10");
    allBooks[4].lendBook(3001, "2023-03-01"); allBooks[4].returnBook("2023-07-01");
    allBooks[4].lendBook(3001, "2024-08-01");
    allBooks[2].lendBook(2001, "2024-01-15"); allBooks[2].returnBook("2024-02-01");
    cout << ">>> Datos de prueba cargados." << endl << endl;

    listAvailableBooks(allBooks);
    cout << endl;
    listLentBooks(allBooks);
    cout << endl;

    searchByAuthorOrCategory(allBooks, "distopia");
    cout << endl;
    searchByAuthorOrCategory(allBooks, "Marquez");
    cout << endl;

    showTopBorrowedBooks(allBooks, 3);
    cout << endl;

    cout << "Buscando en todo el historial (2023-01-01 a 2025-12-31)..." << endl;
    showTopBorrowerInPeriod(allBooks, allUsers, "2023-01-01", "2025-12-31");
    cout << endl;
    
    cout << "Buscando solo en el año 2023..." << endl;
    showTopBorrowerInPeriod(allBooks, allUsers, "2023-01-01", "2023-12-31");
    cout << endl;

    for (size_t i = 0; i < allUsers.size(); ++i) {
        delete allUsers[i];
    }
    allUsers.clear();

    return 0;
}
