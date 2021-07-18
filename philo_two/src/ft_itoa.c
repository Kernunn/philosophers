void ft_itoa(char *ans, int n) {
  long int number;
  int count;

  count = (n <= 0 ? 1 : 0);
  number = n;
  ans[0] = '0';
  while (n != 0) {
	count++;
	n = n / 10;
  }
  if (number < 0) {
	number = -number;
	ans[0] = '-';
  }
  while (number > 0) {
	ans[count - 1] = number % 10 + '0';
	number /= 10;
	count--;
  }
}
