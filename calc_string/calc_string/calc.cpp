#include "calc.h"
#include <cmath>
#include <stack>
#include <climits>
#include <assert.h>

double my_add(double x, double y)
{
	return x + y;
}

double my_minus(double x, double y)
{
	return x - y;
}

double my_mul(double x, double y)
{
	return x * y;
}

double my_div(double x, double y)
{
	return x / y;
}

double my_power(double x, double y)
{
	return pow(x, y);
}

double my_log(double x)
{
	return log(x);
}

double my_sin(double x)
{
	return sin(x);
}

double my_cos(double x)
{
	return cos(x);
}

double my_tan(double x)
{
	return tan(x);
}

double my_max(vector<double> x)
{
	double max = -FLT_MAX;
	for (vector<double>::iterator it = x.begin(); it != x.end(); ++it)
	{
		if (*it > max)
		{
			max = *it;
		}
	}
	return max;
}

double my_min(vector<double> x)
{
	double min = FLT_MAX;
	for (vector<double>::iterator it = x.begin(); it != x.end(); ++it)
	{
		if (*it < min)
		{
			min = *it;
		}
	}
	return min;
}

double my_sum(vector<double> x)
{
	double sum = 0;
	for (vector<double>::iterator it = x.begin(); it != x.end(); ++it)
	{
		sum += *it;
	}
	return sum;
}

double my_avg(vector<double> x)
{
	double sum = 0;
	for (vector<double>::iterator it = x.begin(); it != x.end(); ++it)
	{
		sum += *it;
	}
	return sum / x.size();
}

const static Rule rule_data[] = 
{
	{"+", 1, false, 2, NULL, my_add, NULL},
	{"-", 1, false, 2, NULL, my_minus, NULL},
	{"*", 2, false, 2, NULL, my_mul, NULL},
	{"/", 2, false, 2, NULL, my_div, NULL},
	{"^", 3, false, 2, NULL, my_power, NULL},
	{"log(", 4, true, 1, my_log, NULL, NULL},
	{"sin(", 4, true, 1, my_sin, NULL, NULL},
	{"cos(", 4, true, 1, my_cos, NULL, NULL},
	{"tan(", 4, true, 1, my_tan, NULL, NULL},
	{"max(", 4, true, 3, NULL, NULL, my_max},
	{"min(", 4, true, 3, NULL, NULL, my_min},
	{"sum(", 4, true, 3, NULL, NULL, my_sum},
	{"avg(", 4, true, 3, NULL, NULL, my_avg}
};

void Calc::init_rule()
{
	handle_rule.assign(rule_data, rule_data + sizeof(rule_data)/sizeof(Rule));
	for (int i=0; i<handle_rule.size(); ++i)
	{
		map_rule.insert(pair<const string, int>(handle_rule[i].name, i));
	}
}

int Calc::find_rule_index(const string& str) const
{
	map<const string, int>::const_iterator it = map_rule.find(str);
	if (it == map_rule.end())
	{
		return -1;
	}
	else
	{
		return it->second;
	}
}

int Calc::cal_comma_count(const string& str, int start, int end) const
{
	int count = 1;
	int num = 1;
	for (int i=start; i<=end; ++i)
	{
		if (str[i] == '(')
		{
			++num;
		}
		else if (str[i] == ')')
		{
			--num;
			if (num == 0)
			{
				return count;
			}
		}
		else if (str[i] == ',')
		{
			if (num == 1)
			{
				++count;
			}
		}
	}
}

