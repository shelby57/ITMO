#ifndef LAB3_FLOAT_H
#define LAB3_FLOAT_H
#include <istream>
struct Float
{
    int x;
    bool operator<(const Float &p) const { return this->x < p.x; }
    bool operator>(const Float &p) const { return this->x > p.x; }
};

std::istream &operator>>(std::istream &fin, Float &p)
{
    fin >> p.x;
    return fin;
}

std::ostream &operator<<(std::ostream &fout, const Float &p)
{
    fout << p.x;
    return fout;
}

#endif
