// реализация пользовательского приложения

#include <iostream>
#include "arithmetic.h"

using namespace std;

int main()
{
	string in;
	myexpression exp;
	size_t globalflag = true;

	while (globalflag)
	{
		cout << "Enter your expression:\n";
		cin >> in;

		bool flag = false;
		while (!flag)
		{
			flag = exp.correct();
			if (!flag)
			{
				cout << "Enter your correct expression:\n";
				cin >> in;
				exp = in;
			}
		}

		char choice;

		postfix_entry pe(exp);
		cout << "Calculate the expression?: 1 - Yes, 2 - No\n";
		cin >> choice;

		while (flag)
		{
			if (choice == '1')
			{
				cout << "Result: " << pe.computation() << '\n';
			}
			else
			{
				flag = false;
				break;
			}
			cout << "Calculate the expression again?: 1 - Yes, 2 - No\n";
			cin >> choice;
		}

		cout << "Do you want to finish?: 1 - Yes, 2 - No\n";
		cin >> choice;
		if (choice == '1')
		{
			globalflag = false;
		}
		cin.clear();
	}
}
