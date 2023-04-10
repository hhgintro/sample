#pragma once

namespace HisUtil {
	//두 소수(p,q)는 2byte일 이면 phi,e는 4byte이다
	// fine_d에서 e*phi가 8byte가 될수 있으로 CRYPTO_T는 8byte로 설정해 줘야 합니다.
	// 암호할 msg는 최대 3byte 까지 설정가능하다.
	typedef unsigned __int32 		CRYPTO_T;

	class CCryptoRSA
	{
	public:
		CCryptoRSA();
		virtual ~CCryptoRSA();

		//start~최대n개 : 소수권장범위(0x1000~0xFFFF)
		bool Begin(CRYPTO_T start);

		//p,q : 서로다른 소수 : 소수권장범위(0x1000~0xFFFF)
		//bPrimeCheck : 소수여부 체크(true이며 체크함)
		bool Begin(CRYPTO_T p, CRYPTO_T q, bool bPrimeCheck = true);


		CRYPTO_T Encrypt(CRYPTO_T);
		CRYPTO_T Decrypt(CRYPTO_T);

		void Encrypt(char* in, int insize, char* out, int& outsize);
		void Decrypt(char* in, int insize, char* out, int& outsize);

		CRYPTO_T get_n() { return n; }	//public key
		CRYPTO_T get_e() { return e; }	//public key
		CRYPTO_T get_d() { return d; }	//** private key **

		//DEBUG
		void set_n(CRYPTO_T a) { n = a; }
		void set_e(CRYPTO_T a) { e = a; }
		void set_d(CRYPTO_T a) { d = a; }

	protected:

		//소수여부 체크
		bool isPrime(CRYPTO_T pr);

		/* Standard C Function: Greatest Common Divisor */
		CRYPTO_T gcd(CRYPTO_T a, CRYPTO_T b);
		/* Recursive Standard C Function: Greatest Common Divisor */
		CRYPTO_T gcdr(CRYPTO_T a, CRYPTO_T b);

		//pow(b,e) % m ==> (b^e % m)
		CRYPTO_T mod_pow(CRYPTO_T base, CRYPTO_T exp, CRYPTO_T MOD);


	private:

		CRYPTO_T find_e(CRYPTO_T phi);
		CRYPTO_T find_d(CRYPTO_T phi);


	private:
		CRYPTO_T n;//public key
		CRYPTO_T e;//public key
		CRYPTO_T d;//** private key **
	};

};//..namespace HisUtil {