// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

const string operations = "+-*/";
bool letter(char c);
bool number(char c);
bool op(char c);
int operation_priority(const char c);

class myexpression
{
private:
	string exp;
	string removeSpaces(string input);
	

public:
	myexpression() : exp("") {};
	myexpression(const string& exp_) : exp(exp_) {};
	myexpression(const myexpression& other) : exp(other.exp) {};
//	string removeSpaces(string input);

	bool correct() const;

	char operator [](size_t i) const;
	size_t exp_size() const;

	friend istream& operator>>(istream& in, myexpression& exp_);
	friend ostream& operator<<(ostream& out, const myexpression& exp_);
};

class postfix_entry
{
private:
	string pe;

	postfix_entry() = delete;
public:
	postfix_entry(const myexpression& exp_);

	double computation();

	string get_postfix_entry() const;

	friend ostream& operator<<(ostream& out, const postfix_entry& exp_);
};