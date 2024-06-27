int index_last_negative(int arr[],int len){
    int count=len-1;
    for (int i = count; i >-1; i--)
    {
        if (arr[i]<0)
        {
            return count;
        }
        count--;

    }

}    
