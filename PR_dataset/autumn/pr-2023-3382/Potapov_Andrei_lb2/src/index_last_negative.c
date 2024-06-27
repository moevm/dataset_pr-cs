int index_last_negative(int arr[], int l){
	int i;
	for(i=l;i>=0;i--){
		if(arr[i]<0){
			return i;
			break;
		}	
	}	
}