void Calc::set_calc_string(const string& str)
{
	calc_string.clear();
	double temp_num = 0;
	bool has_point = false;
	bool has_num_to_push = false;
	double point_rate = 0.1;
	string temp_str = "";
	char num_str[1024];
	char temp_char;
	int temp_index;
	int count = 0;
	for (int i=0; i<str.length(); ++i)
	{
		if (str[i] == ' ')// 忽略所有空格
		{
			continue;
		}
		else if (str[i] >= '0' && str[i] <= '9')// 0-9
		{
			has_num_to_push = true;
			if (!has_point)
			{
				temp_num = temp_num * 10 + (str[i] - '0');
			}
			else
			{
				temp_num = temp_num + (str[i] - '0') * point_rate;
				point_rate /= 10;
			}
		}
		else if (str[i] == '.')// .
		{
			has_num_to_push = true;
			has_point = true;
			point_rate = 0.1;
		}
		else
		{
			if (has_num_to_push)// 含有待push的值
			{
				sprintf(num_str, "%g", temp_num);
				calc_string.push_back(string(num_str));
				temp_num = 0;
				has_point = false;
				point_rate = 0.1;
				temp_str = "";
				has_num_to_push = false;
			}
			if (str[i] == ',')// 忽略逗号
			{
				continue;
			}
			temp_str += str[i];
			temp_index = find_rule_index(temp_str);
			if (temp_index == -1)
			{
				if (temp_str == "(" || temp_str == ")")// 普通左括号或者右括号
				{
					calc_string.push_back(temp_str);
					temp_num = 0;
					has_point = false;
					point_rate = 0.1;
					temp_str = "";
					has_num_to_push = false;
				}
			}
			else
			{
				calc_string.push_back(temp_str);
				if (handle_rule[temp_index].op_num == 3)// 若操作符参数不定长，再push一个参数的长度
				{
					sprintf(num_str, "%d", cal_comma_count(str, i+1, str.length()-1));
					calc_string.push_back(string(num_str));
				}
				temp_str = "";
			}
		}
	}
	if (has_num_to_push)// 含有待push的值
	{
		sprintf(num_str, "%g", temp_num);
		calc_string.push_back(string(num_str));
	}
}

