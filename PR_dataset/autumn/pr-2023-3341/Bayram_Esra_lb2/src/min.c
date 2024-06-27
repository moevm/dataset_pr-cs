int min(int arr[], int size) {
    int min_value = arr[0];
    int i = 1;
    
    while (i < size) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
        i++;
    }
    
    return min_value;
}