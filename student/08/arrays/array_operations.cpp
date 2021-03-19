#include "array_operations.hh"

int greatest_v1(int* itemptr, int size)
{
    int* temp_grt = itemptr;

    for (int i = 0; i < size; i++) {
        if (*(itemptr + i) > *temp_grt)
            temp_grt = itemptr;
    }

    return *temp_grt;
}

int greatest_v2(int* itemptr, int* endptr)
{
    return greatest_v1(itemptr, (endptr - itemptr));
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    for (int i = 0; (itemptr + i) <= endptr; i++) {
        *(targetptr + i) = *(itemptr + i);
    }
}

void reverse(int* leftptr, int* rightptr)
{
    int arr_length = rightptr - leftptr;

    for (int i = 0; i <= arr_length / 2; i++) {
        int temp = *(leftptr + i);
        *(leftptr + i) = *(rightptr - i);
        *(rightptr - i) = temp;
    }
}
