#pragma once
class ComplexNumber {
private:
	double re, im;
public:
	double getReal();
	void setReal(double x);
	double getIm();
	void setIm(double x);
	ComplexNumber inverse();
	friend double abs(ComplexNumber c);
	ComplexNumber& operator= ( double b);
	bool operator == (double b) const ;
	bool operator != (double b) const ;
	bool operator == (ComplexNumber a) const;
	bool operator != (ComplexNumber a) const;
	bool operator < (ComplexNumber a) const;
	ComplexNumber operator+ (ComplexNumber a);
	friend ComplexNumber operator- (ComplexNumber a, ComplexNumber b);
	friend ComplexNumber operator- (ComplexNumber a);
	friend ComplexNumber operator~ (ComplexNumber a);
	friend ComplexNumber operator* (ComplexNumber a, ComplexNumber b);
	friend ComplexNumber operator* (ComplexNumber a, double r);
	friend ComplexNumber operator/ (ComplexNumber a, double r);
	friend ComplexNumber operator/ (ComplexNumber a, ComplexNumber b);
	friend std::istream& operator >> (std::istream& is, ComplexNumber &c);
	friend std::ostream& operator << (std::ostream& os, ComplexNumber c);
	ComplexNumber();
	ComplexNumber(double x, double y);
	ComplexNumber(double x);
	ComplexNumber(const ComplexNumber& c);
	~ComplexNumber();
};
