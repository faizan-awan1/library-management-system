#include <iostream>
#include <string>
using namespace std;
// chcp 65001
// library_manager.exe


enum BookStatus {
    AVAILABLE,
    ISSUED,
    RESERVED
};

enum Genre {
    FICTION,
    NON_FICTION,
    SCIENCE,
    HISTORY,
    TECHNOLOGY
};

struct Book {
    int     id;
    string  title;
    string  author;
    Genre   genre;
    BookStatus status;
};

struct Member {
    int    id;
    string name;
    int    issuedBookId;   // -1 means no book issued
};

const int MAX_BOOKS   = 100;
const int MAX_MEMBERS = 50;

Book*   books[MAX_BOOKS];
Member* members[MAX_MEMBERS];
int bookCount   = 0;
int memberCount = 0;
int nextBookId   = 1;
int nextMemberId = 1;

string enumToString(BookStatus s) {
    if (s == AVAILABLE) return "Available";
    if (s == ISSUED)    return "Issued";
    return "Reserved";
}

string enumToString(Genre g) {
    if (g == FICTION)     return "Fiction";
    if (g == NON_FICTION) return "Non-Fiction";
    if (g == SCIENCE)     return "Science";
    if (g == HISTORY)     return "History";
    return "Technology";
}

Book* findBook(int id) {
    for (int i = 0; i < bookCount; i++)
        if (books[i]->id == id) return books[i];
    return nullptr;
}

Member* findMember(int id) {
    for (int i = 0; i < memberCount; i++)
        if (members[i]->id == id) return members[i];
    return nullptr;
}

 Book* findBookByTitle(const string& title) {
    for (int i = 0; i < bookCount; i++)
        if (books[i]->title == title) return books[i];
    return nullptr;
}


void displayBook(const Book& b) {
    cout << "\n  ID      : " << b.id
         << "\n  Title   : " << b.title
         << "\n  Author  : " << b.author
         << "\n  Genre   : " << enumToString(b.genre)
         << "\n  Status  : " << enumToString(b.status)
         << "\n  -------------------------";
}

void displayMember(const Member& m) {
    cout << "\n  ID           : " << m.id
         << "\n  Name         : " << m.name
         << "\n  Issued Book  : " << (m.issuedBookId == -1 ? "None" : to_string(m.issuedBookId))
         << "\n  -------------------------";
}

void displayAllBooks() {
    if (bookCount == 0) { cout << "\n  No books in library.\n"; return; }
    cout << "\n===== ALL BOOKS =====";
    for (int i = 0; i < bookCount; i++)
        displayBook(*books[i]);
    cout << endl;
}

void displayAllMembers() {
    if (memberCount == 0) { cout << "\n  No members registered.\n"; return; }
    cout << "\n===== ALL MEMBERS =====";
    for (int i = 0; i < memberCount; i++)
        displayMember(*members[i]);
    cout << endl;
}


void addBook() {
    if (bookCount >= MAX_BOOKS) { cout << "  Library full!\n"; return; }

    Book* b = new Book();    
    b->id     = nextBookId++;
    b->status = AVAILABLE;

    cout << "\n  Enter Title  : "; cin.ignore(); getline(cin, b->title);
    cout << "  Enter Author : "; getline(cin, b->author);

    cout << "  Genre (0=Fiction, 1=Non-Fiction, 2=Science, 3=History, 4=Technology): ";
    int g; cin >> g;
    b->genre = static_cast<Genre>(g);

    books[bookCount++] = b;
    cout << "  Book added with ID: " << b->id << endl;
}

void addMember() {
    if (memberCount >= MAX_MEMBERS) { cout << "  Member limit reached!\n"; return; }

    Member* m = new Member();   // dynamic memory
    m->id          = nextMemberId++;
    m->issuedBookId = -1;

    cout << "\n  Enter Member Name: "; cin.ignore(); getline(cin, m->name);

    members[memberCount++] = m;
    cout << "  Member added with ID: " << m->id << endl;
}

