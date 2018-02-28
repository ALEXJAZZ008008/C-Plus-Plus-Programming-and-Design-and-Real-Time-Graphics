#include <iostream>
using namespace std;

class MyException
{

};

void component(int flag)
{
    cout << "Component start" << endl;

	if (flag == 1)
	{
		throw MyException();
	}

    cout << "Component end" << endl;
}

void application(int flag)
{
    cout << "Application try start" << endl;

    component(flag);

    cout << "Application try end" << endl;
}

class OutOfBounds
{
    private:
        int _value;

    public:
		int value() const
		{
			return _value;
		}

        OutOfBounds(int value) : _value(value)
		{

		}
};

class Array
{
    private:
        int _list[10];

    public:
        int &operator[](int i)
		{
			if (i < 0 || i >= 10)
			{
				throw OutOfBounds(i);
			}

            return _list[i];
        }
};

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main(int argc, char* argv[])
{
    Array a;

    try
	{
        a[3] = 30;

        cout << "a[3]= " << a[3] << endl;

        a[100] = 100;

        cout << "a[100]= " << a[100] << endl;
    }
	catch (OutOfBounds exception)
	{
        cout << "Exception: OutOfBounds with value " << exception.value() << endl;
    } 

#if 0
    int flag; cin >> flag;

    try
	{
        cout << "Main try start" << endl;

        application(flag);

        cout << "Main try end" << endl;
    }
	catch (MyException)
	{
        cout << "Caught MyException" << endl;
    }

    cout << "Continue" << endl;
#endif

	return CloseProgram();
}
