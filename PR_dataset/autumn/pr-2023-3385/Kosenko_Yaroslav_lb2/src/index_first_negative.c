int index_first_negative(int arr[], int n){
    for (int i = 0; i < n; i++){
        if (arr[i] < 0) return i;
    }
}

