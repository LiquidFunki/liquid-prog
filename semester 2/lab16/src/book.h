#ifndef LAB9_BOOK_H
#define LAB9_BOOK_H

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::istream;
using std::regex_match;
using std::regex;
using std::stoi;
using std::vector;
using std::map;
using std::set;
using std::find_if;
using std::copy;
using std::sort;
using std::back_inserter;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

enum Cover { HARD, SOFT };

class PublishingHouse{
    string version;
    string name;
public:
    PublishingHouse();
    PublishingHouse(string version, string name);
    PublishingHouse(const PublishingHouse &temp);
    virtual ~PublishingHouse();
    string getVersion();
    string getName();
    void setVersion( const string Version);
    void setName( const string Name);
    void printpb();
};

class Book {
public:
    virtual void print() = 0;

    virtual Book *clone() = 0;

    virtual ~Book() {};

    virtual char GetType() = 0;
};

//First inheritor
enum Direction{ REVIVAL, MODERN, POSTMODERN };

enum Genre{ ROMANCE, DETECTIVE, NOVEL, STORY };

class FictionBook : public Book {
    int digital_version;
    string title;
    int pages;
    PublishingHouse publishingHouse;
    Cover cover;
    Direction direction;
    Genre genre;
public:
    FictionBook();
    FictionBook(int digital_version, string title, int pages, const PublishingHouse& publishingHouse, enum Cover cover, Direction direction, Genre genre);

    int get_digital_version() const;
    string get_title() const;
    int get_pages() const;
    PublishingHouse get_pH() const;
    Cover get_cover() const;
    void set_digital_version(const int digital_version);
    void set_title(const string title);
    void set_pages(const int pages);
    void set_pH(PublishingHouse *ph);
    void set_cover(const Cover cover);
    virtual ~FictionBook();
    Direction get_direction() const;
    Genre get_genre() const;
    void set_direction(const Direction direction);
    void set_genre(const Genre genre);
    void print() override;
    Book *clone() override;
    char GetType() override;
};

bool operator==(const FictionBook& A, const FictionBook&  B);


//Second inheritor
enum Sphere{ CHEMISTRY, BIOLOGY, PHYSICS, IT };

class ScienceBook : public Book {
    int digital_version;
    string title;
    int pages;
    PublishingHouse publishingHouse;
    Cover cover;
    Sphere sphere;
    bool certified;
public:
    ScienceBook();
    ScienceBook(int digital_version, string title, int pages, const PublishingHouse& publishingHouse, enum Cover cover, Sphere sphere, bool certified);

    virtual  ~ScienceBook();

    int get_digital_version() const;
    string get_title() const;
    int get_pages() const;
    PublishingHouse get_pH() const;
    Cover get_cover() const;
    void set_digital_version(const int digital_version);
    void set_title(const string title);
    void set_pages(const int pages);
    void set_pH(PublishingHouse *ph);
    void set_cover(const Cover cover);
    Sphere get_sphere() const;
    bool get_certified() const;
    void set_sphere(const Sphere sphere);
    void set_certified(const bool certified);
    void print() override;
    Book *clone() override;
    char GetType() override;
};

bool operator==(const ScienceBook& A, const ScienceBook&  B);

#endif

