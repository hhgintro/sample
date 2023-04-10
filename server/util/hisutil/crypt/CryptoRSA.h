#pragma once

namespace HisUtil {
	//�� �Ҽ�(p,q)�� 2byte�� �̸� phi,e�� 4byte�̴�
	// fine_d���� e*phi�� 8byte�� �ɼ� ������ CRYPTO_T�� 8byte�� ������ ��� �մϴ�.
	// ��ȣ�� msg�� �ִ� 3byte ���� ���������ϴ�.
	typedef unsigned __int32 		CRYPTO_T;

	class CCryptoRSA
	{
	public:
		CCryptoRSA();
		virtual ~CCryptoRSA();

		//start~�ִ�n�� : �Ҽ��������(0x1000~0xFFFF)
		bool Begin(CRYPTO_T start);

		//p,q : ���δٸ� �Ҽ� : �Ҽ��������(0x1000~0xFFFF)
		//bPrimeCheck : �Ҽ����� üũ(true�̸� üũ��)
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

		//�Ҽ����� üũ
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