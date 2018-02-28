#include <windows.h>

#include "vector3d.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main (int, char**)
{
	Vector3d a(1, 2, 3);
	Vector3d b(4, 5, 6);
	
	LARGE_INTEGER frequency, startCount, endCount;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add1(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add2(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add3(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add4(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add5(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add6(b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add7(a, b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add8(a, b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add9(a, b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	a.Add10(a, b);

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	return CloseProgram();
}