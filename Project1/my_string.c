char* str_concat(char* dest, char* src)
{
	// ���ܵ�bug, destԤ�ȷ�����ڴ���Ҫ�㹻�󣬲�Ȼ���ܵ���ı������ڴ�����
	char* p = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	*dest = *src;
	dest++;
	src++;
	while ((*src) != '\0')
	{
		*dest++ = *src++;
	}
	return p;
}

char* str_inverse(char* s)
{
	char* p = s;
	char* temp = (char*)malloc(strlen(s) + 1);//ע�⣬���malloc(strlen(s)),��ôfree��ʱ���������Ǳ������Ĳ��ԣ���ʱ��Ϊ������������alloc����ڴ棬����������ֱ�Ӱѳ�����Ϊ�������롣
	strcpy(temp, s);//���߶�����

	int len = 0;
	while (*s != '\0')
	{
		s++;
		len++;
	}
	int i = 0;
	s = p;
	while (i < len)
	{
		s[i] = temp[len - 1 - i];
		i++;
	}
	free(temp);
	return p;
}

	
