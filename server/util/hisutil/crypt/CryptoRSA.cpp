#include "stdafx.h"
#include "CryptoRSA.h"

//#include <windows.h>
//#include <vector>


namespace HisUtil {

	typedef unsigned __int64 		DOUBLE_CRYPTO_T;	//CRYPTO_T의 2배 크기 유지해 주세요

	//버퍼 제한.(최대 n개까지만 수집한다.)
	const int reserve_count = 100;
	const int CONVERT_CNT = sizeof(CRYPTO_T) - 1;		//3byte 단위로 암호화 한다.(CRYPT_T보다 1byte작게)


	CCryptoRSA::CCryptoRSA()
		:n(0), e(0), d(0)
	{
		srand(GetTickCount());	//stdlib.h
	}

	CCryptoRSA::~CCryptoRSA()
	{
	}

	const int PRIME_RANGE = 100;
	bool CCryptoRSA::Begin(CRYPTO_T start)
	{
		//▶ 키 생성
		//1. 서로다른 소수 p와 q를 선택하고
		CRYPTO_T p = 0;// 16001;// 2357;// 11;
		CRYPTO_T q = 0;// 19681;// 2551;// 3;

		std::vector<CRYPTO_T> buff;
		CRYPTO_T i = start;
		while (buff.size() < reserve_count)
		{
			if (true == isPrime(i))
				buff.push_back(i);

			//CRYPTO_T가 4byte인 경우
			//소수의 최대 크기를 2byte로 제한합니다.
			if (4 == sizeof(CRYPTO_T))
			{
				if (0xFFFFFF <= ++i)
					break;
			}
		}

		//2개 이상(p,q가 서로다른 값을 가져야 하기 때문에)
		if (buff.size() < 2)
			return false;

		int pos = HisUtil::RandInt(0, (int)buff.size() - 1);
		p = buff.at(pos);
		//buff.clear();

		//
		do {
			pos = HisUtil::RandInt(0, (int)buff.size() - 1);
			q = buff.at(pos);
		} while (p == q);
		buff.clear();


		bool result = Begin(p, q, false);
		if (false == result)	return false;

		return true;
	}

	bool CCryptoRSA::Begin(CRYPTO_T p, CRYPTO_T q, bool bPrimeCheck)
	{
		//▶ 키 생성
		//1. 서로다른 소수 p와 q를 선택하고
		if (p == q)		return false;

		//CRYPTO_T가 4byte인 경우
		//소수의 최대 크기를 2byte로 제한합니다.
		if (4 == sizeof(CRYPTO_T))
		{
			if (0xFFFFFF <= p)		return false;
			if (0xFFFFFF <= q)		return false;
		}

		//소수여부 체크
		if (true == bPrimeCheck)
		{
			if (false == isPrime(p))	return false;
			if (false == isPrime(q))	return false;
		}


		//2. 이들의 곱 n = pq를 계산한다.
		n = p * q;


		//3. phi( φ(n) = (p - 1)(q - 1) )를 구한다.
		CRYPTO_T phi = (p - 1) * (q - 1);//φ(n) = (p - 1)(q - 1)


		//find e
		e = find_e(phi);

		//find d
		d = find_d(phi);	//private key
		return true;
	}

	CRYPTO_T CCryptoRSA::Encrypt(CRYPTO_T m)
	{
		//▶ encrypt
		//C = m^e·mod n
		CRYPTO_T C = mod_pow(m, e, n);// pow(m,e) % n
		//printf("encrypt : %lld\n", C);
		////printf("%d\n", mod(582, 129));
		return C;
	}

	CRYPTO_T CCryptoRSA::Decrypt(CRYPTO_T C)
	{
		//▶ decrypt
		//D = C^d·mod n
		CRYPTO_T D = mod_pow(C, d, n);// pow(C,d) % n
		//printf("decrypt : %lld\n", D);
		return D;
	}

	void CCryptoRSA::Encrypt(char* in, int insize, char* out, int& outsize)
	{
		std::vector<CRYPTO_T> buff;
		buff.reserve(insize);

		//입력문자열(in)을 CONVERT_CNT(3byte)단위로 암호화를 진행한다.
		for (int i = 0; i < insize; i += CONVERT_CNT)
		{
			//m[size] = (*(CONVERT_T*)(msg + i));
			CRYPTO_T tmp = 0;
			memcpy(&tmp, in + i, CONVERT_CNT);
			buff.push_back(tmp);
		}

		//encrypt(4byte - (CONVERT_CNT+1))
		for (int i = 0; i < buff.size(); ++i)
		{
			CRYPTO_T tmp = Encrypt(buff[i]);

			int pos = i * (CONVERT_CNT + 1);
			memcpy(out + pos, &tmp, (CONVERT_CNT + 1));
		}
		outsize = (CRYPTO_T)buff.size() * (CONVERT_CNT + 1);
		//printf("\n");
		//buff.clear();
	}

