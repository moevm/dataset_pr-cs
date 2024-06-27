int abs_max(int q[], int len_q) {
	int q_max = 0, max_i, i = 0;
    for(i; i < len_q;i++){
        if (abs(q[i]) > q_max){
                q_max = abs(q[i]);
                max_i = i;
        }
    }
	return max_i;
}
