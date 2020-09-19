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
	// 什么时候传入变量，什么时候传入地址（指针）看数据长短，数据长就传指针
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
	// 当作十进制
	long long int temp = 0;
	int len = strlen(s);
	int i = len - 1; //从零开始
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
		//如果大于2的31次方，则溢出，返回0
	}
	if (neg) {
		inv = -inv;
	}
	return inv;
}

// 生成伪随机数
// 三种生成 0 1随机的方法
// 方法1是微秒级，效果最好，方法2，3无法使用

#pragma region 方法1，微妙级

int random_bin3() {
	//LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	long long int ti;
	//QueryPerformanceFrequency(&nFreq);  // from  <windows.h>
	QueryPerformanceCounter(&nBeginTime);
	//ti = (double)(nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	ti = (long long int)(nBeginTime.QuadPart);
	//ti = ti - (int)ti;                //只要小数部分
	int to = ti % 2; //取1e7增加不确定性
	//printf("%d\n", to);
	return to;
}
#pragma endregion

#pragma region 方法2，毫秒级
int random_bin2() {
	struct TIMEB ts1; // from sys/timeb.h
	TIME_T t1;
	ftime(&ts1);
	t1 = (TIME_T)ts1.millitm;
	printf("%I64d\n", t1);
	return  t1 % 2;
}
#pragma endregion

#pragma region 方法3，秒级
int random_bin1() { // from time.h
	time_t timep;		// int 类型
	struct tm* p;
	time(&timep);		//把当前时间放到指定的内存区域
	p = gmtime(&timep);	// 获取时间结构体
	int temp = p->tm_sec % 2;
	//free(p);
	return temp;
}
#pragma endregion

//  上面三个方法都假设获取的时间是奇偶的概率相同，有时这一假设并不满足，下面无偏的生成0.5概率的0，1，详见习题5.1-3
// 经过下面的修改之后，理论上毫秒和妙都可以用了，不过微妙需要的迭代次数最少，详情见习题解答
int random_bin_unbias() {
	while (1) {
		int x = random_bin3();
		int y = random_bin3();
		if (x!=y) {
			return x;
		}
	}
}

// 生成任意范围的均匀分布
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

#pragma region 微信随机红包

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
	//思路：输出的数列就是的下标i就是第i个人会强到的金额。
	// 初步思路：假设总金额10元，共4个人。数组中第一个元素随机从1-10中产生一个数x，然后第二个从10-x中随机取y，第三个从10-x-y中随机...
	// 问题：第一个元素的期望是 5，第二个是2.5,....而我们希望每个元素的期望都是2.5
	// 解决方案：先从1-4中随机选取一个数，比如3，然后随机从1-10中产生一个数，作为输出数组第三个的值;然后在从剩下位置随机选取一个位置，从10-x再随机产生一个数，以此类推。
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
	printf("\n\n###############  开始测试微信随机红包  #############\n");
	//random_bin3();
	#define NUMBERS_OF_PEO 20
	#define UNCHOOSE_MASK 1
	#define TOTAL_MONEY 50
	int output[NUMBERS_OF_PEO] = { 0 };
	int i = NUMBERS_OF_PEO;
	while (i > 0) {
		output[i - 1] = UNCHOOSE_MASK;// 每个人最少得到1元
		i--;
	}
	red_pocket_random_split(output, TOTAL_MONEY - NUMBERS_OF_PEO, NUMBERS_OF_PEO);
	print_array(output, NUMBERS_OF_PEO);
	printf("###############  结束测试  #############\n");
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
