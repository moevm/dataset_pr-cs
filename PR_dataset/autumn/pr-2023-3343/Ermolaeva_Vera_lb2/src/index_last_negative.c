int index_last_negative (int arr[], int size) {
    for (int i = size-1; i > -1; i--) {
        if (arr[i] < 0)
            return i;
    }
}