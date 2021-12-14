#
<iostream>
#include <Windows.h>
#pragma warning(disable: 4996)

extern "C" {
	void BREAKL() {
		std::cout << std::endl;
	}

	void OutputInt(int a) {
		if (a > 127 || a < -128)
		{
			std::cout << "Int out of range";
			throw;
		}

		std::cout << a;
	}

	void OutputStr(char* ptr) {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		if (ptr == nullptr) {
			std::cout << std::endl;
			return;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
	}

	void OutputIntLn(int a) {
		std::cout << a << std::endl;
	}

	void OutputStrLn(char* ptr) {
		OutputStr(ptr);
		std::cout << std::endl;
	}

	int mpow(int num, int exp) {
		return pow(num, exp);
	}

	int mrand(int min, int max) {
		return rand() % (max - min) + min;
	}
	int sum(int a, int b)
	{
		if ((a + b) > 127 || (a + b) < -128)
		{
			std::cout << "Int out of range";
			throw;
		}
		return a + b;
	}

	int multip(int a, int b)
	{
		if ((a * b) > 127 || (a * b) < -128)
		{
			std::cout << "Int out of range";
			throw;
		}
		return a * b;
	}
}