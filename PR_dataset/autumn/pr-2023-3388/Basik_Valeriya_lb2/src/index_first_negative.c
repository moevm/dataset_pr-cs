int index_first_negative(int* array, int number_of_elements)
{
    for (int i = 0; i < number_of_elements; i++) {
        if (array[i] < 0)
            return i;
    }
    return -1;
}