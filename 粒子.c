#include<stdio.h>
#include<Windows.h>
int main()
{
	system("color f5");
	printf("woquwozhendeniubibamoyumochulaizhezhongdongxi\n");
	float x, y, a;
	for (y = 1.5f; y > -1; y -= 0.1f)
	{
		for (x = -1.5f; x < 1.5f; x += .05f)
		{
			a = x * x + y * y - 1;
			printf(a * a * a - x * x * y * y * y <= 0.0f ? "*" : " ");
		}
		Sleep(150);
		printf("\n");
	}
	return 0;
}