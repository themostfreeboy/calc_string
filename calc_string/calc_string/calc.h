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
	string name;// ��ʾ��������ַ���
	int priority;// ���ȼ�(����Խ�����ȼ�Խ��)
	bool has_bracket;// �Ƿ�������
	int op_num;// ������������ĸ���(3������������)
	fun_one_num* p_fun_one_num;// һ������������Ӧ�ļ��㺯��
	fun_two_num* p_fun_two_num;// ��������������Ӧ�ļ��㺯��
	fun_unknown_num* p_fun_unknown_num;// ����������������Ӧ�ļ��㺯��
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
	void copy(const Calc& c){};// ��ֹ��������
	void operator=(const Calc& c){};// ��ֹ�ȺŸ�ֵ
};

#endif