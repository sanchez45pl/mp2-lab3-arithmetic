// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"

bool letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool number(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool op(char c)
{
	if (operations.find(c) != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int operation_priority(const char c)
{
	if (!op(c))
	{
		cout << "Wrong symbol\n";
		return -1;
	}
	if (c == '*' || c == '/')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

char myexpression::operator [](size_t i) const
{
	return exp.at(i);
}

size_t myexpression::exp_size() const
{
	return exp.size();
}

bool myexpression::correct() const
{
	bool correct = true;
	string flag = "sl";
	bool dotflag = true;

	stack <string> s(exp.size());

	if (exp.size() == 0)
	{
		correct = false;
		cout << "Incorrect expression\n";
	}

	for (size_t i = 0; i < exp.size(); i++)
	{
		switch (exp[i])
		{
		case '(':
			if (flag != "op" && flag != "sl")
			{
				correct = false;
				cout << i << " symbol: Incorrect parenthesis\n";
			}
			s.push("sl");
			flag = "sl";
			dotflag = true;
			break;

		case ')':
			if (s.empty() || s.top() != "sl" || flag == "op" || flag == "sl")
			{
				correct = false;
				cout << i << " symbol: Incorrect parenthesis\n";
			}
			else
			{
				s.pop();
			}
			flag = "sr";
			dotflag = true;
			break;

		case '.':
			if (((flag != "n" && (i + 1 == exp.size() || !number(exp[i + 1]))) && flag != "op" && flag != "sl") || flag == "v" || !dotflag)
			{
				correct = false;
				cout << i << " symbol: Incorrect dot\n";
			}
			flag = "d";
			dotflag = false;
			break;

		default:
			if (number(exp[i]) || letter(exp[i]) || op(exp[i]))
			{
				if (number(exp[i]))
				{
					if (flag == "v" || flag == "sr")
					{
						correct = false;
						cout << i << " symbol: Incorrect number\n";
					}
					flag = "n";
				}
				if (letter(exp[i]))
				{
					if (flag == "d" || flag == "sr" || flag == "n")
					{
						correct = false;
						cout << i << " symbol: Incorrect variable\n";
					}
					flag = "v";
					dotflag = true;
				}
				if (op(exp[i]))
				{
					if ((flag == "op" && (exp[i] != '-' || exp[i - 1] == '-')) || (exp[i] != '-' && flag == "sl") || (i + 1 == exp.size() ||
						(!number(exp[i + 1]) && !letter(exp[i + 1]) && exp[i + 1] != '(' && exp[i + 1] != '.' && exp[i + 1] != '-')))
					{
						correct = false;
						cout << i << " symbol: Incorrect operation\n";
					}
					flag = "op";
					dotflag = true;
				}
			}
			else
			{
				flag = "sl";
				dotflag = true;
				correct = false;
				cout << i << " symbol: Incorrect symbol\n";
			}
			break;
		}
	}
	if (!s.empty())
	{
		correct = false;
		cout << "Incorrect parenthesis\n";
	}
	return correct;
}

string myexpression::removeSpaces(string input) 
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	return input;
}

istream& operator>>(istream& in, myexpression& exp_)
{
	in >> exp_.exp;
	return in;
}

ostream& operator<<(ostream& out, const myexpression& exp_)
{
	out << exp_.exp;
	return out;
}

postfix_entry::postfix_entry(const myexpression& exp_)
{
	if (exp_.correct())
	{
		bool flag = true;
		string out;
		stack <char> st(exp_.exp_size());
		for (size_t i = 0; i < exp_.exp_size(); i++)
		{
			if (letter(exp_[i]) || number(exp_[i]) || exp_[i] == '.')
			{
				out.push_back(exp_[i]);
				if (i + 1 == exp_.exp_size() || ((letter(exp_[i]) && !letter(exp_[i + 1])) ||
					(number(exp_[i]) && !number(exp_[i + 1]) && exp_[i + 1] != '.') || (exp_[i] == '.' && !number(exp_[i + 1]))))
				{
					out.push_back(' ');
				}
			}
			if (exp_[i] == '(')
			{
				st.push(exp_[i]);
			}

			if (exp_[i] == '-' && flag)
			{
				st.push('~');
			}

			if (exp_[i] == ')')
			{
				while (st.top() != '(')
				{
					out.push_back(st.pop());
					out.push_back(' ');
				}
				st.pop();
			}
			if (op(exp_[i]) && !(exp_[i] == '-' && flag))
			{
				while (!st.empty() && ((st.top() == '~') ||
					(op(st.top()) && operation_priority(exp_[i]) >= operation_priority(st.top()))))
				{
					out.push_back(st.pop());
					out.push_back(' ');
				}
				st.push(exp_[i]);
			}
			if (exp_[i] == '(' || (op(exp_[i]) && exp_[i] != '-'))
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
		}
		while (!st.empty())
		{
			out.push_back(st.pop());
			out.push_back(' ');
		}
		out.pop_back();
		pe = out;
	}
	else
	{
		cout << "Incorrect expression\n";
	}
}

double postfix_entry::computation()
{
	size_t dotflag = 0;
	bool flagn = false;
	bool flagvar = false;

	stack <double> dst;
	double temp;
	string var;
	vector <string> allvar;
	vector <double> allvardata;
	char check;

	for (size_t i = 0; i < pe.size(); i++)
	{
		if (letter(pe[i]))
		{
			var.push_back(pe[i]);
		}
		if (pe[i] == ' ' || (letter(pe[i]) && i + 1 == pe.size()))
		{
			dotflag = 0;
			flagn = false;
			flagvar = false;
			for (size_t j = 0; j < allvar.size(); j++)
			{
				if (var == allvar[j])
				{
					flagvar = true;
					dst.push(allvardata[j]);
				}
			}
			if (var != "" && !flagvar)
			{
				allvar.push_back(var);
				cout << "Do you want to enter the value of a variable " << var << "?: 1 - Yes, 2 - No\n";
				cin >> check;
				if (check == '1')
				{
					while (!(cin >> temp) || cin.peek() != '\n')
					{
						cin.clear();
						while (cin.get() != '\n');
						{
							cout << "Incorrect input!\n";
						}
					}
					allvardata.push_back(temp);
					dst.push(temp);
				}
				else
				{
					cout << "Variables in expression\n";
					return 0;
				}
			}
			var.clear();
		}
		if (number(pe[i]))
		{
			if (dotflag == 0)
			{
				if (flagn)
				{
					temp = dst.pop() * 10 + double(pe[i]) - 48;
					dst.push(temp);
				}
				else
				{
					dst.push(double(pe[i]) - 48);
				}
				flagn = true;
			}
			else
			{
				temp = dst.pop() + ((double(pe[i]) - 48) / (pow(10, dotflag)));
				dst.push(temp);
				dotflag++;
			}
		}
		if (pe[i] == '.')
		{
			if ((i == 0 || !number(pe[i - 1])))
			{
				dst.push(0.0);
			}
			flagn = false;
			dotflag++;
		}

		switch (pe[i])
		{
		case '~':
			temp = -(dst.pop());
			dst.push(temp);
			break;
		case '+':
			temp = (dst.pop() + dst.pop());
			dst.push(temp);
			break;
		case '-':
			temp = (-dst.pop() + dst.pop());
			dst.push(temp);
			break;
		case '*':
			temp = (dst.pop() * dst.pop());
			dst.push(temp);
			break;
		case '/':
			temp = dst.pop();
			if (temp == 0)
			{
				cout << "Error division by zero\n";
				return 0;
			}
			temp = dst.pop() / temp;
			dst.push(temp);
			break;
		default:
			break;
		}
	}
	return dst.pop();
}

string postfix_entry::get_postfix_entry() const
{
	return pe;
}

ostream& operator<<(ostream& out, const postfix_entry& exp_)
{
	out << exp_.pe;
	return out;
}