#ifndef __CALC_H__
#define __CALC_H__

#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

typedef double fun_one_num(double x);// һ������������Ӧ�ĵĲ���������ص�����
typedef double fun_two_num(double x, double y);// ��������������Ӧ�ĵĲ���������ص�����
typedef double fun_unknown_num(const vector<double>& x);// ����������������Ӧ�ĵĲ���������ص�����

struct Rule
{
	string name;// ��ʾ��������ַ���
	unsigned int priority;// ���ȼ�(����Խ�����ȼ�Խ��)
	bool has_bracket;// �Ƿ�������
	unsigned int op_num;// ������������ĸ���(3������������)
	fun_one_num* p_fun_one_num;// һ������������Ӧ�ļ��㺯��
	fun_two_num* p_fun_two_num;// ��������������Ӧ�ļ��㺯��
	fun_unknown_num* p_fun_unknown_num;// ����������������Ӧ�ļ��㺯��
};

class Calc
{
public:
	Calc(){};// ���캯��
	~Calc(){};// ��������
	void init_rule();// ��ʼ�������������Ϣ
	void set_calc_string(const string& str);// ���ô�������ַ���
	double calc_process() const;// ����
private:
	vector<Rule> handle_rule;// �����������Ϣ
	map<const string, unsigned int> map_rule;// �Բ�������Ϣ��name�������������Ӳ����ٶ�
	vector<const string> calc_string;// ��������ַ���
	int find_rule_index(const string& str) const;// ͨ��name�ڲ���������map���ҵ���Ӧ���±�ֵ����û���򷵻�-1
	unsigned int cal_comma_count(const string& str, unsigned int start, unsigned int end) const;// ͨ������ͳһ�����������Ĳ�������(֧�ֺ���Ƕ��)
	void do_handle_fun(stack<const string>& s_string, stack<double>& s_num, unsigned int rule_index) const;// ִ�в�������Ӧ�Ļص�����
	void copy(const Calc& c){};// ��ֹ��������
	void operator=(const Calc& c){};// ��ֹ�ȺŸ�ֵ
};

#endif