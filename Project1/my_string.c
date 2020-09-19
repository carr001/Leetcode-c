char* str_concat(char* dest, char* src)
{
	// 可能的bug, dest预先分配的内存需要足够大，不然会跑到别的变量的内存区域
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
	char* temp = (char*)malloc(strlen(s) + 1);//注意，如果malloc(strlen(s)),那么free的时候会出错，这是编译器的策略，暂时认为编译器不怕你alloc大的内存，或者期望你直接把长度作为参数输入。
	strcpy(temp, s);//二者都可以

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

	
