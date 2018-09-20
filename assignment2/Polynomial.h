#pragma warning(disable : 4996)

#pragma once
//2.3 The Polynomial ADT
//program 2.8 Adding two polynomials
//program 2.9 Adding a new term
//ADT 2.3 Polynomial
// 다항식의 add, sub, mult, eval 코딩하기

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <exception>

using namespace std;

class Polynomial;

class Term
{
	friend Polynomial;
	Term() {}
	Term(float c, int e):coef(c), exp(e) {}
private:
	float coef;
	int exp;
};

class Polynomial {
public:
	//construct the polynomial p(x) = 0;
	Polynomial();
	

	//return the sum of the polynomials *this and b
	Polynomial Add(Polynomial b);
	
	Polynomial Sub(Polynomial b);

	//return the product of the polynomials *this and b
	Polynomial Multiply(Polynomial b);
	
	//evaluate the polynomial *this at f and return the result
	//float Eval(float f);

	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
private:
	static Term *termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;

	void addTermToArrSortedDeduplicateByExponent(Term * termArr, int &termArrSize, Term & t);

	void NewTerm(const Term & t);
};

Polynomial::Polynomial()
{
	start = -1;
	finish = -1;
	terms = 0;
}

int Polynomial::Display() {
	int aPos = start;
	for (; aPos <= finish; aPos++) {
		cout << termArray[aPos].coef << "x^" << termArray[aPos].exp;
		if ((aPos - finish) != 0)
			cout << " + ";
	}
	cout << "\n";
	return 0;
}

void Polynomial::NewTerm(const Term & t) {
	NewTerm(t.coef, t.exp);
}

//Program 2.9: Adding a new term
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term *temp = new Term[capacity];
		copy(termArray, termArray + free, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}



int Polynomial::GetData() {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree Of Polynomial:";
	cin >> degree;
	start = free;
	for (i = degree; i > 0; i--) {
		cout << "Enter coefficient of x^" << i << ":";
		cin >> coef;
		cout << "Enter exponent of x^" << i << ":";
		cin >> expo;
		NewTerm(coef, expo);
	}
	finish = free - 1;
	terms = finish - start + 1;
	return 0;
}

//program 2.8: Adding two polynomials
//교재 91 페이지 내용과 다른 코드 확인하기
Polynomial Polynomial::Add(Polynomial b)
{
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free;
	while ((aPos <= finish) && (bPos <= b.finish))
		if ((termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp))
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos <= finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1;
	return c;
}


Polynomial Polynomial::Sub(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free;
	while ((aPos <= finish) && (bPos <= b.finish))
		if ((termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = termArray[aPos].coef - b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp))
		{
			c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos <= finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1;
	return c;
}

Polynomial Polynomial::Multiply(Polynomial b) {
	if (terms == 0 || b.terms == 0) throw runtime_error("terms size = 0");

	Polynomial result;
	result.start = free;
	//store multiply result temporarily. 
	Term * tmpArr = new Term[terms*b.terms];
	int arrSize = 0;//the size of the array above.

	for (int i = start; i <= finish; i++) {
		for (int k = b.start; k <= b.finish; k++) {
			float newCoef = termArray[i].coef * b.termArray[k].coef;
			float newExp = termArray[i].exp + b.termArray[k].exp;
			Term t(newCoef, newExp);
			addTermToArrSortedDeduplicateByExponent(tmpArr, arrSize, t);
		}
	}

	for (int i = 0; i < arrSize; i++) {
		result.NewTerm(tmpArr[i]);
	}
	result.finish = free - 1;
	result.terms = result.finish - result.start + 1;

	delete[] tmpArr;
	return result;
}

//the term in termArr is in the descending order by exponent. 
//if tow term have same exponent, combine them. else, insert the new term.
void Polynomial::addTermToArrSortedDeduplicateByExponent(Term * termArr, int & termArrSize, Term & t) {
	if (termArrSize == 0) {
		termArr[termArrSize++] = t;
		return;
	}
	//if the exponent of the last term is equal to t.exp
	if (termArr[termArrSize - 1].exp == t.exp) { 
		termArr[termArrSize - 1].coef += t.coef;
		return;
	}
	//if the exponent of the last term is greater than t.exp
	if (termArr[termArrSize - 1].exp > t.exp) {
		termArr[termArrSize] = t;
		termArrSize++;
		return;
	}

	int i = termArrSize - 1;
	//if true, the input term has the same exponent as the term in the array,
	//don't need to increase "termArrSize", i.e, the size of "termArr". Just combine the two terms.
	bool isExpEqual = false;
	for (; i >= 0; i--) {//search the proper place.(index)
		if (termArr[i].exp == t.exp) {
			isExpEqual = true;
			break;
		}
		if (termArr[i].exp > t.exp) {
			break;
		}
	}
	if (isExpEqual) {
		termArr[i].coef += t.coef;//combine the two terms.
	}
	else {
		int j = termArrSize - 1;
		//move back one step to make room for the input term
		for (; j > i; j--) {
			termArr[j + 1] = termArr[j];
		}
		termArr[j] = t;
		termArrSize++;
	}
}