#ifndef LAB3_INT_H
#define LAB3_INT_H
#include <istream>
struct Int
{
    int x;
    bool operator<(const Int &p) const { return this->x < p.x; }
    bool operator>(const Int &p) const { return this->x > p.x; }
};

std::istream &operator>>(std::istream &fin, Int &p)
{
    fin >> p.x;
    return fin;
}

std::ostream &operator<<(std::ostream &fout, const Int &p)
{
    fout << p.x;
    return fout;
}

#endif
