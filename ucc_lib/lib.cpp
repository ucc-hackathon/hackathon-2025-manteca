#include "lib.h"
#include <iostream>
#include <vector>

Lend::Lend() : user_id(0), lend_date(""), return_date("") {}
Lend::Lend(int user_id, const string& lend_date, const string& return_date) : user_id(user_id), lend_date(lend_date), return_date(return_date) {}
Lend::~Lend() {}
void Lend::setUserId(int user_id) { this->user_id = user_id; }
void Lend::setLendDate(const string& lend_date) { this->lend_date = lend_date; }
void Lend::setReturnDate(const string& return_date) { this->return_date = return_date; }
int Lend::getUserId() const { return user_id; }
string Lend::getLendDate() const { return lend_date; }
string Lend::getReturnDate() const { return return_date; }

book::book() : id(0), title(""), author(""), year(0), category(""), lended(false), times_lended(0) {}
book::book(int id, const string& title, const string& author, int year, const string& category) : id(id), title(title), author(author), year(year), category(category), lended(false), times_lended(0) {}
book::~book() {}
void book::lendBook(int user_id, const string& lend_date) {
    if (!lended) {
        lended = true;
        times_lended++;
        lends_history.push_back(Lend(user_id, lend_date));
    }
}
void book::returnBook(const string& return_date) {
    if (lended && !lends_history.empty()) {
        lended = false;
        lends_history.back().setReturnDate(return_date);
    }
}
int book::getId() const { return id; }
string book::getTitle() const { return title; }
string book::getAuthor() const { return author; }
int book::getYear() const { return year; }
string book::getCategory() const { return category; }
bool book::isLended() const { return lended; }
int book::getTimesLended() const { return times_lended; }
const vector<Lend>& book::getLendsHistory() const { return lends_history; }

User::User() : id(0) {}
User::User(int id) : id(id) {}
int User::getId() const { return id; }
User::~User() {}

Student::Student() : User(0), year(0) {}
Student::Student(int id, int year) : User(id), year(year) {}
int Student::getYear() const { return year; }
Student::~Student() {}

Teacher::Teacher() : User(0), department("") {}
Teacher::Teacher(int id, const string& department) : User(id), department(department) {}
string Teacher::getDepartment() const { return department; }
Teacher::~Teacher() {}

string toLower(string text) {
    string lowerText = "";
    for (char c : text) {
        lowerText += tolower(c);
    }
    return lowerText;
}

void listAvailableBooks(const vector<book>& books) {
    cout << "--- Libros Disponibles ---" << endl;
    for (size_t i = 0; i < books.size(); ++i) {
        if (!books[i].isLended()) {
            cout << "ID: " << books[i].getId() << ", Titulo: " << books[i].getTitle() << ", Autor: " << books[i].getAuthor() << endl;
        }
    }
    cout << "--------------------------" << endl;
}

void listLentBooks(const vector<book>& books) {
    cout << "--- Libros Prestados ---" << endl;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].isLended()) {
            cout << "ID: " << books[i].getId() << ", Titulo: " << books[i].getTitle() << ", Prestado a User ID: " << books[i].getLendsHistory().back().getUserId() << endl;
        }
    }
    cout << "------------------------" << endl;
}

void searchByAuthorOrCategory(const vector<book>& books, const string& query) {
    cout << "--- Resultados de Busqueda para '" << query << "' ---" << endl;
    string queryLower = toLower(query);

    for (size_t i = 0; i < books.size(); ++i) {
        string authorLower = toLower(books[i].getAuthor());
        string categoryLower = toLower(books[i].getCategory());

        if (authorLower.find(queryLower) != string::npos || categoryLower.find(queryLower) != string::npos) {
            cout << "ID: " << books[i].getId() << ", Titulo: " << books[i].getTitle() << ", Autor: " << books[i].getAuthor() << ", Categoria: " << books[i].getCategory() << endl;
        }
    }
    cout << "------------------------------------------" << endl;
}

void showTopBorrowedBooks(const vector<book>& books, int count) {
    vector<book> sortedBooks = books;

    for (size_t i = 0; i < sortedBooks.size(); ++i) {
        size_t max_index = i;
        for (size_t j = i + 1; j < sortedBooks.size(); ++j) {
            if (sortedBooks[j].getTimesLended() > sortedBooks[max_index].getTimesLended()) {
                max_index = j;
            }
        }
        book temp = sortedBooks[i];
        sortedBooks[i] = sortedBooks[max_index];
        sortedBooks[max_index] = temp;
    }

    cout << "--- Top " << count << " Libros Mas Prestados ---" << endl;
    for (int i = 0; i < count && i < sortedBooks.size(); ++i) {
        cout << i + 1 << ". " << sortedBooks[i].getTitle() << " (Prestado " << sortedBooks[i].getTimesLended() << " veces)" << endl;
    }
    cout << "---------------------------------" << endl;
}

void showTopBorrowerInPeriod(const vector<book>& books, const vector<User*>& users, const string& startDate, const string& endDate) {
    vector<UserLendCounter> counters;

    for (size_t i = 0; i < books.size(); ++i) {
        const vector<Lend>& history = books[i].getLendsHistory();
        for (size_t j = 0; j < history.size(); ++j) {
            if (history[j].getLendDate() >= startDate && history[j].getLendDate() <= endDate) {
                int currentUserId = history[j].getUserId();
                bool userFound = false;
                for (size_t k = 0; k < counters.size(); ++k) {
                    if (counters[k].userId == currentUserId) {
                        counters[k].lendCount++;
                        userFound = true;
                        break;
                    }
                }
                if (!userFound) {
                    UserLendCounter newCounter;
                    newCounter.userId = currentUserId;
                    newCounter.lendCount = 1;
                    counters.push_back(newCounter);
                }
            }
        }
    }

    if (counters.empty()) {
        cout << "No hubo prestamos en el periodo de " << startDate << " a " << endDate << "." << endl;
        return;
    }

    int topUserId = 0;
    int maxLends = 0;
    for (size_t i = 0; i < counters.size(); ++i) {
        if (counters[i].lendCount > maxLends) {
            maxLends = counters[i].lendCount;
            topUserId = counters[i].userId;
        }
    }

    User* topUser = nullptr;
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getId() == topUserId) {
            topUser = users[i];
            break;
        }
    }

    cout << "--- Usuario con Mas Prestamos entre " << startDate << " y " << endDate << " ---" << endl;
    if (topUser) {
        if (Student* s = dynamic_cast<Student*>(topUser)) {
            cout << "Estudiante ID: " << s->getId() << ", Anio: " << s->getYear() << " (con " << maxLends << " libros prestados)" << endl;
        } else if (Teacher* t = dynamic_cast<Teacher*>(topUser)) {
            cout << "Profesor ID: " << t->getId() << ", Depto: " << t->getDepartment() << " (con " << maxLends << " libros prestados)" << endl;
        }
    }
    cout << "---------------------------------------------------------" << endl;
}