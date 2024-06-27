int index_first_zero(int a[], int n){
    for (int i=0;i<n;i++){
        if (a[i]==0){
            return i;
        }
    }
}
