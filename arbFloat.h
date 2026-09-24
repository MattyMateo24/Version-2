#ifndef ARBFLOAT_H
#define ARBFLOAT_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>


#define MAX_PREC  60


using namespace std;

class arbFloat {
    public:

    //Constructors
    arbFloat();
    arbFloat(int p);
    arbFloat(int p, int n);
    arbFloat(int p, long int n);
    arbFloat(int p, long long int n);
    arbFloat(int p, float f);
    arbFloat(int p, double d);
    arbFloat(int p, long double d);
    arbFloat(bool ext);
    arbFloat(int p, string s);
    arbFloat(const arbFloat& x);


    //Arithmetic operators
    arbFloat& operator+=(const arbFloat& x);
    friend arbFloat operator+(const arbFloat& x, const arbFloat& y);
    arbFloat& operator-=(const arbFloat x);
    friend arbFloat operator-(const arbFloat& x,  const arbFloat& y);
    arbFloat& operator*=(const arbFloat& x);
    friend arbFloat operator*(const arbFloat& x, const arbFloat& y);
    arbFloat& operator/=(const arbFloat x);
    friend arbFloat operator/(const arbFloat& x, const arbFloat& y);

    friend arbFloat rt2(const arbFloat& x);
    friend arbFloat sqr(const arbFloat& x);
    friend arbFloat pow(const arbFloat& x, int power);

    //Comparison operators
    friend bool operator==(const arbFloat& l, const arbFloat& r);
    friend bool operator!=(const arbFloat& l, const arbFloat& r);
    friend bool operator<(const arbFloat& l, const arbFloat& r);
    friend bool operator>(const arbFloat& l, const arbFloat& r);
    friend bool operator<=(const arbFloat& l, const arbFloat& r);
    friend bool operator>=(const arbFloat& l, const arbFloat& r);

    //Useful Mathematical functions/operators
    static const arbFloat ZERO;
    static const arbFloat ONE;
    static const arbFloat TWO;
    static const arbFloat PI;
    static const arbFloat E;

    //Transcendental functions
    friend arbFloat sin(const arbFloat& x);
    friend arbFloat cos(const arbFloat& x);
    friend arbFloat tan(const arbFloat& x);
    friend arbFloat arcsin(const arbFloat& x);
    friend arbFloat arccos(const arbFloat& x);
    friend arbFloat arctan(const arbFloat& x);
    friend arbFloat exp(const arbFloat& x);
    friend arbFloat ln(const arbFloat& x);
    friend arbFloat mod(const arbFloat& x, const arbFloat& y);

    void round();
    void print_number();
    void truncate();
    void abs_val();
    void negate();
    void print_digits();
    bool is_pos();

    static arbFloat gen_PI(int prec);
    static arbFloat gen_E();

    vector<int> get_digits();
    int get_exp();
    int get_sign();


    friend double arb_to_double(arbFloat num);

    private:

    void initialize();

    int exp;
    vector<int> digits;
    int sign;
};


#endif