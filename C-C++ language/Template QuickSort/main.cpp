#include "return_codes.h"

#include "Float.h"
#include "Int.h"
#include "phonebook.h"
#include "quicksort.h"
#include <fstream>
#include <iostream>
#include <vector>

void processing_error(int code)
{
    if (code == 1)
        std::cerr << "Incorrect count of program arguments";
    if (code == 2)
        std::cerr << "The input file could not be opened for reading";
    if (code == 3)
        std::cerr << "failed to allocate memory";
    if (code == 4)
        std::cerr << "Could not open the output file for writing";
    if (code == 5)
        std::cerr << "Incorrect first argument";
    if (code == 6)
        std::cerr << "Incorrect data in input file";
}

template< typename T >
void go(std::vector< T > &a, std::ostream &fout, bool type)
{
    if (type)
        quicksort< T, true >(a, 0, a.size() - 1);
    else
        quicksort< T, false >(a, 0, a.size() - 1);
    for (auto &x : a)
        fout << x << '\n';
}

template< typename T >
void read(std::vector< T > &a, std::istream &fin, std::string &count_line)
{
    T s;
    std::size_t cnt = std::stoi(count_line);
    for (int i = 0; i < cnt; ++i)
    {
        fin >> s;
        a.emplace_back(s);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        processing_error(1);
        return ERROR_INVALID_DATA;
    }

    std::ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open())
    {
        processing_error(2);
        return ERROR_FILE_NOT_FOUND;
    }

    std::string type_sort, type_data, count_line;
    std::getline(fin, type_data);
    if ((type_data != "int" && type_data != "float" && type_data != "phonebook"))
    {
        processing_error(6);
        fin.close();
        return ERROR_NOT_IMPLEMENTED;
    }

    std::getline(fin, type_sort);
    if (type_sort != "ascending" && type_sort != "descending")
    {
        processing_error(6);
        fin.close();
        return ERROR_INVALID_DATA;
    }

    std::getline(fin, count_line);
    if (!is_number_int(count_line))
    {
        processing_error(6);
        fin.close();
        return ERROR_INVALID_DATA;
    }

    std::ofstream fout;
    fout.open(argv[2]);
    if (!fout.is_open())
    {
        fin.close();
        processing_error(2);
        return ERROR_FILE_NOT_FOUND;
    }
    bool type = true;
    if (type_sort == "descending")
        type = false;
    if (type_data == "int")
    {
        std::vector< int > a;
        read< int >(a, fin, count_line);
        fin.close();
        go< int >(a, fout, type);
    }
    else if (type_data == "float")
    {
        std::vector< float > a;
        read< float >(a, fin, count_line);
        fin.close();
        go< float >(a, fout, type);
    }
    else
    {
        std::vector< phonebook > a;
        read< phonebook >(a, fin, count_line);
        fin.close();
        go< phonebook >(a, fout, type);
    }
    return ERROR_SUCCESS;
}