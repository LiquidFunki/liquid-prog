#include "book.h"

//Publishing house


PublishingHouse::PublishingHouse() : version(), name() { };

PublishingHouse::PublishingHouse(string version, string name) : version(version), name(name) { };

PublishingHouse::PublishingHouse(const PublishingHouse &temp) : version(temp.version), name(temp.name) { }

PublishingHouse::~PublishingHouse() { };

string PublishingHouse::getVersion() const{ return this->version; };

string PublishingHouse::getName() const{ return this->name; };

void PublishingHouse::setVersion(const string Version) { this->version = Version; };

void PublishingHouse::setName(const string Name) { this->name = Name; };

void PublishingHouse::printpb() {
    cout << version;
    cout << "     ";
    cout << name;
    };

//Book

Book::Book() : digital_version(0), title(), pages(0), publishingHouse(), cover(HARD) { };

Book::Book(int digital_version, string title, int pages, const PublishingHouse& publishingHouse, enum Cover cover) :
        digital_version(digital_version), title(title), pages(pages), publishingHouse(publishingHouse), cover(cover) { };

Book::Book(const Book &temp) : digital_version(temp.digital_version), title(temp.title), pages(temp.pages),
                               publishingHouse(temp.publishingHouse), cover(temp.cover) { };

Book::~Book() { };

int Book::get_digital_version() const{
    return this->digital_version;
}

string Book::get_title() const{ return this->title; };

int Book::get_pages() const{ return this->pages; };

PublishingHouse Book::get_publishingHouse() const{ return this->publishingHouse; };

Cover Book::get_cover() const{ return cover; };

void Book::set_digital_version(const bool Digital_version) { this->digital_version = Digital_version; };

void Book::set_title(const string Title) { this->title = Title; };

void Book::set_pages(const int Pages) { this->pages = Pages; };

void Book::set_publishingHouse(PublishingHouse *temp_publishingHouse) {
    publishingHouse.setVersion(temp_publishingHouse->getVersion());
    publishingHouse.setName(temp_publishingHouse->getName());
};

void Book::set_cover(const enum Cover Cover) { this->cover = Cover; };

void Book::print1() {
    cout << "     ";
    cout << digital_version;
    cout << "     ";
    cout << title;
    cout << "     ";
    cout << pages;
    cout << "     ";
    publishingHouse.printpb();
    cout << "     ";
    cout << cover << endl;
     }

Book& Book::object_book(string s){
    Book *new_book = new Book;
    string temp = s;
    int pos = 0;

    pos = temp.find(' ');
    string field1 = temp.substr(0, pos);
    int new_field1 = stoi(field1);
    new_book->digital_version = new_field1;
    temp.erase(0, pos+1);

    pos = temp.find(' ');
    string field2 = temp.substr(0, pos);
    new_book->title = field2;
    temp.erase(0, pos+1);

    pos = temp.find(' ');
    string field3 = temp.substr(0, pos);
    int new_field3 = stoi(field3);
    new_book->pages = new_field3;
    temp.erase(0, pos+1);

    pos = temp.find(' ');
    string field4 = temp.substr(0, pos);
    temp.erase(0, pos+1);
    pos = temp.find(' ');
    string field5 = temp.substr(0, pos);
    temp.erase(0, pos+1);
    PublishingHouse *temp_house = new PublishingHouse(field4, field5);
    new_book->publishingHouse = *temp_house;

    pos = temp.find(' ');
    string field6 = temp.substr(0, pos);
    int  new_field6 = stoi(field6);
    if(new_field6 == 0) new_book->cover = HARD;
    if(new_field6 == 1) new_book->cover = SOFT;
    temp.erase(0, pos+1);

    return *new_book;
}

string Book::toString(){
    stringstream result;
    result << get_digital_version() << " " << get_title() << " " << get_pages() << " " << get_cover() << " "
           << get_publishingHouse().getVersion() << " " << get_publishingHouse().getName() << endl;
    return result.str();
}

Book& Book::operator=(Book& book) {
        set_digital_version(book.get_digital_version());
        set_pages(book.get_pages());
        set_title(book.get_title());
        set_cover(book.get_cover());
        PublishingHouse pH(book.get_publishingHouse().getVersion(), book.get_publishingHouse().getName());
        set_publishingHouse(&pH);
    return *this;
}

bool operator==(Book& first, Book& second){
    bool  result = true;
    if (first.get_digital_version() == second.get_digital_version()
        && first.get_title() == second.get_title()
        && first.get_pages() == second.get_pages()
        && first.get_cover() == second.get_cover()
        && first.get_publishingHouse().getVersion() == second.get_publishingHouse().getVersion()
        && first.get_publishingHouse().getName() == second.get_publishingHouse().getName()){
        result &= true;
    }else{
        result &= false;
    }
    return result;
}

bool operator!=(Book& first, Book& second){
    return !(first == second);
}

ostream & operator<<(ostream &out, Book& book){
    out << "     ";
    out << book.get_digital_version();
    out << "     ";
    out << book.get_title();
    out << "     ";
    out << book.get_pages();
    out << "     ";
    out << book.get_publishingHouse().getVersion();
    out << "     ";
    out << book.get_publishingHouse().getName();
    out << "     ";
    out << book.get_cover() << endl;
    return out;
}