	void CCryptoRSA::Decrypt(char* in, int insize, char* out, int& outsize)
	{
		std::vector<CRYPTO_T> buff;
		buff.reserve(insize);

		//입력문자열(in)은 4byte로 구성된다.
		for (int i = 0; i < insize; i += (CONVERT_CNT + 1))
		{
			//m[size] = (*(CONVERT_T*)(msg + i));
			CRYPTO_T tmp = 0;
			memcpy(&tmp, in + i, (CONVERT_CNT + 1));
			buff.push_back(tmp);
		}

		//decrypt
		for (int i = 0; i < buff.size(); ++i)
		{
			CRYPTO_T tmp = Decrypt(buff[i]);

			int pos = i * CONVERT_CNT;
			memcpy(out + pos, &tmp, CONVERT_CNT);
		}
		outsize = (CRYPTO_T)buff.size() * CONVERT_CNT;
		//printf("\n");
		//buff.clear();
	}

	bool CCryptoRSA::isPrime(CRYPTO_T pr)
	{
		CRYPTO_T j = (CRYPTO_T)sqrt(pr);
		for (CRYPTO_T i = 2; i <= j; i++)
		{
			if (pr % i == 0)
				return false;
		}
		return true;
	}

	/* Standard C Function: Greatest Common Divisor */
	CRYPTO_T CCryptoRSA::gcd(CRYPTO_T a, CRYPTO_T b)
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

		CRYPTO_T c;
		while (a != 0) {
			c = a; a = b%a;  b = c;
		}
		return b;
	}

	/* Recursive Standard C Function: Greatest Common Divisor */
	CRYPTO_T CCryptoRSA::gcdr(CRYPTO_T a, CRYPTO_T b)
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
	CRYPTO_T CCryptoRSA::mod_pow(CRYPTO_T base, CRYPTO_T exp, CRYPTO_T MOD)
	{
		CRYPTO_T result = 1;

		//원코드에서는 없는건데...나중에 체크하게 될까봐.
		//우선, 주석처리함.
		//base %= MOD;
		while (exp > 0) {
			if (exp & 1)//if (exp % 2 == 1)
			{
				//DOUBLE_CRYPTO_T a1 = (DOUBLE_CRYPTO_T)result*base;
				//if (base != (CRYPTO_T)(a1 / result))
				//{
				//	printf("a1 overflow result[%lld], base[%lld], MOD[%lld]\n", result, base, MOD);
				//}
				result = (CRYPTO_T)(((DOUBLE_CRYPTO_T)result*base) % MOD);
			}
			//DOUBLE_CRYPTO_T b1 = (DOUBLE_CRYPTO_T)base*base;
			//if (base != (CRYPTO_T)(b1 / base))
			//{
			//	printf("b1 overflow result[%lld], base[%lld], MOD[%lld]\n", result, base, MOD);
			//}
			base = (CRYPTO_T)(((DOUBLE_CRYPTO_T)base*base) % MOD);
			exp >>= 1;//exp /= 2;
		}
		return result%MOD;
	}

	CRYPTO_T CCryptoRSA::find_e(CRYPTO_T phi)
	{
		//4. 다음 조건에 만족하는 e를 찾는다.
		//	1 < e < φ(n), gcd(e,φ(n)) = 1 (여기서 gcd는 최대 공약수를 의미합니다.)
		//---------------------------------------------------------------------------
		//  ∵ φ(n) = (p-1)(q-1) 이므로 gcd(e,φ(n))는 gcd(e,(p-1)(q-1))와 같습니다.
		//		∴(그렇기 때문에) gcd(e,(p-1)) = 1과 gcd(e,(q-1)) = 1일때
		//			gcd(e,φ(n)) 는 1일수 밖에 없습니다.
		//	∴(그러므로), ∵(왜냐하면)
		//---------------------------------------------------------------------------
		std::vector<CRYPTO_T> E;
		for (CRYPTO_T i = 2; i < phi; ++i)
		{
			//위∵ 참조
			if (1 == gcd(i, phi))
			{
				e = i;
				E.push_back(i);
				//printf("e:%lld\n", e);
				//break;

				if (reserve_count < E.size())
					break;
			}
		}

		if (0 == E.size())
			return 0;

		int pos = RandInt(0, (int)E.size() - 1);
		//e = E[pos];
		//E.clear();
		return E.at(pos);
	}

	CRYPTO_T CCryptoRSA::find_d(CRYPTO_T phi)
	{
		//5. 다음 조건에 만족하는 d를 구합니다.
		//	1 < d < φ(n), e*d (mode φ(n)) = 1 ( e*d 를 mode φ(n) 로 나누면 나머지가 1 이다)
		//	∴ e*d 보다 1 작은수를 φ(n)으로 나누면 0입니다.
		//		식, (e*d-1) % φ(n) = 0
		for (CRYPTO_T i = 2; i < phi; ++i)
			//for (CRYPTO_T i = phi; i > 2 ; --i)
		{
			//DOUBLE_CRYPTO_T tmp = (DOUBLE_CRYPTO_T)e*i;
			//if (e != (CRYPTO_T)(tmp / i))
			//{
			//	printf("overflow e[%lld], i[%lld]\n", e, i);
			//}
			if (0 == (((DOUBLE_CRYPTO_T)e*i) - 1) % phi)
			{
				//d = i;
				//printf("d:%lld\n", d);
				////break;
				return i;
			}
		}
		return 0;
	}


};//..namespace HisUtil {
