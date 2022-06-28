#ifndef LAB3_PHONEBOOK_H
#define LAB3_PHONEBOOK_H
#include <istream>
#include <ostream>
#include <string>

bool is_digit(char &x)
{
    return x >= '0' && x <= '9';
}

bool is_number_int(const std::string &s)
{
    for (char i : s)
    {
        if (!is_digit(i))
        {
            return false;
        }
    }
    return true;
}
struct phonebook
{
    std::size_t phone_number;
    std::string surname;
    std::string name;
    std::string patronymic;

    bool operator>(const phonebook &x) const
    {
        if (this->surname != x.surname)
        {
            return this->surname > x.surname;
        }
        if (this->name != x.name)
        {
            return this->name > x.name;
        }
        if (this->patronymic != x.patronymic)
        {
            return this->patronymic > x.patronymic;
        }
        return this->phone_number > x.phone_number;
    }

    bool operator<(const phonebook &x) const
    {
        if (this->surname != x.surname)
        {
            return this->surname < x.surname;
        }
        if (this->name != x.name)
        {
            return this->name < x.name;
        }
        if (this->patronymic != x.patronymic)
        {
            return this->patronymic < x.patronymic;
        }
        return this->phone_number < x.phone_number;
    }
};

std::istream &operator>>(std::istream &fin, phonebook &p)
{
    std::string phone;
    fin >> p.surname >> p.name >> p.patronymic >> phone;
    if (is_number_int(phone))
    {
        p.phone_number = std::stoull(phone);
    }
    return fin;
}

std::ostream &operator<<(std::ostream &fout, const phonebook &p)
{
    return fout << p.surname << " " << p.name << " " << p.patronymic << " " << p.phone_number;
}

#endif