void issueBook() {
    int bid, mid;
    cout << "\n  Enter Book ID   : "; cin >> bid;
    cout << "  Enter Member ID : "; cin >> mid;

    Book*   b = findBook(bid);
    Member* m = findMember(mid);

    if (!b) { cout << "  Book not found!\n";   return; }
    if (!m) { cout << "  Member not found!\n"; return; }
    if (b->status != AVAILABLE) { cout << "  Book is not available!\n"; return; }
    if (m->issuedBookId != -1)  { cout << "  Member already has a book issued!\n"; return; }

    b->status       = ISSUED;
    m->issuedBookId = bid;
    cout << "  Book \"" << b->title << "\" issued to " << m->name << endl;
}

void returnBook() {
    int mid;
    cout << "\n  Enter Member ID: "; cin >> mid;

    Member* m = findMember(mid);
    if (!m)                    { cout << "  Member not found!\n";          return; }
    if (m->issuedBookId == -1) { cout << "  No book issued to this member.\n"; return; }

    Book* b = findBook(m->issuedBookId);
    if (b) b->status = AVAILABLE;

    cout << "  Book \"" << (b ? b->title : "?") << "\" returned successfully.\n";
    m->issuedBookId = -1;
}

void searchBook() {
    cout << "\n  Search by (1) ID  (2) Title: ";
    int ch; cin >> ch;

    if (ch == 1) {
        int id; cout << "  Enter Book ID: "; cin >> id;
        Book* b = findBook(id);
        if (b) displayBook(*b); else cout << "  Not found.\n";
    } else {
        string title; cout << "  Enter Title: "; cin.ignore(); getline(cin, title);
        Book* b = findBookByTitle(title);
        if (b) displayBook(*b); else cout << "  Not found.\n";
    }
}

void deleteBook() {
    int id; cout << "\n  Enter Book ID to delete: "; cin >> id;
    for (int i = 0; i < bookCount; i++) {
        if (books[i]->id == id) {
            if (books[i]->status == ISSUED) { cout << "  Cannot delete — book is currently issued!\n"; return; }
            delete books[i];                // free memory
            for (int j = i; j < bookCount - 1; j++) books[j] = books[j+1];
            bookCount--;
            cout << "  Book deleted.\n";
            return;
        }
    }
    cout << "  Book not found.\n";
}

void showMenu();   // forward declaration

void handleChoice(int choice) {
    switch (choice) {
        case 1:  addBook();         break;
        case 2:  addMember();       break;
        case 3:  issueBook();       break;
        case 4:  returnBook();      break;
        case 5:  searchBook();      break;
        case 6:  displayAllBooks(); break;
        case 7:  displayAllMembers(); break;
        case 8:  deleteBook();      break;
        case 0:
            cout << "\n  Exiting... Thank you!\n";
            // free all dynamic memory before exit
            for (int i = 0; i < bookCount;   i++) delete books[i];
            for (int i = 0; i < memberCount; i++) delete members[i];
            return;
        default:
            cout << "  Invalid choice. Try again.\n";
    }
    showMenu();   // recursive call
}

void showMenu() {
    cout << "\n╔══════════════════════════════╗"
         << "\n║    LIBRARY MANAGEMENT SYS    ║"
         << "\n╠══════════════════════════════╣"
         << "\n║  1. Add Book                 ║"
         << "\n║  2. Add Member               ║"
         << "\n║  3. Issue Book               ║"
         << "\n║  4. Return Book              ║"
         << "\n║  5. Search Book              ║"
         << "\n║  6. View All Books           ║"
         << "\n║  7. View All Members         ║"
         << "\n║  8. Delete Book              ║"
         << "\n║  0. Exit                     ║"
         << "\n╚══════════════════════════════╝"
         << "\n  Enter choice: ";

    int ch; cin >> ch;
    handleChoice(ch);
}

int main() {
    cout << "  Welcome to Library Management System\n";
    showMenu();
    return 0;
}
