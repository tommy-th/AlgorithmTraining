void quicksort(int* a, int low, int high){

	int i = low, j = high, h;
	int x = a[(low + high) / 2];

	do{
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j){
			h = a[i]; a[i] = a[j]; a[j] = h;
			i++; j--;
		}
	} while (i <= j);

	if (low < j) quicksort(a, low, j);
	if (i < high) quicksort(a, i, high);
}