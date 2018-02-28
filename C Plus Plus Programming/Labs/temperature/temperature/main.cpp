#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	while (true)
	{
		cout << "Please enter Fahrenheit temperature: ";

		int fahrenheit;
		cin >> fahrenheit;

		float celsius = (fahrenheit - 32)  * (5 / static_cast<float>(9));

		cout << "The temperature in Celsius is: " << celsius << endl;
	}

	return 0;
}