#define N 100

int max(int arr[N]){
    int ma=0;
    for (int i=0;i<N;i++){
        if (arr[i]>ma){
            ma = arr[i];
        }
    }
    return ma;
}
