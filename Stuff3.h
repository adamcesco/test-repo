#ifndef STUFF3_H
#define STUFF3_H

#include <bits/stdc++.h>

using namespace std;

class Stuff3 {
    friend ostream& operator<<(ostream& os, const Stuff3& s);
    friend istream& operator>>(istream& os, Stuff3& s);

   public:
    Stuff3(bool = true, int = 0, int = 0, int = 0);
    Stuff3(const Stuff3&);

    bool operator==(const Stuff3& s) const;
    Stuff3& operator=(const Stuff3& s);

    static int compareCount;

   private:
    int a, b, c;
};


int Stuff3::compareCount = 0;

Stuff3::Stuff3(bool israndom, int x, int y, int z) {
    if (israndom) {
        a = rand() % 1000;
        b = rand() % 1000;
        c = rand() % 1000;
    } else {
        a = x;
        b = y;
        c = z;
    }
}

Stuff3::Stuff3(const Stuff3& s) {
    a = s.a;
    b = s.b;
    c = s.c;
}

bool Stuff3::operator==(const Stuff3& s) const {
    Stuff3::compareCount++;
    return (a == s.a) && (b == s.b) && (c == s.c);
}

Stuff3& Stuff3::operator=(const Stuff3& s) {
    a = s.a;
    b = s.b;
    c = s.c;
    return *this;
}

ostream& operator<<(ostream& os, const Stuff3& s) {
    os << "(" << s.a << " " << s.b << " " << s.c << ")";
    return os;
}

istream& operator>>(istream& is, Stuff3& s) {
    is >> s.a >> s.b >> s.c;
    return is;
}

#endif // STUFF3_H