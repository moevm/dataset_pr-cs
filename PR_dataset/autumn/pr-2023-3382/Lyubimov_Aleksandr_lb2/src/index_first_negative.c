int index_first_negative(int * array, int len_array) {
    int i;
    for (i = 0; i < len_array; i ++) {
        if (array[i] < 0) {
            return i;
        }
    }
}
