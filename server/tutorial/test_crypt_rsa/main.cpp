// test_crypt_ras.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


#include<iostream>
#include<math.h>
#include <conio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

const int max_buffer = 100;
const int key_pos = 0;

//long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
long int p, q, n, t, flag, e[max_buffer], d[max_buffer], temp[100], j, m[100], en[100], i;
char msg[100] = "ABCDEFGHJIKLMNOPQRSTUVWXYZabcdefghjiklmnopqrstuvwxyz0123456789";

bool isPrime(__int64 pr)
{
	__int64 j = (__int64)sqrt(pr);
	for (__int64 i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return false;
	}
	return true;
}
/* Standard C Function: Greatest Common Divisor */
__int64 gcd(__int64 a, __int64 b)
{
	//===========================================
	//�ִ� �����
	//12�� ��� = 1,2,3,4,6,12
	//18�� ��� = 1,2,3,6,9,18
	//
	//����� = 1,2,3,6     <--6:�ִ�����

	//===========================================
	//�ּ� �����
	//2�� ��� = 2,4,6,8,10,12,14,16,18,...
	//3�� ��� = 3,6,9,12,15,18,...
	//
	//����� = 6,12,18,...       <--6:�ּҰ���� 

	__int64 c;
	while (a != 0) {
		c = a; a = b%a;  b = c;
	}
	return b;
}

/* Recursive Standard C Function: Greatest Common Divisor */
__int64 gcdr(__int64 a, __int64 b)
{
	if (a == 0) return b;
	return gcdr(b%a, a);
}

//pow(b,e) % m ==> (b^e % m)
//pow()�Լ��� �����÷ο��� �߻��ؼ� ã�� �Լ��� �Ʒ��̴�.
//	exp)	13 ^ 7 = 62748717 ���� 7�� (4 + 2 + 1)
//				13 ^ 4 = 28561
//				13 ^ 2 = 169
//				13 ^ 1 = 13
//			�� 13^7 = (13^4) * (13^2) * (13^1)
//
//	���⼭���� ��¥ ������(�μ����ذ� �˴ϴ�)
//		����) bc mod n = (b mod n).(c mod n) mod n
//		modulo 33
//			13^1 = 13
//			13^2 = 169 �� 4
//			13^4 = 4*4 = 16
//			13^8 = 16*16 = 256 �� 25
//			...
//		since 7 = (4 + 2 + 1)
//			we have m' = 13^7 = 13^(4+2+1) = 13^4 * 13^2 * 13^1�� 16 * 4 * 13 = 832 �� 7 mod 33
__int64 mod_pow(__int64 base, __int64 exp, __int64 MOD) {
	//base %= MOD;//���ڵ忡���� ���°ǵ�...�ּ�ó����.
	__int64 result = 1;
	while (exp > 0) {
		if (exp & 1)//if (exp % 2 == 1)
			result = (result*base) % MOD;
		base = (base*base) % MOD;
		exp >>= 1; //exp /= 2;
	}
	return result%MOD;
}

#include <windows.h>
#include <vector>
inline int   RandInt(int x, int y) { return rand() % (y - x + 1) + x; }
int main()
{
	////mod_pow() ��������
	//printf("mod_pow:%lld\n", mod_pow(5, 7, 9));
	//printf("mod_pow:%lld\n", mod_pow(9, 7, 5));
	//printf("pow:%lld\n", (__int64)pow(9, 7) % 5);

	//printf("test:%lld\n", (__int64)pow(13, 1) % 33);
	//printf("test:%lld\n", (__int64)pow(13, 2) % 33);
	//printf("test:%lld\n", (__int64)pow(13, 4) % 33);
	//printf("test:%lld\n", 13*4*16 % 33);


	////�Ҽ� Ȯ��
	//for (__int64 i = 10000; i < 20000; ++i)
	//{
	//	if (true == isPrime(i))
	//		printf("\t%lld", i);
	//}

	//�� Ű ����
	//1. ���δٸ� �Ҽ� p�� q�� �����ϰ�
	//2. �̵��� �� n = pq�� ����Ѵ�.
	//3. phi( ��(n) = (p - 1)(q - 1) )�� ���Ѵ�.
	__int64 p = 2357;// 16001;// 2357;// 11;
	__int64 q = 2551;// 19681;// 2551;// 3;
	__int64 n = p * q;
	__int64 phi = (p - 1) * (q - 1);//��(n) = (p - 1)(q - 1)
	__int64 e = 0;	//public key
	__int64 d = 0;	//private key

	//4. ���� ���ǿ� �����ϴ� e�� ã�´�.
	//	1 < e < ��(n), gcd(e,��(n)) = 1 (���⼭ gcd�� �ִ� ������� �ǹ��մϴ�.)
	//---------------------------------------------------------------------------
	//  �� ��(n) = (p-1)(q-1) �̹Ƿ� gcd(e,��(n))�� gcd(e,(p-1)(q-1))�� �����ϴ�.
	//		��(�׷��� ������) gcd(e,(p-1)) = 1�� gcd(e,(q-1)) = 1�϶�
	//			gcd(e,��(n)) �� 1�ϼ� �ۿ� �����ϴ�.
	//	��(�׷��Ƿ�), ��(�ֳ��ϸ�)
	//---------------------------------------------------------------------------
	std::vector<__int64> E;
	for (__int64 i = 2; i < phi; ++i)
	{
		//���� ����
		if (1 == gcd(i, phi))
		{
			e = i;
			E.push_back(i);
			//printf("e:%lld\n", e);
			//break;
		}
	}

	srand(GetTickCount());
	int pos = RandInt(0, E.size());
	e = E[pos];
	E.clear();

	//e = 6006521;
	printf("e:%lld\n", e);


	//5. ���� ���ǿ� �����ϴ� d�� ���մϴ�.
	//	1 < d < ��(n), e*d (mode ��(n)) = 1 ( e*d �� mode ��(n) �� ������ �������� 1 �̴�)
	//	�� e*d ���� 1 �������� ��(n)���� ������ 0�Դϴ�.
	//		��, (e*d-1) / ��(n) = 0
	for (__int64 i = 2; i < phi; ++i)
	{
		if (0 == (((e*i) - 1) % phi))
		{
			d = i;
			printf("d:%lld\n", d);
			//break;
		}
	}

	//6. public key�� (n, e)
	//7. private key�� (n, d) �Դϴ�.

	//char�� �迭�� ó���ϱ� ������ 255�� ���� ������ ������.
	__int64 m = 165000;// 5000;// 255;// 5;

	//�� encrypt
	//C = m^e��mod n
	__int64 C = mod_pow(m, e, n);// pow(m,e) % n
	printf("encrypt : %lld\n", C);
	//printf("%d\n", mod(582, 129));

	//�� decrypt
	//D = C^d��mod n
	__int64 D = mod_pow(C, d, n);// pow(C,d) % n
	printf("decrypt : %lld\n", D);

	system("pause");
	return 0;
}
