// test_crypt_ras.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	//최대 공약수
	//12의 약수 = 1,2,3,4,6,12
	//18의 약수 = 1,2,3,6,9,18
	//
	//공약수 = 1,2,3,6     <--6:최대공약수

	//===========================================
	//최소 공배수
	//2의 배수 = 2,4,6,8,10,12,14,16,18,...
	//3의 배수 = 3,6,9,12,15,18,...
	//
	//공배수 = 6,12,18,...       <--6:최소공배수 

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
//pow()함수는 오버플로워가 발생해서 찾은 함수가 아래이다.
//	exp)	13 ^ 7 = 62748717 에서 7은 (4 + 2 + 1)
//				13 ^ 4 = 28561
//				13 ^ 2 = 169
//				13 ^ 1 = 13
//			∴ 13^7 = (13^4) * (13^2) * (13^1)
//
//	여기서부터 진짜 신중히(인수분해가 됩니다)
//		공식) bc mod n = (b mod n).(c mod n) mod n
//		modulo 33
//			13^1 = 13
//			13^2 = 169 ≡ 4
//			13^4 = 4*4 = 16
//			13^8 = 16*16 = 256 ≡ 25
//			...
//		since 7 = (4 + 2 + 1)
//			we have m' = 13^7 = 13^(4+2+1) = 13^4 * 13^2 * 13^1≡ 16 * 4 * 13 = 832 ≡ 7 mod 33
__int64 mod_pow(__int64 base, __int64 exp, __int64 MOD) {
	//base %= MOD;//원코드에서는 없는건데...주석처리함.
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
	////mod_pow() 검증로직
	//printf("mod_pow:%lld\n", mod_pow(5, 7, 9));
	//printf("mod_pow:%lld\n", mod_pow(9, 7, 5));
	//printf("pow:%lld\n", (__int64)pow(9, 7) % 5);

	//printf("test:%lld\n", (__int64)pow(13, 1) % 33);
	//printf("test:%lld\n", (__int64)pow(13, 2) % 33);
	//printf("test:%lld\n", (__int64)pow(13, 4) % 33);
	//printf("test:%lld\n", 13*4*16 % 33);


	////소수 확인
	//for (__int64 i = 10000; i < 20000; ++i)
	//{
	//	if (true == isPrime(i))
	//		printf("\t%lld", i);
	//}

	//▶ 키 생성
	//1. 서로다른 소수 p와 q를 선택하고
	//2. 이들의 곱 n = pq를 계산한다.
	//3. phi( φ(n) = (p - 1)(q - 1) )를 구한다.
	__int64 p = 2357;// 16001;// 2357;// 11;
	__int64 q = 2551;// 19681;// 2551;// 3;
	__int64 n = p * q;
	__int64 phi = (p - 1) * (q - 1);//φ(n) = (p - 1)(q - 1)
	__int64 e = 0;	//public key
	__int64 d = 0;	//private key

	//4. 다음 조건에 만족하는 e를 찾는다.
	//	1 < e < φ(n), gcd(e,φ(n)) = 1 (여기서 gcd는 최대 공약수를 의미합니다.)
	//---------------------------------------------------------------------------
	//  ∵ φ(n) = (p-1)(q-1) 이므로 gcd(e,φ(n))는 gcd(e,(p-1)(q-1))와 같습니다.
	//		∴(그렇기 때문에) gcd(e,(p-1)) = 1과 gcd(e,(q-1)) = 1일때
	//			gcd(e,φ(n)) 는 1일수 밖에 없습니다.
	//	∴(그러므로), ∵(왜냐하면)
	//---------------------------------------------------------------------------
	std::vector<__int64> E;
	for (__int64 i = 2; i < phi; ++i)
	{
		//위∵ 참조
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


	//5. 다음 조건에 만족하는 d를 구합니다.
	//	1 < d < φ(n), e*d (mode φ(n)) = 1 ( e*d 를 mode φ(n) 로 나누면 나머지가 1 이다)
	//	∴ e*d 보다 1 작은수를 φ(n)으로 나누면 0입니다.
	//		식, (e*d-1) / φ(n) = 0
	for (__int64 i = 2; i < phi; ++i)
	{
		if (0 == (((e*i) - 1) % phi))
		{
			d = i;
			printf("d:%lld\n", d);
			//break;
		}
	}

	//6. public key는 (n, e)
	//7. private key는 (n, d) 입니다.

	//char형 배열을 처리하기 때문에 255를 넘을 이유는 없을듯.
	__int64 m = 165000;// 5000;// 255;// 5;

	//▶ encrypt
	//C = m^e·mod n
	__int64 C = mod_pow(m, e, n);// pow(m,e) % n
	printf("encrypt : %lld\n", C);
	//printf("%d\n", mod(582, 129));

	//▶ decrypt
	//D = C^d·mod n
	__int64 D = mod_pow(C, d, n);// pow(C,d) % n
	printf("decrypt : %lld\n", D);

	system("pause");
	return 0;
}
