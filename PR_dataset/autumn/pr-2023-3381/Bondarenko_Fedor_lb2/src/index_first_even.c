int index_first_even (int array []) {
    int i;
    for (i = 0; i < 100; i++) {
        if (abs(array[i]) % 2 == 0) {
                return i;
                break;
        }
    }
}
