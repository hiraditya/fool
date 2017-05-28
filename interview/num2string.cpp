#include<cstdio>

void num2str(int n) {
char buffer[50];
int i = 0;

bool isNeg = n<0;

unsigned int n1 = isNeg ? -n : n;

while(n1!=0)
{
    buffer[i++] = n1%10+'0';
    n1=n1/10;
}

if(isNeg)
    buffer[i++] = '-';

buffer[i] = '\0';

for(int t = 0; t < i/2; t++)
{
    buffer[t] ^= buffer[i-t-1];
    buffer[i-t-1] ^= buffer[t];
    buffer[t] ^= buffer[i-t-1];
}

if(n == 0)
{
    buffer[0] = '0';
    buffer[1] = '\0';
}   

printf("%s\n", buffer);
}

int main() {
	// your code goes here
	num2str(-1);
	num2str(-0);
	num2str(100);
	num2str(-100);
	return 0;
}
