int ft_atoi(const char *str) {
  int sign;
  long long ans;

  ans = 0;
  while ((*str >= 9 && *str <= 13) || *str == ' ')
	str++;
  sign = (*str == '-' ? -1 : 1);
  if (*str == '+' || *str == '-')
	str++;
  while (*str >= '0' && *str <= '9') {
	if (sign * ans * 10 < sign * ans)
	  return (sign < 0 ? 0 : -1);
	ans = ans * 10 + sign * (*str++ - '0');
  }
  return ((int) ans);
}
