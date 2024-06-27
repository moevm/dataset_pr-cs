int min(int massive[], int len){
    int min = massive[0];
    int index = 0;
    for(int i = 0; i < len; i++)
    {
        if(massive[i] < min) {
            min = massive[i];
            index = i;
        }
    }
    return(index);
}