int index_last_negative(int* array, int number_of_elements)
{
    for (int i = number_of_elements - 1; i >= 0; i--) {
        if (array[i] < 0)
            return i;
    }
    return -1;
}