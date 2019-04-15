#include "calc.h"
#include <iostream>

using namespace std;

void test_1()
{
	vector<string> test_str;
	test_str.push_back("1.1+2.2*3-4+max(8,min(100,10,300,200),7)");
	test_str.push_back("1.1+(2.2-3.3)*4+sum(1.1,2.2,3.3,avg(1,2,3,4,5))/3");
	test_str.push_back("1+2^3/4+sqrt(9)+pow(3,2)");
	test_str.push_back("(1+2)^2*3/9");
	test_str.push_back("max(min(1,2,3),min(4,5,6,7),min(8,9,10,11,12))");
	Calc test_calc;
	test_calc.init_rule();
	for (vector<string>::iterator it = test_str.begin(); it != test_str.end(); ++it)
	{
		test_calc.set_calc_string(*it);
		cout << *it << " = " << test_calc.calc_process() << endl;
	}
}

void test_2()
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
	test_1();
	test_2();
	system("pause");
	return 0;
}
