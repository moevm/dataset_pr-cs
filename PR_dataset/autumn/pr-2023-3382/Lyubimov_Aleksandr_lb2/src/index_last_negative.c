int index_last_negative(int * array, int len_array) {
    int i;
    for (i = len_array - 1; i > 0; i --) {
        if (array[i] < 0){
            return i;
        }
    }
}
