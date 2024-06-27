#define N 100

int min(int arr[N], int chm){
    int m=999;
    for (int i=0;i<chm;i++){
        if (arr[i]<m){
            m=arr[i];
        }
    }
    return m;
}
