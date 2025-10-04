#ifndef LIB_H
#define LIB_H

#include <string>
#include <vector>

using namespace std;

class Lend
{
private:
    int user_id;
    string lend_date; // Formato esperado: "YYYY-MM-DD"
    string return_date;
protected:
    friend class book;
    void setUserId(int user_id);
    void setLendDate(const string& lend_date);
    void setReturnDate(const string& return_date);
public:
    Lend();
    Lend(int user_id, const string& lend_date, const string& return_date = "");
    int getUserId() const;
    string getLendDate() const;
    string getReturnDate() const;
    ~Lend();
};

class book
{
private:
    int id;
    string title;
    string author;
    int year;
    string category;
    bool lended = false;
    int times_lended = 0;
    vector<Lend> lends_history;
public:
    book();
    book(int id, const string& title, const string& author, int year, const string& category);
    
    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getYear() const;
    string getCategory() const;
    bool isLended() const;
    int getTimesLended() const;
    const vector<Lend>& getLendsHistory() const;

    void lendBook(int user_id, const string& lend_date);
    void returnBook(const string& return_date);
    
    ~book();
};

class User
{
protected:
    int id;
public:
    User();
    User(int id);
    int getId() const;
    virtual ~User();
};

class Student : public User
{
private:
    int year;
public:
    Student();
    Student(int id, int year);
    int getYear() const;
    ~Student();
};

class Teacher : public User
{
private:
    string department;
public:
    Teacher();
    Teacher(int id, const string& department);
    string getDepartment() const;
    ~Teacher();
};

struct UserLendCounter {
    int userId;
    int lendCount;
};

string toLower(string text);

void listAvailableBooks(const vector<book>& books);
void listLentBooks(const vector<book>& books);
void searchByAuthorOrCategory(const vector<book>& books, const string& query);
void showTopBorrowedBooks(const vector<book>& books, int count);
void showTopBorrowerInPeriod(const vector<book>& books, const vector<User*>& users, const string& startDate, const string& endDate);

#endif