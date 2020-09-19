#define INT_MAX 65535

// binary search
int binary_search(int* sorted_nums,const int length, const int target) {
	// assume small to big sorted
	int p = 0;
	int q = length;
	int m = 0;

	while (p<q) {
		if (*(sorted_nums + p) == target) {
			return p;
		}
		if (*(sorted_nums + q) == target) {
			return q;
		}

		m = (p + q) / 2;
		if (*(sorted_nums + m) > target) {
			q = m;
		}
		else {
			p = m;
		}
	}
}

// insert sort
int* insert_sort_s2b(int* nums, int length) {
	//在原数组上排序
	int j = 0;
	int key = 0;
	int i = 0;
	for (j = 1;j < length;j++) {
		key = nums[j];
		i = j - 1;
		while (i>-1 && nums[i]>key) {
			nums[i + 1] = nums[i];
			i--;
		}
		nums[i + 1] = key;
	}
	return nums;
}

int* insert_sort_b2s(int* nums, int length) {
	//在原数组上排序
	int j = 0;
	int key = 0;
	int i = 0;
	for (j = 1;j < length;j++) {
		key = nums[j];
		i = j - 1;
		while (i > -1 && nums[i] < key) {
			nums[i + 1] = nums[i];
			i--;
		}
		nums[i + 1] = key;
	}
	return nums;
}

// merge sort
void merge(int* nums, int p, int q, int r) {
	int n1 = (q - p + 1) + 1;//加上哨兵位
	int n2 = (r - q ) + 1;
	int* L = (int*)malloc(sizeof(int) * (n1));
	memset(L,0, sizeof(int) * (n1 ));
	int* R = (int*)malloc(sizeof(int) * (n2));
	memset(R, 0, sizeof(int) * (n2 ));
	int i = 0;
	while (i < n1-1) {
		*(L + i) = *(nums + p+i);
		i++;
	}
	int j = 0;
	while (j < n2-1) {
		*(R + j) = *(nums + q+1+j);
		j++;
	}
	L[n1-1] = INT_MAX;
	R[n2-1] = INT_MAX;
	i = 0;
	j = 0;
	int k = p;
	for (k = p;k < r+1;k++) {
		if (L[i] < R[j]) {
			*(nums + k) = L[i];
			i++;
		}
		else {
			*(nums + k) = R[j];
			j++;
		}
	}
}

void merge_sort(int* nums, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(nums, p, q);
		merge_sort(nums, q + 1, r);
		merge(nums, p,q,r);
	}
}

// count invers pairs count
int count_sub(int* nums, int p, int q, int r, int* count) {
	int n1 = (q - p + 1) + 1;//加上哨兵位
	int n2 = (r - q) + 1;
	int* L = (int*)malloc(sizeof(int) * (n1));
	memset(L, 0, sizeof(int) * (n1));
	int* R = (int*)malloc(sizeof(int) * (n2));
	memset(R, 0, sizeof(int) * (n2));
	int i = 0;
	while (i < n1 - 1) {
		*(L + i) = *(nums + p + i);
		i++;
	}
	int j = 0;
	while (j < n2 - 1) {
		*(R + j) = *(nums + q + 1 + j);
		j++;
	}
	// count invers pairs O(n)
	i = 0;
	j = 0;
	while (i < n1-1) {
		(*count) += j;
		while (j < n2-1) {
			if (L[i] > R[j]) {
				(*count)++;
				j++;
			}
			else {
				break;
			}
		}
		i++;
	}

	// merge sub O(n)
	L[n1-1] = INT_MAX;
	R[n2-1] = INT_MAX;
	i = 0;
	j = 0;
	int k = p;
	for (k = p;k < r + 1;k++) {
		if (L[i] < R[j]) {
			*(nums + k) = L[i];
			i++;
		}
		else {
			*(nums + k) = R[j];
			j++;
		}
	}
}

void divide_conquer(int* nums, int p, int r, int* count) {
	if (p < r) {
		int q = (p + r) / 2;
		divide_conquer(nums, p, q, count);
		divide_conquer(nums, q + 1, r, count);
		count_sub(nums, p, q, r, count);
	}
}

int inverse_pair_totalcount(int* nums, int len) {
	int* count = (int*)malloc(sizeof(int));
	memset(count, 0, sizeof(int));
	// if you don't want to sort the original array
	//int* nums_temp = (int*)malloc(sizeof(int)*(len));
	//memset(nums_temp, nums, sizeof(int) * (len));

	divide_conquer(nums, 0, len-1, count);
	int count_temp = (*count);
	free(count);
	return count_temp;
}







