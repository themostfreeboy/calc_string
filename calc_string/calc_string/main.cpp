#include "calc.h"
#include <iostream>

using namespace std;

void test()
{
	string str;
	Calc test_calc;
	test_calc.init_rule();
	while (cin >> str)
	{
		test_calc.set_calc_string(str);
		cout << test_calc.calc_process() << endl;
	}
}

int main(int argc, char** argv)
{
	test();
	system("pause");
	return 0;
}
