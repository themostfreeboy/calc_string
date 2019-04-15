#ifndef __CALC_H__
#define __CALC_H__

#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

typedef double fun_one_num(double x);// 一个操作数所对应的的操作符处理回调函数
typedef double fun_two_num(double x, double y);// 两个操作数所对应的的操作符处理回调函数
typedef double fun_unknown_num(const vector<double>& x);// 不定长操作数所对应的的操作符处理回调函数

struct Rule
{
	string name;// 表示运算符的字符串
	unsigned int priority;// 优先级(数字越大优先级越高)
	bool has_bracket;// 是否含有括号
	unsigned int op_num;// 运算符操作数的个数(3代表不定长函数)
	fun_one_num* p_fun_one_num;// 一个操作符所对应的计算函数
	fun_two_num* p_fun_two_num;// 两个操作符所对应的计算函数
	fun_unknown_num* p_fun_unknown_num;// 不定长操作符所对应的计算函数
};

class Calc
{
public:
	Calc(){};// 构造函数
	~Calc(){};// 析构函数
	void init_rule();// 初始化操作符相关信息
	void set_calc_string(const string& str);// 设置待计算的字符串
	double calc_process() const;// 计算
private:
	vector<Rule> handle_rule;// 操作符相关信息
	map<const string, unsigned int> map_rule;// 对操作符信息的name建立索引，增加查找速度
	vector<const string> calc_string;// 待计算的字符串
	int find_rule_index(const string& str) const;// 通过name在操作符索引map中找到对应的下标值，若没有则返回-1
	unsigned int cal_comma_count(const string& str, unsigned int start, unsigned int end) const;// 通过逗号统一不定长函数的参数个数(支持函数嵌套)
	void do_handle_fun(stack<const string>& s_string, stack<double>& s_num, unsigned int rule_index) const;// 执行操作符对应的回调函数
	void copy(const Calc& c){};// 禁止拷贝构造
	void operator=(const Calc& c){};// 禁止等号赋值
};

#endif