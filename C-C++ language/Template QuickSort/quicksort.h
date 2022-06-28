#include "Float.h"
#include "Int.h"
#include "phonebook.h"

#include <vector>
#ifndef LAB3_QUICKSORT_H
#	define LAB3_QUICKSORT_H
#endif

template< typename T >
int comp(T &x, T &y, bool descending)
{
    if (x < y)
    {
        if (descending)
            return 1;
        else
            return -1;
    }
    if (x > y)
    {
        if (descending)
            return -1;
        else
            return 1;
    }
    return 0;
}

template< typename T, bool descending >
void quicksort(std::vector< T > &a, int x, int y)
{
flag:
    if (x < y)
    {
        int l = x;
        int r = y;
        T c = a[(l + r) / 2];
        do
        {
            while (comp(a[l], c, descending) == 1)
                ++l;
            while (comp(a[r], c, descending) == -1)
                --r;
            if (l <= r)
            {
                T t = a[l];
                a[l++] = a[r];
                a[r--] = t;
            }
        } while (l <= r);
        quicksort< T, descending >(a, x, r);
        x = l;
        goto flag;
    }
}
