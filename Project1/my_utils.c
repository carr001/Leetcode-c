#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>

#if defined(WIN32)
# define  TIMEB    _timeb
# define  ftime    _ftime
typedef __int64 TIME_T;
#else
#define TIMEB timeb
typedef long long TIME_T;
#endif

long long int dec2bin(long long int a)
{
	// ʲôʱ���������ʲôʱ�����ַ��ָ�룩�����ݳ��̣����ݳ��ʹ�ָ��
	long long int old_temp = 0;
	long long int new_temp = 0;
	long long int i = 1;
	while (a != 0)
	{
		new_temp = a % 2 * i;
		old_temp = new_temp + old_temp;
		a = a / 2;
		i = i * 10;
	}
	return old_temp;
}

long long int bin2dec(long long int a)
{
	long long int old_temp = 0;
	long long int new_temp = 0;
	long long int i = 1;
	while (a != 0)
	{
		new_temp = (a % 10) * i;
		old_temp = new_temp + old_temp;
		a = a / 10;
		i = i * 2;
	}
	return old_temp;

}

long long int str2bint(char* s)
{
	// ����ʮ����
	long long int temp = 0;
	int len = strlen(s);
	int i = len - 1; //���㿪ʼ
	long long int mul = 1;
	while (i >= 0)
	{
		temp = (s[i] - '0') * mul + temp;
		i = i - 1;
		mul = mul * 10;
	}
	return temp;
}

char* int2str(long long int a)
{
	char* s = (char*)malloc(100);
	memset(s, 0, sizeof(s));
	char temp[] = "0";
	long long int a_temp = a;
	int a_len = 0;
	while (a_temp != 0)
	{
		a_len += 1;
		a_temp /= 10;
	}

	s[a_len] = '\0';
	a_len -= 1;
	while (a_len >= 0)
	{
		s[a_len] = a % 10 + '0';
		a_len -= 1;
		a /= 10;
	}
	return s;
}

long long int integer_inverse(long long int x) {
	int neg = 0;
	if (x < 0) {
		x = -x;
		neg = 1;
	}
	long long int inv = 0;
	int i = 10;
	while (x != 0) {
		inv = inv * i + x % 10;
		x /= 10;
	}
	if (inv > 2147483648) {
		return 0;
		//�������2��31�η��������������0
	}
	if (neg) {
		inv = -inv;
	}
	return inv;
}

// ����α�����
// �������� 0 1����ķ���
// ����1��΢�뼶��Ч����ã�����2��3�޷�ʹ��

#pragma region ����1��΢�

int random_bin3() {
	//LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	long long int ti;
	//QueryPerformanceFrequency(&nFreq);  // from  <windows.h>
	QueryPerformanceCounter(&nBeginTime);
	//ti = (double)(nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	ti = (long long int)(nBeginTime.QuadPart);
	//ti = ti - (int)ti;                //ֻҪС������
	int to = ti % 2; //ȡ1e7���Ӳ�ȷ����
	//printf("%d\n", to);
	return to;
}
#pragma endregion

#pragma region ����2�����뼶
int random_bin2() {
	struct TIMEB ts1; // from sys/timeb.h
	TIME_T t1;
	ftime(&ts1);
	t1 = (TIME_T)ts1.millitm;
	printf("%I64d\n", t1);
	return  t1 % 2;
}
#pragma endregion

#pragma region ����3���뼶
int random_bin1() { // from time.h
	time_t timep;		// int ����
	struct tm* p;
	time(&timep);		//�ѵ�ǰʱ��ŵ�ָ�����ڴ�����
	p = gmtime(&timep);	// ��ȡʱ��ṹ��
	int temp = p->tm_sec % 2;
	//free(p);
	return temp;
}
#pragma endregion

//  �������������������ȡ��ʱ������ż�ĸ�����ͬ����ʱ��һ���貢�����㣬������ƫ������0.5���ʵ�0��1�����ϰ��5.1-3
// ����������޸�֮�������Ϻ������������ˣ�����΢����Ҫ�ĵ����������٣������ϰ����
int random_bin_unbias() {
	while (1) {
		int x = random_bin3();
		int y = random_bin3();
		if (x!=y) {
			return x;
		}
	}
}

// �������ⷶΧ�ľ��ȷֲ�
int random_range(int sml, int big) {
	if (big == sml) {
		return sml;
	}
	int bits = log2(big - sml) + 1;
	int low_bit = 0;
	int result = 0;
	while (bits>-1) {
		low_bit = random_bin_unbias();
		result = (result << 1) + low_bit;
		bits--;
	}
	if (result > (big - sml)) {
		result = random_range(0, big - sml);
	}
	return sml + result;
}

#pragma region ΢��������

#define UNCHOOSE_MASK 1
int find_unchoose_position(int* output, int index) {
	// suppose -1 means unchoosed element
	int* p = output;
	int i = 0;
	while (index > -1) {
		if (*(p + i) == UNCHOOSE_MASK) {
			index--;
		}
		i++;
	}
	i--;
	return i;
}
void red_pocket_random_split(int* output, int total, int number_of_peoples) {
	//˼·����������о��ǵ��±�i���ǵ�i���˻�ǿ���Ľ�
	// ����˼·�������ܽ��10Ԫ����4���ˡ������е�һ��Ԫ�������1-10�в���һ����x��Ȼ��ڶ�����10-x�����ȡy����������10-x-y�����...
	// ���⣺��һ��Ԫ�ص������� 5���ڶ�����2.5,....������ϣ��ÿ��Ԫ�ص���������2.5
	// ����������ȴ�1-4�����ѡȡһ����������3��Ȼ�������1-10�в���һ��������Ϊ��������������ֵ;Ȼ���ڴ�ʣ��λ�����ѡȡһ��λ�ã���10-x���������һ�������Դ����ơ�
	if (number_of_peoples == 1) {
		int position = find_unchoose_position(output, number_of_peoples - 1);
		output[position] = output[position] + total;
	}
	else {
		int index = random_range(0, number_of_peoples - 1);
		int position = find_unchoose_position(output, index);
		int money = random_range(0, total);
		output[position] = output[position] + money;
		number_of_peoples--;
		red_pocket_random_split(output, total - money, number_of_peoples);
	}
}
void test_redpocket() {
	printf("\n\n###############  ��ʼ����΢��������  #############\n");
	//random_bin3();
	#define NUMBERS_OF_PEO 20
	#define UNCHOOSE_MASK 1
	#define TOTAL_MONEY 50
	int output[NUMBERS_OF_PEO] = { 0 };
	int i = NUMBERS_OF_PEO;
	while (i > 0) {
		output[i - 1] = UNCHOOSE_MASK;// ÿ�������ٵõ�1Ԫ
		i--;
	}
	red_pocket_random_split(output, TOTAL_MONEY - NUMBERS_OF_PEO, NUMBERS_OF_PEO);
	print_array(output, NUMBERS_OF_PEO);
	printf("###############  ��������  #############\n");
}
#pragma endregion


void swap_array(int* nums,int idx1,int idx2) {
	int temp = *(nums + idx1);
	*(nums + idx1) = *(nums+idx2);
	*(nums + idx2) = temp;
}

void random_shuffle_by_swapping(int* nums,int length) {
	while (length>0) {
		int rand = random_range(0,length-1);
		swap_array(nums,rand,length-1);
		length--;
	}
}
