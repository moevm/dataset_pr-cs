int input (int numbers[]){
    int i = 0, flag = 1, size = 0;

    while(flag){
        scanf("%d", &numbers[i]);
        i++;
        size++;

        if (getchar()=='\n'){
            flag = 0;
        }
    }

    return size;
}
