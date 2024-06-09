#include <string.h>
#include <iostream>
#include <vector>

using namespace std;


class String
{
public:
    String()
    {
        cout << "String()" << endl;
        _s = new char[1];
        *_s = 0;
    }
    String(const char* s)
    {
        cout << "String(const char* s) (s=" << s << ')' << endl;
        _s = new char[strlen(s) + 1];
        strcpy(_s, s);
    }

    String(const String& s)
    {
        cout << "String(const String& s)" << endl;
        _s = new char[strlen(s._s) + 1];
        strcpy(_s, s._s);
    }

    String(String&& s)
    {
        cout << "String(String&& s)" << endl;
        _s = s._s;
        s._s = (char*)666;
    }

    String& operator=(const String& s)
    {
        cout << "String& operator=(const String& s)" << endl;
        if (this != &s) {   // self assignment check #$^%$#@$%^
            delete[] _s;

            _s = new char[strlen(s._s) + 1];
            strcpy(_s, s._s);
        }
        return *this;
    }

    String& operator=(String&& s)
    {
        cout << "String& operator=(String&& s)" << endl;
        delete[] _s;
        _s = s._s;
        s._s = (char*)666;
        return *this;
    }

    ~String()
    {
        if (_s == (char*)666)
            cout << "~String(): zerfetzt" << endl;
        else
            delete[] _s;
    }

    const char* c_str() const { return _s; }
    size_t size() const { return strlen(_s); }

private:
    char* _s;
};



String concatenate(const char* s1, const char* s2)
{
    size_t len = strlen(s1) + strlen(s2) + 1;
    char* tmp = new char[len];
    strcpy(tmp, s1);
    strcpy(tmp+strlen(s1), s2);

    String retstr(tmp);
    delete[] tmp;

    cout << "drin: " << (void*)retstr.c_str() << endl;

    return retstr;
}

class Person
{
public:
    Person(String&& firstname, String&& lastname)
    : firstname(std::move(firstname)),   // <--- !
      lastname(std::move(lastname))      // <--- !
    {}
private:
    String firstname;
    String lastname;
};


int main()
{
    Person p("Joerg", "Faschingbauer");

    (void)p;

    // {
    //     String s;
    //     s = concatenate("aaa", "bbb"); // move assignment, if
    //                                    // implemented by String
    //     cout << "heraussen: " << (void*)s.c_str() << endl;
    // }

    // {
    //     String s;
    //     s = "abc";
    // }

    // // std::move
    // {
    //     String source("source");
    //     String dest;
    //     dest = std::move(source);

    //     //cout << source.c_str() << endl;
    //     cout << dest.c_str() << endl;
    // }

    // {
    //     std::vector<String> strings;
    //     strings.push_back("blah");
    // }

    // {
    //     std::vector<String> strings;
    //     strings.emplace_back("blah");
    // }
    


    return 0;
}
