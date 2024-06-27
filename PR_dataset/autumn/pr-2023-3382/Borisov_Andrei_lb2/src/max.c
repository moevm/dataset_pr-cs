int max(int massive[], int len){
    int max = massive[0];
    int index = 0;
    for(int i = 0; i < len; i++)
    {
        if(massive[i] > max) {
            max = massive[i];
            index = i;
        }
    }
    return(index);
}