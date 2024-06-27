int max(int arr[], int size) {
    int max_value = arr[0];
    int i = 1;
    
    while (i < size) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
        i++;
    }
    
    return max_value;
}