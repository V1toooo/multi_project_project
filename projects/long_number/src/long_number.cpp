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

LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.sign == 0) return LongNumber("0");
    if (this->sign == 0) return LongNumber("0");

    int len_a = this->length;
    int len_b = x.length;
    int* a = new int[len_a];
    int* b = new int[len_b];
    int sign_a = this->sign;
    int sign_b = x.sign;

    for (int i = 0; i < len_a; i++) a[i] = this->numbers[i];
    for (int i = 0; i < len_b; i++) b[i] = x.numbers[i];

    if (len_a < len_b) return LongNumber("0");
    if (len_a == len_b) {
        bool a_less = false;
        for (int i = 0; i < len_a; i++) {
            if (a[i] < b[i]) { a_less = true; break; }
            if (a[i] > b[i]) break;
        }
        if (a_less) return LongNumber("0");
    }

    reverse(a, a + len_a);
    reverse(b, b + len_b);

    string result = "";
    int* remainder = new int[len_a + len_b]();
    int remainder_len = 0;

    for (int i = len_a - 1; i >= 0; i--) {
        for (int j = remainder_len; j > 0; j--) {
            remainder[j] = remainder[j-1];
        }
        remainder[0] = a[i];
        remainder_len++;

        int digit = 0;
        for (int d = 9; d >= 0; d--) {
            int* product = new int[len_b + 1];
            int prod_len = 0;
            int carry = 0;
            for (int j = 0; j < len_b; j++) {
                int mult = b[j] * d + carry;
                product[prod_len++] = mult % 10;
                carry = mult / 10;
            }
            if (carry) product[prod_len++] = carry;

            bool product_less_or_equal = false;
            if (prod_len < remainder_len) {
                product_less_or_equal = true;
            } else if (prod_len == remainder_len) {

                int cmp = 0;
                for (int j = prod_len - 1; j >= 0; j--) {
                    if (product[j] > remainder[j]) { cmp = 1; break; }
                    if (product[j] < remainder[j]) { cmp = -1; break; }
                }
                product_less_or_equal = (cmp <= 0);
            } else {
                product_less_or_equal = false;
            }

            if (product_less_or_equal) {
                digit = d;
                int borrow = 0;
                for (int j = 0; j < prod_len; j++) {
                    int sub = product[j] + borrow;
                    if (remainder[j] < sub) {
                        remainder[j] = remainder[j] + 10 - sub;
                        borrow = 1;
                    } else {
                        remainder[j] -= sub;
                        borrow = 0;
                    }
                }
                for (int j = prod_len; j < remainder_len && borrow; j++) {
                    if (remainder[j] < borrow) {
                        remainder[j] = remainder[j] + 10 - borrow;
                        borrow = 1;
                    } else {
                        remainder[j] -= borrow;
                        borrow = 0;
                    }
                }

                while (remainder_len > 1 && remainder[remainder_len - 1] == 0) {
                    remainder_len--;
                }
                delete[] product;
                break;
            }
            delete[] product;
        }
        result += to_string(digit);
    }

    while (result.length() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    delete[] a;
    delete[] b;
    delete[] remainder;

    if (result == "0") return LongNumber("0");
    if (sign_a != sign_b) result = "-" + result;
    return LongNumber(result.c_str());
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    if (x.compare(LongNumber("0")) == 0) return LongNumber("0");
    
    LongNumber a = *this;
    LongNumber b = x;
    int original_sign = a.sign;
    
    a.sign = 1;
    b.sign = 1;
    
    if (a.compare(b) == -1) {
        LongNumber res = *this; 
        res.sign = original_sign;
        return res;
    }
    
    if (a.compare(b) == 0) return LongNumber("0");
    
    LongNumber quotient = a / b;
    LongNumber product = quotient * b;
    LongNumber remainder = a - product;
    
    remainder.sign = original_sign;
    
    if (remainder.compare(LongNumber("0")) == 0) {
        remainder.sign = 1;
    }

    while (remainder.length > 1 && remainder.numbers[remainder.length - 1] == 0) {
        remainder.length--;
    }

    return remainder;
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