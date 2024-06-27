int index_first_negative(int array[], int len){
    int count=0;
    for (int i = 0; i < len; i++)
    {
        if (array[i]<0){
            return count;
        }
        count++;
    }
}
