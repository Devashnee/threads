#include<windows.h>
#include<iostream>

using namespace std;

DWORD WINAPI Sum(LPVOID n)
{
	int num = *(DWORD*)n;
	cout << "Sum Thread created. ID is : " << GetCurrentThreadId() << endl;
	int sum = 0;
	for (int i = 0; i <= num; i++)
		sum += i;
	cout << "The sum is : " << sum << endl;
	return 0;
}

DWORD WINAPI Factorial(LPVOID n)
{
	int num = *(DWORD*)n;
	cout << "Factorial Thread created. ID is : " << GetCurrentThreadId() << endl;
	int fct = 1;
	if (num == 0)
		cout << "Factorial is 1." << endl;
	else
	{
		for (int i = num; i > 0; i--)
			fct *= i;
		cout << "Factorial is : " << fct << endl;
	}
	return 0;
}

DWORD WINAPI ParentThread(LPVOID n)
{
	DWORD SumID;
	DWORD FactorialID; 
	
	int num = *(DWORD*)n;

	cout << "Parent Thread created. ID is : " << GetCurrentThreadId() << endl;
	HANDLE SumHandle = CreateThread(NULL, 0, Sum, &num, 0, &SumID);
	HANDLE FactorialHandle = CreateThread(NULL, 0, Factorial, &num, 0, &FactorialID);
	
	if (SumHandle != NULL)
		WaitForSingleObject(SumHandle, 3000);
	if (FactorialHandle != NULL)
		WaitForSingleObject(FactorialHandle, 3000);

	CloseHandle(SumHandle);
	CloseHandle(FactorialHandle);

	return 0;
}

int main()
{
	int number;
	DWORD id;
	cout << "Please enter your desired number : " << endl;
	cin >> number;
	
	HANDLE ParentHandle = CreateThread(NULL, 0, ParentThread, &number, 0, &id);
	
	if (ParentHandle != NULL)
		WaitForSingleObject(ParentHandle, 3000);

	CloseHandle(ParentHandle);


	system("pause");
	return 0;
}