#include "long_number.hpp"
#include <cstring>

#include <algorithm>
#include <iostream>
#include <string>

using bvs::LongNumber;
using namespace std;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 0;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) {
	this->length = length;
	this->sign = sign;
	numbers = new int[length];	
	for(int i = 0; i < length; i++){
		this->numbers[i] = 0;
	}
}

LongNumber::LongNumber(const char* const str) {
	numbers = nullptr;
	length = 0;
	sign = 0;
	create_from_str(str);
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];

	for(int i = 0; i < length; i++){
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	create_from_str(str);
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	delete[] numbers;

	length = x.length;
	sign = x.sign;
	numbers = new int[length];

	for(int i = 0; i < length; i++){
		numbers[i] = x.numbers[i];
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if(this == &x) return *this;
	delete[] numbers;

	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;

	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if(this == &x) return 1;
	if(this->sign != x.sign) return 0;
	if(this->length != x.length) return 0;

	bool equal = 1;
	for(int i = 0; i < this->length; i++){
		if(this->numbers[i] != x.numbers[i]){
			equal = 0;
			break;
		}
	}
	return equal;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if(this==&x || this->sign < x.sign) return 0;
	if(this->sign > x.sign) return 1;
	if(this->sign == 0) return 0;

	if(this->sign > 0){
		if(this->length > x.length) return 1;
		if(this->length < x.length) return 0;

		for(int i = 0; i < this->length; i++){
			if(this->numbers[i] < x.numbers[i]) return 0;
			if(this->numbers[i] > x.numbers[i]) return 1;
		}
		return 0;
	}

	if(this->sign < 0){
		if(this->length > x.length) return 0;
		if(this->length < x.length) return 1;

		for(int i = 0; i < this->length; i++){
			if(this->numbers[i] < x.numbers[i]) return 1;
			if(this->numbers[i] > x.numbers[i]) return 0;
		}
		return 0;
	}

	return 0;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return (x > *this);
}
bool LongNumber::operator >= (const LongNumber& x) const 
{
    return (*this > x) || (*this == x);
}

bool LongNumber::operator <= (const LongNumber& x) const 
{
    return (*this < x) || (*this == x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (this->sign == 0) return x;
    if (x.sign == 0) return *this;

    if (this->sign == x.sign) {
        LongNumber result = plus_modules(*this, x);
        if (result.sign != 0) result.sign = this->sign;
        return result;
    }

    int cmp = this->compare(x);
    if (cmp == 0) return LongNumber("0");
    
    LongNumber result = minus_modules(*this, x);
    if (cmp == 1) {
        result.sign = this->sign;
    } else {
        result.sign = x.sign;
    }
    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (this->sign == 0) {
        LongNumber x_copy = x;
        x_copy.sign = -x.sign;
        return x_copy;
    } 
    if (x.sign == 0) return *this;

    if (this->sign == x.sign && this->compare(x) == 0) {
        return LongNumber("0");
    }

    if (this->sign != x.sign) {
        LongNumber result = plus_modules(*this, x);
        result.sign = this->sign;
        return result;
    }

    int cmp = this->compare(x);
    
    LongNumber result = minus_modules(*this, x);
    
    if (this->sign == 1) {
        if (cmp == 1) result.sign = 1;
        else result.sign = -1;
    } else {
        if (cmp == 1) result.sign = -1;
        else result.sign = 1;
    }
    
    return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	if (this->sign == 0 || x.sign == 0) return LongNumber("0");

    int* a = new int[length];
    int* b = new int[x.length];
    
    for (int i = 0; i < length; i++) {
        a[i] = numbers[i];
    }
    for (int i = 0; i < x.length; i++) {
        b[i] = x.numbers[i];
    }

	int len_a = this->length;
	int len_b = x.length;
	int sign_a = this->sign;
	int sign_b = x.sign;
	std::reverse(a, a + len_a);
	std::reverse(b, b + len_b);

	
	int len_c = len_a + len_b + 1;
	int* c = new int[len_c]();
	int sign_c;
	if (sign_a < sign_b || sign_a > sign_b) sign_c = -1;
	else sign_c = 1;

	if (len_a < len_b){ //a - more len than b
            swap(a, b);
			swap(len_a, len_b);
    }

	for (int i = 0; i < len_a; i++){
        for (int j = 0; j < len_b; j++){
            c[i + j] += a[i] * b[j];
        }
    }
    for (int i = 0; i < len_c - 1; i++){
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

	while (len_c > 1 && c[len_c - 1] == 0) {
            len_c--;
    }

    string result_str;
    for (int i = len_c - 1; i >= 0; i--) {
        result_str += to_string(c[i]);
    }

    delete[] a;
    delete[] b;
    delete[] c;

    if (result_str == "0") return LongNumber("0");
    if (sign_c == -1) result_str = "-" + result_str;
    return LongNumber(result_str.c_str());
}

LongNumber LongNumber::operator / (const LongNumber& x) const
{
    if (this->is_zero() || x.is_zero()) {
        return LongNumber();
    }

    LongNumber dividend = *this;
    LongNumber divisor = x;
    dividend.sign = 1;
    divisor.sign = 1;

    if (dividend < divisor) {
        return LongNumber();
    }

    LongNumber quotient(dividend.length, 1);
    LongNumber current("0");

    for (int i = 0; i < dividend.length; i++) {
       current = current * LongNumber("10");
        
        LongNumber digit(1, 1);
        digit.numbers[0] = dividend.numbers[i];
        current = current + digit;

        int quotient_digit = 0;
        for (int q = 0; q <= 9; q++) {
            LongNumber product = divisor * LongNumber(std::to_string(q).c_str());
            if (product <= current) {
                quotient_digit = q;
            } else {
                break;
            }
        }

        quotient.numbers[i] = quotient_digit;

        LongNumber product = divisor * LongNumber(std::to_string(quotient_digit).c_str());
        current = current - product;
    }

    if (this->sign == -1 && x.numbers[0] > 1) {
        quotient.numbers[quotient.length - 1] = quotient.numbers[quotient.length - 1] + 1;
    }

    int begin = 0;
    while (begin < quotient.length - 1 && quotient.numbers[begin] == 0) {
        begin++;
    }

    LongNumber result(quotient.length - begin, this->sign * x.sign);
    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = quotient.numbers[begin + i];
    }

    if (result.length == 1 && result.numbers[0] == 0) {
        result.sign = 1;
    }

    return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const
{
    return *this - (*this / x) * x;
}

bool LongNumber::is_negative() const noexcept {
	return (sign == -1);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int result = 0;
	int start = 0;
	if (str[0] == '-'){
		start = 1; 
	}

	for (int i = start; str[i] != '\0'; i++){
		result++;
	}

	return result;
}

void LongNumber::create_from_str(const char* const str){
    delete[] numbers;
    numbers = nullptr;
    length = 0;
    sign = 0;
    
    int start = 0;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        sign = 1;
        start = 1;
    } else {
        sign = 1;
        start = 0;
    }
    
    length = strlen(str) - start;
    
    bool all_zeros = true;
    for (int i = 0; i < length; ++i) {
        if (str[start + i] != '0') {
            all_zeros = false;
            break;
        }
    }
    
    if (all_zeros) {
        sign = 0;
        length = 1;
    }
    
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        numbers[i] = str[start + i] - '0';
    }
}

int LongNumber::compare(const LongNumber& other) const {
    if (this->length > other.length) return 1;
    if (this->length < other.length) return -1;
    
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] > other.numbers[i]) return 1;
        if (this->numbers[i] < other.numbers[i]) return -1;
    }
    return 0;
}

