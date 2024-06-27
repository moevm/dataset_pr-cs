int index_first_negative(int arr[], int l){
	int i;
	for(i=0; i<l;i++){
		if(arr[i]<0){
			return i;
			break;	
		}	
	}	
}