istream & operator>>(istream &in, Book& book){
    int dg;
    int pages;
    string name;
    int cover;
    string version;
    string pb_name;

    cout << "Availability of digital version: " << endl;
    in >> dg;
    cout << "Count of pages: " << endl;
    in >> pages;
    cout << "Name of the book: " << endl;
    in >> name;
    cout << "Cover of the book: " << endl;
    in >> cover;
    cout << "Version of the book: " << endl;
    in >> version;
    cout << "Name of the publishing house: " << endl;
    in >> pb_name;

    stringstream buffer;
    buffer << dg << " " << name << " " << pages << " " << cover << " " << pb_name << " " << version;
    regex reg("^[0-1] [A-Z][a-zA-Z]* [0-9]{1,4} [0-1] [A-Z][a-zA-Z]* [A-Za-z][a-zA-Z]*");

    if(regex_match(buffer.str(), reg)){
        book.set_digital_version(dg);
        book.set_title(name);
        book.set_pages(pages);
        if(cover == 0) book.set_cover(HARD);
        else if(cover == 1) book.set_cover(SOFT);
        PublishingHouse pH(version, pb_name);
        book.set_publishingHouse(&pH);
        return in;
        }
    }

//First inheritor
FictionBook::FictionBook(): Book(), direction(REVIVAL), genre(ROMANCE) {}

FictionBook::FictionBook(int digital_version, string title, int pages, const PublishingHouse& publishingHouse, enum Cover cover, Direction direction, Genre genre) :
        Book(digital_version, title, pages, publishingHouse, cover), direction(direction), genre(genre) {}

FictionBook::FictionBook(FictionBook& copy): Book(copy.get_digital_version(), copy.get_title(), copy.get_pages(),
                                                  copy.get_publishingHouse(), copy.get_cover()), direction(copy.get_direction()), genre(copy.get_genre()) {}

FictionBook:: ~FictionBook() {}

Direction FictionBook::get_direction() const { return this->direction; }

Genre FictionBook::get_genre() const { return this->genre; }

void FictionBook::set_direction(const Direction direction) {
    this->direction = direction;
}

void FictionBook::set_genre(const Genre genre) {
    this->genre = genre;
}

void FictionBook::print2() {
    Book::print1();
    cout << "     Direction: ";
    cout << direction;
    cout << "     Genre: ";
    cout << genre << endl;
}

ostream & operator<<(ostream &out ,const FictionBook& book){
    out << "     ";
    out  << book.get_digital_version();
    out << "     ";
    out << book.get_title();
    out << "     ";
    out << book.get_pages();
    out << "     ";
    out << book.get_cover();
    out << "     ";
    out << book.get_publishingHouse().getVersion();
    out << "     ";
    out << book.get_publishingHouse().getName();
    out << "     ";
    out << book.get_direction();
    out << "     ";
    out << book.get_genre();
    return out;
}

bool operator>(const FictionBook& A, const FictionBook& B){
    bool result;
    if (A.get_pages() > B.get_pages() )
        result = true;
    else
        result = false;
    return result;
}

bool operator==(const FictionBook& A, const FictionBook& B){
    bool  result = true;
    if (A.get_digital_version() == B.get_digital_version()
        && A.get_title() == B.get_title()
        && A.get_pages() == B.get_pages()
        && A.get_cover() == B.get_cover()
        && A.get_publishingHouse().getVersion() == B.get_publishingHouse().getVersion()
        && A.get_publishingHouse().getName() == B.get_publishingHouse().getName()
        && A.get_direction() == B.get_direction()
        && A.get_genre() == B.get_genre()){
        result &= true;
    }else{
        result &= false;
    }
    return result;
}

//Second inheritor
ScienceBook::ScienceBook(): Book(), sphere(CHEMISTRY), certified(false) {}

ScienceBook::ScienceBook(int digital_version, string title, int pages, const PublishingHouse& publishingHouse, enum Cover cover, Sphere sphere, bool certified) :
        Book(digital_version, title, pages, publishingHouse, cover), sphere(sphere), certified(certified) {}

ScienceBook::ScienceBook(ScienceBook& copy): Book(copy.get_digital_version(), copy.get_title(), copy.get_pages(),
                                                  copy.get_publishingHouse(), copy.get_cover()), sphere(copy.get_sphere()), certified(copy.get_certified()) {}

ScienceBook:: ~ScienceBook() {}

Sphere ScienceBook::get_sphere() const { return this->sphere; }

bool ScienceBook::get_certified() const { return this->certified; }

void ScienceBook::set_sphere(const Sphere sphere) {
    this->sphere = sphere;
}

void ScienceBook::set_certified(const bool certified) {
    this->certified = certified;
}

void ScienceBook::print3() {
    Book::print1();
    cout << "     Sphere: ";
    cout << sphere;
    cout << "     Certified: ";
    cout << certified << endl;
}

ostream & operator<<(ostream &out ,const ScienceBook& book){
    out << "     ";
    out  << book.get_digital_version();
    out << "     ";
    out << book.get_title();
    out << "     ";
    out << book.get_pages();
    out << "     ";
    out << book.get_cover();
    out << "     ";
    out << book.get_publishingHouse().getVersion();
    out << "     ";
    out << book.get_publishingHouse().getName();
    out << "     ";
    out << book.get_sphere();
    out << "     ";
    out << book.get_certified();
    return out;
}

bool operator>(const ScienceBook& A, const ScienceBook& B){
    bool result = true;
    if (A.get_pages() > B.get_pages() )
        result = true;
    else
        result = false;
    return result;
}

bool operator==(const ScienceBook& A, const ScienceBook& B){
    bool  result = true;
    if (A.get_digital_version() == B.get_digital_version()
        && A.get_title() == B.get_title()
        && A.get_pages() == B.get_pages()
        && A.get_cover() == B.get_cover()
        && A.get_publishingHouse().getVersion() == B.get_publishingHouse().getVersion()
        && A.get_publishingHouse().getName() == B.get_publishingHouse().getName()
        && A.get_sphere() == B.get_sphere()
        && A.get_certified() == B.get_certified()){
        result &= true;
    }else{
        result &= false;
    }
    return result;
}


