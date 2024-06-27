int min(int arr[], int size) {
    int minimum = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
}