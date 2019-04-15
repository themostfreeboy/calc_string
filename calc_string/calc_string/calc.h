#ifndef __CALC_H__
#define __CALC_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

typedef double fun_one_num(double x);
typedef double fun_two_num(double x, double y);
typedef double fun_unknown_num(const vector<double>& x);

struct Rule
{
	string name;// 表示运算符的字符串
	int priority;// 优先级(数字越大优先级越高)
	bool has_bracket;// 是否含有括号
	int op_num;// 运算符操作数的个数(3代表不定长函数)
	fun_one_num* p_fun_one_num;// 一个操作符所对应的计算函数
	fun_two_num* p_fun_two_num;// 两个操作符所对应的计算函数
	fun_unknown_num* p_fun_unknown_num;// 不定长操作符所对应的计算函数
};

class Calc
{
public:
	Calc(){};
	~Calc(){};
	void init_rule();
	void set_calc_string(const string& str);
	double calc_process() const;
private:
	vector<Rule> handle_rule;
	map<const string, int> map_rule;
	vector<const string> calc_string;
	int find_rule_index(const string& str) const;
	int cal_comma_count(const string& str, int start, int end) const;
	void copy(const Calc& c){};// 禁止拷贝构造
	void operator=(const Calc& c){};// 禁止等号赋值
};

#endif