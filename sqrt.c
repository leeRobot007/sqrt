#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/timeb.h>

//timeb�ô�д����ʾ
#define TIMEB timeb

//ȫ�ֵĺ�����ֱ�ӻ�ȡx�ľ���ֵ
#define ABS(x) ((x)>0?(x):-(x))

//�������
#define eps 1e-10

//ţ�ٷ�
double sqrt1(double xi)
{
	//����ƽ����
 
	double g =  xi;

	//��������ڿ��ƾ���֮��
	while (ABS(g*g - x)>eps)
	{
		//������ʽ
		g = (g + x / g) / 2;
	}
	return g;
}

//����[0,2)��Χ������ƽ����
double Tsqrt(double x)
{
	//ͨ��̩�չ�ʽ���
	double sum, coffe, factorial, xpower, term;
	int i;
	sum = 0;  //���
	coffe = 1;
	factorial = 1;
	xpower = 1;

	//ÿһ�μ���Ķ���ʽ��ֵ����һ��Ϊ1
	term = 1; 
	i = 0;

	//������ʽ�Ľ��С�ھ��Ⱦ��˳�
	while (ABS(term)>eps)
	{
		sum += term;
		coffe *= (0.5 - i);//ϵ��
		factorial *= (i + 1); //�׳�		
		xpower *= (x - 1); //����ʽ
		term = coffe * xpower / factorial;
		i++;
	}
	return sum;
}

//�����ƽ���
double sqrt2(double x)
{
	//����2����Ҫת��Ϊ[0,2)������ȥ
	double correction = 1;

	//�����ֱ任��С��2
	while (x >= 2)
	{
		x /= 4;
		correction *= 2;
	}
	//��С��2�Ľ�����Ա任ϵ��
	return Tsqrt(x)*correction;
}

//ƽ�����������㷨������˷�ת��
float sqrt3(float xi) 
{
	
	//���泤����
	long i;

	//��Ϊfloat
	float number = (float)xi;
	float x, y;
	const float f = 1.5F;
	x = number * 0.5F;
	y = number;
	i = *(long *)&y;//����������ʾ���ڴ�ת��Ϊ����
	i = 0x5f3759df - (i >> 1); //ע����һ�� 
	y = *(float*)&i;

	//ţ�ٵ���
	y = y * (f - (x * y * y));
	y = y * (f - (x * y * y));

	//����ƽ����
	return number * y;
}

//���ַ�
double sqrt4(double x)
{
	//ǰ��������ֵ
	double low, up, mid;
	low = 0, up = (x >= 1 ? x : 1);
	mid = (low + up) / 2;
	do
	{
		//ͨ���м�ֵ��ƽ���Ľ����ѡ���м�ֵ��ֵ��С�����Ǵ���
		if (mid*mid>x)
			up = mid;
		else
			low = mid;
		mid = (up + low) / 2;

		//���ƾ���
	} while (ABS(mid - low) > eps);

	return mid;
}

//���������Ƚ�Ч��
int main() 
{
	//��Ϊһ�εļ���ʱ��̫�̣��������Ӽ������
	int number = 100000;

	//������
	double y, y1, y2, y3,y4;

	//����ʱ��
	double t, t1, t2, t3,t4;

	//����20����ֵ
	for (int i = 0; i<20; i++)
	{
		//����һ�����ڵ���ֵ��ƽ����
		double x = rand() % 10000;

		//��ʼʱ��ͽ���ʱ��
		clock_t start, finish;

		//���õĺ���
		start = clock();
		for (int j = 0; j < number; j++)
		{
			y = sqrt(x);
		}
		finish = clock();
		t = finish-start;

		//ţ�ٷ�
		start = clock();
		for (int j = 0; j < number; j++)
		{
			y1 = sqrt1(x);
		}
		finish = clock();
		t1 = finish - start;
		
		//�����ƽ���
		start = clock();
		for (int j = 0; j < number; j++)
		{
			y2 = sqrt2(x);
		}
		finish = clock();
		t2 = finish - start;

		//ƽ����������
		start = clock();
		float x1 = (float)x;
		for (int j = 0; j < number; j++)
		{
			y3 = sqrt3(x1);
		}
		finish = clock();
		t3 = finish - start;

		//���ַ�
		start = clock();
		for (int j = 0; j < number; j++)
		{
			y4 = sqrt4(x);
		}
		finish = clock();
		t4 = finish - start;

		printf("x=%7.2f y=%16.11f <%6.2f>,y1=%16.11f <%6.2f>,y2=%16.11f <%6.2f>,y3=%16.11f <%6.2f>,y4=%16.11f <%6.2f>\n", x, y, t, y1, t1, y2, t2, y3, t3,y4,t4);
	}
	
	system("pause");
	return 0;

}