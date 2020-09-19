#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include"my_utils.h"
#include"my_string.h"
#include"my_math.h"
#include"my_sort.h"

#define INFINITE 65535

#pragma region sort by category

// ��ͨ���: ����֮��
// ��̬�滮: 202(python)��
//   ���η�: 50��53
//     ����: 2��206
#pragma endregion

#pragma region ͨ�����ݽṹ
 // Definition for singly-linked list.
struct ListNode {
	int val;
	struct ListNode* next;
};

struct HeapArray {
	int len;
	int* array;
};
#pragma endregion

#pragma region 2 �������
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* p = l1;
	int i = 0;
	int flowed = 0;
	int temp1;
	int temp2;
	while (l1->next != NULL || l2->next != NULL) {
		if (l1->next == NULL) {
			l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			l1->next->val = 0;
			l1->next->next = NULL;
		}
		if (l2->next == NULL) {
			l2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			l2->next->val = 0;
			l2->next->next = NULL;
		}
		temp1 = l1->val;
		temp2 = l2->val;
		l1->val = temp1 + temp2 + flowed;
		if (l1->val>9) {
			flowed = 1;
			l1->val = l1->val - 10;
		}
		else{
			flowed = 0;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	temp1 = l1->val;
	temp2 = l2->val;
	l1->val = temp1 + temp2 + flowed;
	if (l1->val > 9) {
		l1->val = l1->val - 10;
		l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		l1->next->val = 1;
		l1->next->next = NULL;
	}
	return p;
}

void test2() {
	printf("\n\n###############  ��ʼ���� 2 �������  #############\n");
	int nums1[] = {5,6,7};
	int nums2[] = {2,4,3};
	int len1 = sizeof(nums1) / sizeof(nums1[0]);
	int len2 = sizeof(nums2) / sizeof(nums2[0]);
	struct ListNode* l1 = create_ListNode_from_array(nums1, len1);
	struct ListNode* l2 = create_ListNode_from_array(nums2, len2);
	l1 = addTwoNumbers(l1,l2);
}
#pragma endregion

#pragma region 7 ������ת
void test7() {
	printf("\n\n###############  ��ʼ���� 7 ������ת  #############\n");
	long long int a = 1534236469;
	long long int b = integer_inverse(a);
	printf("%d\n", b);
}
#pragma endregion

#pragma region 9 ������
int is_palindrome(long long int x) {
	long long int b = integer_inverse(x);
	if (b == x) {
		return 1;
	}
	else {
		return 0;
	}
}

void test9() {
	printf("\n\n###############  ��ʼ���� 9 ������  #############\n");
	long long int a = 1534236469;
	int b = is_palindrome(a);
	
	printf("%d\n", b);
}


#pragma endregion

#pragma region 13 ��������ת����
int romanToInt(char* s) {
	//ע���˷����Ǹ���leetcode�ġ�
	//���⣺�����������������ģ��������"IXCM"��Ӧ�ÿ���"IX"��"CM"����"I"��"XC","M"������"IX"��"XC"��"CM"��"M"��
	//�𣺸���leetcode�����Ľ��������"IXCM"�Ļ��������889��
	//	Ҳ��˵������������Ҫһ��һ�������ģ���Ӧ�ÿ���IX��-1��,XC��-10��,CM��-100��,M��1000����
	//  ע���Ⲣ�����������һ�������
	//  ���ԣ����ʲô�������ֲ��������Ĺؼ�

	int count = 0;
	while (*s) {
		if (*s == 'V')         count += 5;
		else if (*s == 'L')    count += 50;
		else if (*s == 'D')    count += 500;
		else if (*s == 'M')    count += 1000;
		else if (*s == 'I')
			count = (*(s + 1) == 'V' || *(s + 1) == 'X') ? count - 1 : count + 1;
		else if (*s == 'X')
			count = (*(s + 1) == 'L' || *(s + 1) == 'C') ? count - 10 : count + 10;
		else// �� *s='C'
			count = (*(s + 1) == 'D' || *(s + 1) == 'M') ? count - 100 : count + 100;
		s++;
	}
	return count;
}

void test13() {
	printf("\n\n###############  ��ʼ���� 13 ��������ת����  #############\n");
	long long int a = 1534236469;
	long long int b = integer_inverse(a);
	printf("%d\n", b);
}
#pragma endregion

#pragma region 20 ��Ч������

void test20() {
	printf("\n\n###############  ��ʼ���� 20 ��Ч������  #############\n");
	long long int a = "{[]}";
	long long int b = integer_inverse(a);
	printf("%d\n", b);
}
#pragma endregion

#pragma region 50 pow(x,n)
void test50(){
	printf("\n\n###############  ��ʼ���� 50 pow(x,n)  #############\n");
	double x = 2;
	int n = -2;
	x = myPow(x,n);
	printf("%f\n", x);
}
#pragma endregion

#pragma region 53 ��������к�
int find_max_cross(int* nums, int low, int mid, int high) {
	int leftmax = -2147483647; // -inf 0x8000 0000
	int sum = 0;
	int i = mid;
	while (i >= low) {
		sum += nums[i];
		if (sum > leftmax) {
			leftmax = sum;
		}
		i--;
	}
	sum = 0;
	i = mid + 1;
	int righmax = -2147483647;
	while (i <= high) {
		sum += nums[i];
		if (sum > righmax) {
			righmax = sum;
		}
		i++;
	}
	return  leftmax + righmax;
}

int maxSubArray(int* nums, int low,int high) {
	//����������leetcode�����Ǹ�����������ͬ�����ϻ�������������±꣬����python������ʵ�֣���c�Ļ���Ҫ����һ�����ݽṹ����΢�鷳
	// O(nlogn)
	if (low == high) {
		return nums[low];
	}
	else {
		int mid = (low + high) / 2;
		int leftmax = maxSubArray(nums, low, mid);
		int righmax = maxSubArray(nums, mid+1, high);
		int crosmax = find_max_cross(nums, low,mid,high);
		if (leftmax>=righmax && leftmax>=crosmax) {
			return leftmax;
		}
		else if(righmax>=leftmax && righmax>=crosmax) {
			return righmax;
		}
		else {
			return crosmax;
		}
	}
}

int find_left_max(int* nums, int high) {
	int leftmax = -2147483647; // -inf 0x8000 0000
	int sum = 0;
	int i = high;
	while (i >= 0) {
		sum += nums[i];
		if (sum > leftmax) {
			leftmax = sum;
		}
		i--;
	}
	return  leftmax;
}

int maxSubArray2(int* nums, int high) {
	// O(n) dynamic programming Ҳ�� ϰ��4-1.5
	if (0 == high) {
		return nums[0];
	}
	int max = max(maxSubArray2(nums, high-1),find_left_max(nums, high));
	return max;
}

void test53() {
	printf("\n\n###############  ��ʼ���� 53 ��������к�  #############\n");
	
	int a[] = { -2,1,-3,4,-1,2,1,-5,4 };
	int len = sizeof(a) / sizeof(a[0]);
	int b = maxSubArray2(a,len-1);
	//printf("%f\n", );
}
#pragma endregion

#pragma region 67 ����֮��

char* myaddBinary(char* a, char* b) {

	//	char s1[100] = "1110110101";
	//	char* s2 = "1110111011";λ��̫�󣬻������,���ֻ����9λ��
	char* s = "0";
	if (*a == '0' && *b == '0')
		return s;
	long long int x1 = dec2bin(bin2dec(str2bint(a)) + bin2dec(str2bint(b)));
	s = int2str(x1);
	return s;
}

char* addBinary(char* a, char* b) {
	char* p1 = a;
	char* p2 = b;
	str_inverse(a);
	str_inverse(b);
	char* s = (char*)malloc(100); //��Ҫ������ԭλ���ϲ���1.�鷳;2.���ܴ����Ժ�δ֪�Ĵ���
	memset(s, '\0', 100);
	char* p3 = s;

	int i = 0;
	int flowed = 0;
	int temp1;
	int temp2;
	while (*a != '\0' || *b != '\0') {
		if (*a == '\0') {
			temp1 = 0;
		}
		else {
			temp1 = *a - '0';
			a++;
		}
		if (*b == '\0') {
			temp2 = 0;
		}
		else {
			temp2 = *b - '0';
			b++;
		}

		*s = '0' + temp1 + temp2 + flowed;
		if (*s > '1') {
			flowed = 1;
			*s = *s - 2;
		}
		else {
			flowed = 0;
		}
		s++;
	}
	if (flowed == 1) {
		*s = '1';
	}
	str_inverse(p1);
	str_inverse(p2);
	str_inverse(p3);
	return p3;
}

void test67()
{
	printf("\n\n###############  ��ʼ���� 67 ����֮��  #############\n");
	char s1[] = "11";
	char s2[] = "1";
	char* s = addBinary(s1, s2);
	printf("%s\n", s);
}
#pragma endregion

#pragma region 202 ������С��������
int sum_array(int* nums, int numsSize) {
	int i = numsSize;
	int sum = 0;
	for (i;i > -1;i--) {
		sum = sum + nums[i];
	}
	return sum;
}
int minSubArrayLen(int s, int* nums, int numsSize) {
	int sum = sum_array(nums, numsSize);
	if (sum > s) {
		return numsSize;
	}
	else{
		int* nums_left = nums;
	}
}

void test202()
{
	printf("\n\n###############  ��ʼ���� 202 ������С��������  #############\n");
	int s = 7;
	int nums[100] = {2,3,1,2,4,3};
	int len = sizeof(nums)/sizeof(nums[0]);
	int result = minSubArrayLen(s,nums,len-1);
	printf("%d\n", result);
	printf("###############  �������� 202 ������С��������  #############\n");
}
#pragma endregion

#pragma region 206 ��ת����
void test206() {
	printf("\n\n###############  ��ʼ���� 206 ��ת����  #############\n");
	int s = 7;
	int nums[] = { 1,2,3,4 };
	int len = sizeof(nums) / sizeof(nums[0]);
	struct ListNode* l1 = create_ListNode_from_array(nums, len);
	print_list(l1);
	struct ListNode* l2 = link_reverse(l1);
	print_list(l2);
	printf("###############  �������� 206 ��ת����  #############\n");
}
#pragma endregion

#pragma region 315 �����Ҳ�С�ڵ�ǰԪ�صĸ���
// �Ѿ�д�� ���������Ĵ��루inverse_pair_totalcount in my_sort.c��������ûд����ÿһ��Ԫ�صĴ���


#pragma endregion

#pragma region ��ʮ���� ��̬�滮
#define MAX_ROD_LENGTH 100
int bottle_up_cut_rod(int* p, int* s,int n) {
	if (n == 0) { return 0; }
	int r[MAX_ROD_LENGTH] = { 0 };
	int q = -INFINITE;
	int i = 0;
	int j = 0;
	for (i = 1;i <= n;i++) {
		q = -INFINITE;
		for (j = 1;j <= i;j++) {
			if(q< p[j] + r[i - j]){
				q = p[j] + r[i - j];
				s[i] = j;
			}
		}
		r[i] = q;
	}
	return q;
}

int memo_cut_rod(int* p, int n, int* memo, int cur) {
	if (n < 1) { return 0; }
	if (n <= cur) { return memo[n]; }

	int q = -INFINITE;
	int i = 0;
	for (i = 0;i < n; i++) {
		q = max(q, p[i] + memo[n - i - 1]);
	}
	memo[n] = q;
	return q;
}



#pragma endregion



#pragma region main
void print_array(int* nums,int length) {
	int i = 0;
	for (i = 0;i < length;i++) {
		printf("%d ",nums[i]);
	}
	printf("\n");
}
void clrs_test() {
	printf("\n\n###############  ��ʼ clrs ����  #############\n");
	//int array[100] = { 27,17,3,16,13,10,1,5,7,12,4,8,9,0 };
	int array[11] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int s[MAX_ROD_LENGTH] = { 0 };// �洢����
	int n = 9;
	int q = bottle_up_cut_rod(array,s,n);
	while (n>0) {
		printf("%d\n",s[n]);
		n = n - s[n];
	}

	printf("total profit is : %d \n",q);
	//int temp = heap_extract_max(pt->array, pt->len);
	printf("###############  ���� clrs ����  #############\n");
}
void test()
{
	printf("\n\n###############  ��ʼһ�����  ############\n");
	//random_bin3();
	//int array[100] = { 27,17,3,16,13,10,1,5,7,12,4,8,9,0 };
	int array[100] = { 5,3,17,10,84,19,6,22,9 };
	struct HeapArray* pt = (struct HeapArray*)malloc(sizeof(struct HeapArray));
	//int array[100] = { 15,13,9,5,12,8,7,4,0,6,2,1 };
	//int array[100] = { 16,14,10,8,7,9,3,2,4,1 };
	pt->array = array;
	pt->len = 9;
	//int length = sizeof(a) / sizeof(a[0]);
	build_min_heap(pt);
	print_array(pt->array, pt->len);
	//int temp = heap_extract_min(pt);
	min_heap_delete(pt,1);
	////int temp1 = heap_extract_max(pt);
	////max_heap_insert(pt,10);
	//max_heap_delete(pt,1);
	//int* nums = min_heap_sort(pt);
	print_array(pt->array, 8);
	//int temp = heap_extract_max(pt->array, pt->len);
	printf("###############  ����һ�����  #############\n");
}
int main()
{
	clrs_test();
	test();
	//test2();
	//test7();
	//test50();
	test53();
	//test67();
	//test202();
	test206();
}

#pragma endregion


