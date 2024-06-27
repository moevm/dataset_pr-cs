int index_first_negative(int arr[],int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            res = i;
            break;
        }
    }
    return res;
}
