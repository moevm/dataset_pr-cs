int index_first_negative(int arr[], int sizeOfArr){
    int index_first;
    int i = 0;
    while (i < sizeOfArr){
        if (arr[i] < 0){
            index_first = i;
            break;
        }
        i++;
    }
    return index_first;
}
