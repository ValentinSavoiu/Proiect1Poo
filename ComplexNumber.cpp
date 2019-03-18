#include <cmath>
#include <iostream>
#include "ComplexNumber.h"


ComplexNumber::ComplexNumber() {
	re = 0;
	im = 0;
}

ComplexNumber::ComplexNumber(double x) {
	re = x;
	im = 0;
}

ComplexNumber::ComplexNumber(double x, double y) {
	re = x;
	im = y;
}

ComplexNumber::ComplexNumber(const ComplexNumber& c) {
	re = c.re;
	im = c.im;
}

std::istream& operator >> (std::istream& is, ComplexNumber &c) {
	double x, y;
	is >> x >> y;
	c.setIm(y);
	c.setReal(x);
	return is;
}

std::ostream& operator << (std::ostream& os, ComplexNumber c) {
	if(-1e-13 < c.re && c.re < 1e-13) c.re = 0;
	if(-1e-13 < c.im && c.im < 1e-13) c.im = 0;
	if (c.im != 0 && c.re != 0)
		os << c.re << " + " << c.im << 'i';
	else if (c.im == 0) {
		os << c.re;
	}
	else os << c.im << 'i';
	return os;
}

ComplexNumber operator- (ComplexNumber a) {
	ComplexNumber c;
	c.setReal(-1 * a.getReal());
	c.setIm(-1 * a.getIm());
	return c;
}

ComplexNumber operator~ (ComplexNumber a) {
	ComplexNumber c;
	c.setReal(a.getReal());
	c.setIm(-1 * a.getIm());
	return c;
}


double abs(ComplexNumber c) {
	return sqrt(c.re*c.re + c.im*c.im);
}


ComplexNumber ComplexNumber::inverse() {
	double abso = abs(*this);
	return ~(*this) / abso / abso;
}

ComplexNumber ComplexNumber::operator+ (ComplexNumber a) {
	ComplexNumber c(re + a.re, im + a.im);
	return c;
}

ComplexNumber& ComplexNumber:: operator= ( double b) {
	re = b;
	im = 0;
	return *this;
}

bool ComplexNumber::operator== (double b) const {
	return ((im == 0) && (re == b));
}

bool ComplexNumber::operator!= (double b) const{
	return !((*this) == b);
}


ComplexNumber operator- (ComplexNumber a, ComplexNumber b) {
	ComplexNumber c;
	c = a + -b;
	return c;
}

ComplexNumber operator* (ComplexNumber a, ComplexNumber b) {
	ComplexNumber c;
	c.setReal(a.getReal() * b.getReal() - a.getIm() * b.getIm());
	c.setIm(a.getIm() * b.getReal() + a.getReal() * b.getIm());
	return c;
}

ComplexNumber operator/ (ComplexNumber a, ComplexNumber b) {
	return a * b.inverse();
}

ComplexNumber operator* (ComplexNumber a, double b) {
	ComplexNumber c;
	c.setReal(a.getReal() * b);
	c.setIm(a.getIm() * b);
	return c;
}

ComplexNumber operator/ (ComplexNumber a, double b) {
	if (b == 0) throw("Impartire la zero!");
	ComplexNumber c;
	c.setReal(a.getReal() / b);
	c.setIm(a.getIm() / b);
	return c;
}

bool ComplexNumber :: operator < (ComplexNumber a) const{
	if (a.re != re) return re < a.re;
	return im < a.im;
}

bool ComplexNumber :: operator == (ComplexNumber a) const {
	return (*this - a == 0);
}

bool ComplexNumber :: operator != (ComplexNumber a) const {
	return ! (a == (*this));
}


double ComplexNumber::getIm() {
	return im;
}
double ComplexNumber::getReal() {
	return re;
}
void ComplexNumber::setReal(double x) {
	re = x;
}
void ComplexNumber::setIm(double x) {
	im = x;
}
ComplexNumber::~ComplexNumber() {}