double Calc::calc_process() const
{
	stack<const string> s_string;// 存储操作符的栈
	stack<double> s_num;// 存储数字的栈
	int temp_index_1, temp_index_2;
	double temp_double_1, temp_double_2;
	string temp_string;
	for (int i=0; i<calc_string.size(); ++i)
	{
		if (calc_string[i] == "(")// 普通(
		{
			s_string.push(calc_string[i]);
		}
		else if (calc_string[i] == ")")// )
		{
			while (true)
			{
				assert(!s_string.empty());
				temp_string = s_string.top();
				if (temp_string == "(")// 普通(
				{
					s_string.pop();
					break;
				}
				else// 非普通(
				{
					temp_index_1 = find_rule_index(temp_string);
					assert(temp_index_1 != -1);
					if (handle_rule[temp_index_1].op_num == 1)// 一个操作数的操作符
					{
						temp_double_1 = s_num.top();
						s_num.pop();
						assert(handle_rule[temp_index_1].p_fun_one_num);
						s_num.push(handle_rule[temp_index_1].p_fun_one_num(temp_double_1));
						s_string.pop();
					}
					else if (handle_rule[temp_index_1].op_num == 2)// 两个操作数的操作符
					{
						temp_double_1 = s_num.top();
						s_num.pop();
						temp_double_2 = s_num.top();
						s_num.pop();
						assert(handle_rule[temp_index_1].p_fun_two_num);
						s_num.push(handle_rule[temp_index_1].p_fun_two_num(temp_double_2, temp_double_1));
						s_string.pop();
					}
					else if (handle_rule[temp_index_1].op_num == 3)// 不定长个操作数的操作符
					{
						assert(handle_rule[temp_index_1].has_bracket);
						int param_num;
						s_string.pop();
						sscanf(s_string.top().c_str(), "%d", &param_num);
						vector<double> temp_double_vector;
						for (int i=0; i<param_num; ++i)
						{
							temp_double_1 = s_num.top();
							s_num.pop();
							temp_double_vector.push_back(temp_double_1);
						}
						assert(handle_rule[temp_index_1].p_fun_unknown_num);
						s_num.push(handle_rule[temp_index_1].p_fun_unknown_num(temp_double_vector));
						s_string.pop();
						break;
					}
					if (handle_rule[temp_index_1].has_bracket)// 该操作符包含括号
					{
						break;
					}
				}
			}
		}
		else// 数字或运算符
		{
			temp_index_1 = find_rule_index(calc_string[i]);
			if (temp_index_1 == -1)// 数字
			{
				sscanf(calc_string[i].c_str(), "%lf", &temp_double_1);
				s_num.push(temp_double_1);
			}
			else// 运算符
			{
				while (!s_string.empty())// 栈非空
				{
					temp_string = s_string.top();
					if (temp_string == "(")// 左括号优先级最低，且不在handle_rule中，直接break即可
					{
						break;
					}
					temp_index_2 = find_rule_index(temp_string);
					if (handle_rule[temp_index_2].priority >= handle_rule[temp_index_1].priority)// 优先级较高或同级
					{
						if (handle_rule[temp_index_2].priority == handle_rule[temp_index_1].priority && handle_rule[temp_index_2].has_bracket)// 如该运算符含有括号，则遇到优先级相等的情况，不弹栈
						{
							break;
						}
						if (handle_rule[temp_index_2].op_num == 1)// 一个操作数的操作符
						{
							temp_double_1 = s_num.top();
							s_num.pop();
							assert(handle_rule[temp_index_2].p_fun_one_num);
							s_num.push(handle_rule[temp_index_2].p_fun_one_num(temp_double_1));
							s_string.pop();
						}
						else if (handle_rule[temp_index_2].op_num == 2)// 两个操作数的操作符
						{
							temp_double_1 = s_num.top();
							s_num.pop();
							temp_double_2 = s_num.top();
							s_num.pop();
							assert(handle_rule[temp_index_2].p_fun_two_num);
							s_num.push(handle_rule[temp_index_2].p_fun_two_num(temp_double_2, temp_double_1));
							s_string.pop();
						}
						else if (handle_rule[temp_index_2].op_num == 3)// 不定长个操作数的操作符
						{
							assert(handle_rule[temp_index_2].has_bracket);
							int param_num;
							s_string.pop();
							sscanf(s_string.top().c_str(), "%d", &param_num);
							vector<double> temp_double_vector;
							for (int i=0; i<param_num; ++i)
							{
								temp_double_1 = s_num.top();
								s_num.pop();
								temp_double_vector.push_back(temp_double_1);
							}
							assert(handle_rule[temp_index_2].p_fun_unknown_num);
							s_num.push(handle_rule[temp_index_2].p_fun_unknown_num(temp_double_vector));
							s_string.pop();
						}
					}
					else// 优先级较低
					{
						break;
					}
				}
				if (handle_rule[temp_index_1].op_num == 3)// 不定长操作数的操作符，放入符号前，先将参数个数压入符号栈
				{
					s_string.push(calc_string[i+1]);
					s_string.push(calc_string[i]);
					++i;
				}
				else
				{
					s_string.push(calc_string[i]);
				}
			}
		}
	}
	while (!s_string.empty())
	{
		temp_string = s_string.top();
		temp_index_1 = find_rule_index(temp_string);
		assert(temp_index_1 != -1);
		if (handle_rule[temp_index_1].op_num == 1)// 一个操作数的操作符
		{
			temp_double_1 = s_num.top();
			s_num.pop();
			assert(handle_rule[temp_index_1].p_fun_one_num);
			s_num.push(handle_rule[temp_index_1].p_fun_one_num(temp_double_1));
			s_string.pop();
		}
		else if (handle_rule[temp_index_1].op_num == 2)// 一个操作数的操作符
		{
			temp_double_1 = s_num.top();
			s_num.pop();
			temp_double_2 = s_num.top();
			s_num.pop();
			assert(handle_rule[temp_index_1].p_fun_two_num);
			s_num.push(handle_rule[temp_index_1].p_fun_two_num(temp_double_2, temp_double_1));
			s_string.pop();
		}
		else if (handle_rule[temp_index_1].op_num == 3)// 不定长个操作数的操作符
		{
			assert(handle_rule[temp_index_1].has_bracket);
			int param_num;
			s_string.pop();
			sscanf(s_string.top().c_str(), "%d", &param_num);
			vector<double> temp_double_vector;
			for (int i=0; i<param_num; ++i)
			{
				temp_double_1 = s_num.top();
				s_num.pop();
				temp_double_vector.push_back(temp_double_1);
			}
			s_num.push(handle_rule[temp_index_1].p_fun_unknown_num(temp_double_vector));
			s_string.pop();
		}
	}
	return s_num.top();
}
