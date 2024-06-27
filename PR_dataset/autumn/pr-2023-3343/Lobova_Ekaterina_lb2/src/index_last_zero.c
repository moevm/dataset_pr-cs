int index_last_zero(int a[], int n){
    for (int i=n-1;i>=0;i--){
        if (a[i]==0){
            return i;
        }
    }
}
