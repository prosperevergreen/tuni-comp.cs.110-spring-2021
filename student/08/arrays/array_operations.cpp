#include "array_operations.hh"

int greatest_v1(int* itemptr, int size)
{
    int temp_grt = *itemptr;

    for (int i = 0; i < size; i++) {
        if (*(itemptr + i) > temp_grt)
            temp_grt = *(itemptr + i);
    }

    return temp_grt;
}

int greatest_v2(int* itemptr, int* endptr)
{
    return greatest_v1(itemptr, (endptr - itemptr));
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    int size = endptr - itemptr;
    for (int i = 0; i <= size; i++) {
        *(targetptr + i) = *(itemptr + i);
    }
}

void reverse(int* leftptr, int* rightptr)
{
    int* fist_elem_ptr = leftptr;
    int* last_elem_ptr = rightptr - 1;
    int size = 1 + (last_elem_ptr - fist_elem_ptr);

    for (int i = 0; i <= size / 2; i++) {
        int temp = *(fist_elem_ptr + i);
        *(fist_elem_ptr + i) = *(last_elem_ptr - i);
        *(last_elem_ptr - i) = temp;
    }
}
