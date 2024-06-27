int index_last_odd (int array []) {
    int i;
    for (i = 99; i >= 0; i--) {
        if (abs(array[i]) % 2 == 1) {
                return i;
                break;
        }
    }
}