bool LongNumber::is_zero() const noexcept
{
    return length == 1 && numbers[0] == 0;
}

LongNumber LongNumber::plus_modules(const LongNumber& a, const LongNumber& b) const {

    int len_a = a.length;
    int len_b = b.length;
    int* a_digits = new int[len_a];
    int* b_digits = new int[len_b];
    
    for (int i = 0; i < len_a; i++) a_digits[i] = a.numbers[i];
    for (int i = 0; i < len_b; i++) b_digits[i] = b.numbers[i];

    std::reverse(a_digits, a_digits + len_a);
    std::reverse(b_digits, b_digits + len_b);

    if (len_a < len_b) {
        swap(a_digits, b_digits);
        swap(len_a, len_b);
    }

    int result_len = len_a + 1;
    int* result = new int[result_len]();

    for (int i = 0; i < len_a; i++) {
        result[i] = a_digits[i];
    }

    for (int i = 0; i < len_b; i++) {
        result[i] += b_digits[i];
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    for (int i = 0; i < result_len - 1; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    while (result_len > 1 && result[result_len - 1] == 0) {
        result_len--;
    }

    string result_str;
    for (int i = result_len - 1; i >= 0; i--) {
        result_str += to_string(result[i]);
    }
    
    delete[] a_digits;
    delete[] b_digits;
    delete[] result;
    
    return LongNumber(result_str.c_str());
}

LongNumber LongNumber::minus_modules(const LongNumber& a, const LongNumber& b) const {
    int cmp = a.compare(b);

    if (cmp == 0) return LongNumber("0");

    int len_a = a.length;
    int len_b = b.length;
    int* a_digits = new int[len_a];
    int* b_digits = new int[len_b];
    
    for (int i = 0; i < len_a; i++) a_digits[i] = a.numbers[i];
    for (int i = 0; i < len_b; i++) b_digits[i] = b.numbers[i];

    std::reverse(a_digits, a_digits + len_a);
    std::reverse(b_digits, b_digits + len_b);

    bool a_bigger = (cmp == 1);
    if (!a_bigger) {
        swap(a_digits, b_digits);
        swap(len_a, len_b);
    }

    for (int i = 0; i < len_b; i++) {
        if (a_digits[i] < b_digits[i]) {
            int j = i + 1;
            while (j < len_a && a_digits[j] == 0) j++;
            if (j < len_a) {
                a_digits[j]--;
                for (int k = j - 1; k > i; k--) {
                    a_digits[k] = 9;
                }
                a_digits[i] += 10;
            }
        }
        a_digits[i] -= b_digits[i];
    }

    while (len_a > 1 && a_digits[len_a - 1] == 0) {
        len_a--;
    }
    
    string result_str;
    for (int i = len_a - 1; i >= 0; i--) {
        result_str += to_string(a_digits[i]);
    }
    
    delete[] a_digits;
    delete[] b_digits;
    
    return LongNumber(result_str.c_str());
}
// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace bvs {
	ostream& operator << (std::ostream &os, const LongNumber& x) {
		if(x.sign == 0){
			os << "0";
			return os;
		}
		if(x.sign == -1){
			os << "-";
		}
		for(int i = x.length - 1; i >= 0; i--){
			os << x.numbers[i];
		}
		return os;
	}
}
