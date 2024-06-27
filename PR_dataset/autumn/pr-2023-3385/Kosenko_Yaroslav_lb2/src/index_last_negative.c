int index_last_negative(int arr[], int n){
    for (int i = n-1; i >= 0; i--){
        if (arr[i] < 0) return i;
    }
}

