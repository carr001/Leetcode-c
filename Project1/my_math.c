double myPow(double x, int n) {
	// ǰ���� if����������
	if (x == 1 || (x == -1 && n % 2 == 0)) {
		return 1;
	}
	if (n  <-2147483647) {
		return 0;
	}
	// n must be integer
	if (n == 0) {
		return 1;
	}
	else if (n == 1) {
		return x;
	}
	else if (x == 0) {
		return 0;
	}
	else if (n < 0) {
		n = -n;
		x = 1 / x;
	}
	//ʹ�÷��η�
	int odd = n % 2;
	if (odd) {//
		n = n - 1;
		return x * myPow(x * x, n / 2);
	}
	else {
		return myPow(x * x, n / 2);
	}

}