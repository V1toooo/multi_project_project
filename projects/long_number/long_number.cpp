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
	int start = 0;

	if(str[0] == '-'){
		sign = -1;
		start = 1;
	} else {
		sign = 1;
		if (str[0] == '+'){
			start = 1;
		} else {
			start = 0;
		}
	}

	length = strlen(str) - start;

	bool all_zeros = 1;
	for(int i = 0; i < length; i++){
		if (str[start + i] != '0'){
			all_zeros = 0;
			break;
		}
	}
	if (all_zeros == 1){
		sign = 0;
		if(length > 1){
			length = 1;
		}
	}
	numbers = new int[length];
	for(int i = 0; i < length; i++){
		numbers[i] = str[start + i] - '0';
	}
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
	delete[] numbers;

	int start = 0;

	if(str[0] == '-'){
		sign = -1;
		start = 1;
	} else {
		sign = 1;
		if (str[0] == '+'){
			start = 1;
		} else {
			start = 0;
		}
	}

	length = strlen(str) - start;

	bool all_zeros = 1;
	for(int i = 0; i < length; i++){
		if (str[start + i] != '0'){
			all_zeros = 0;
			break;
		}
	}
	if (all_zeros == 1){
		sign = 0;
		if(length > 1){
			length = 1;
		}
	}
	numbers = new int[length];
	for(int i = 0; i < length; i++){
		numbers[i] = str[start + i] - '0';
	}

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
	reverse(a, a + len_a);
	reverse(b, b + len_b);

	if(sign_a != sign_b && len_a == len_b){ //same modulus and different sign
		bool equal = 1;
		for(int i = 0; i < this->length; i++){
			if(a[i] != b[i]){
				equal = 0;
				break;
			}
		}
		if(equal == 1){
			delete[] a;
			delete[] b;
			return LongNumber("0");
		}
	}

    if ((sign_a == 1 && sign_b == 1) || (sign_a == -1 && sign_b == -1)) { //same sign
        if (len_a < len_b){ //a - more len than b
            swap(a, b);
			swap(len_a, len_b);
			swap(sign_a, sign_b);
        }

        int result_len = len_a + 1; // 1 digit more for possible transfer
		int* result = new int[result_len];
		
		for (int i = 0; i < len_a; i++) {
    		result[i] = a[i];
		}
		result[len_a] = 0;
		int result_sign = sign_a;

        for (int i = 0; i < len_b; i++){
            result[i + 1] += (result[i] + b[i]) / 10;
            result[i] = (result[i] + b[i]) % 10;
        }

        for (int i = 0; i < result_len - 1; i++){
            result[i + 1] += (result[i]) / 10;
            result[i] = (result[i]) % 10;
        }

        while (result_len > 1 && result[result_len - 1] == 0) {
            result_len--;
        }

        string result_str;
        for (int i = result_len - 1; i >= 0; i--) {
            result_str += to_string(result[i]);
        }

        delete[] a;
        delete[] b;
        delete[] result;

        if (result_str == "0") return LongNumber("0");
        if (result_sign == -1) result_str = "-" + result_str;
        return LongNumber(result_str.c_str());
    }
        
    if ((sign_a == -1 && sign_b == 1) || (sign_a == 1 && sign_b == -1)) {
		if (len_a < len_b){ //a should be more than b
            swap(a, b);
			swap(len_a, len_b);
			swap(sign_a, sign_b);
        }
		else if(len_a == len_b){
			bool a_less = 0;
			for(int i = len_a - 1; i >= 0; i--){
				if(a[i] < b[i]){
					a_less = 1;
					break;
				}
				if(a[i] > b[i]){
					a_less = 0;
					break;
				}
			}
			if(a_less == 1){
				swap(a, b);
				swap(len_a, len_b);
				swap(sign_a, sign_b);
			}
		}
	

		for (int i = 0; i < len_b; i++) {
        	if (a[i] < b[i]) {
            	for (int count_before_1 = i + 1; count_before_1 < len_a; count_before_1++) {
                	if (a[count_before_1] > 0) {
                    	a[count_before_1] -= 1;
                    	a[i] = ((a[i] + 10) - b[i]);
                    	for (int back = count_before_1 - 1; back > i; back -= 1) {
                        	a[back] = 9;
                    	}
                    	break;
                	}
            	}
        	}
        	else if ((a[i] > b[i]) || (a[i] == b[i])) {
            	a[i] = a[i] - b[i];
        	}
    	}
    	string result_str;
		while (len_a > 1 && a[len_a - 1] == 0) {
        	len_a--;
    	}
        for (int i = len_a - 1; i >= 0; i--) {
            result_str += to_string(a[i]);
        }

        delete[] a;
        delete[] b;

        if (result_str == "0") return LongNumber("0");
        if (sign_a == -1) result_str = "-" + result_str;
        return LongNumber(result_str.c_str());
	}
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	if (this->sign == 0){
		LongNumber x_copy = x;
		x_copy.sign = -x.sign;
		return x_copy;
	} 
	if (x.sign == 0) return *this;

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
	reverse(a, a + len_a);
	reverse(b, b + len_b);

	if(sign_a == sign_b && len_a == len_b){ //same modulus and same sign
		bool equal = 1;
		for(int i = 0; i < this->length; i++){
			if(a[i] != b[i]){
				equal = 0;
				break;
			}
		}
		if(equal == 1){
			delete[] a;
			delete[] b;
			return LongNumber("0");
		}
	}

    if ((sign_a == 1 && sign_b == -1) || (sign_a == -1 && sign_b == 1)) { //different sign
        if (len_a < len_b){ //a - more len than b
            swap(a, b);
			swap(len_a, len_b);
			swap(sign_a, sign_b);
        }

        int result_len = len_a + 1; // 1 digit more for possible transfer
		int* result = new int[result_len];
		
		for (int i = 0; i < len_a; i++) {
    		result[i] = a[i];
		}
		result[len_a] = 0;
		int result_sign = sign_a;

        for (int i = 0; i < len_b; i++){
            result[i + 1] += (result[i] + b[i]) / 10;
            result[i] = (result[i] + b[i]) % 10;
        }

        for (int i = 0; i < result_len - 1; i++){
            result[i + 1] += (result[i]) / 10;
            result[i] = (result[i]) % 10;
        }

        while (result_len > 1 && result[result_len - 1] == 0) {
            result_len--;
        }

        string result_str;
        for (int i = result_len - 1; i >= 0; i--) {
            result_str += to_string(result[i]);
        }

        delete[] a;
        delete[] b;
        delete[] result;

        if (result_str == "0") return LongNumber("0");
        if (result_sign == -1) result_str = "-" + result_str;
        return LongNumber(result_str.c_str());
    }
        
    if ((sign_a == 1 && sign_b == 1) || (sign_a == -1 && sign_b == -1)) {
		bool a_bigger = 1;
    	bool need_minus = 0;
    
    	if (len_a < len_b) a_bigger = 0;
    	else if (len_a > len_b) a_bigger = 1;
    	else {
        	for (int i = len_a - 1; i >= 0; i--) {
            	if (a[i] > b[i]) break;
            	if (a[i] < b[i]) {
            		a_bigger = 0;
                	break;
            	}
        	}
    	}
		
		
		if (a_bigger == 0){ //a should be more than b
            swap(a, b);
			swap(len_a, len_b);
			swap(sign_a, sign_b);
        }


		if (sign_a == 1) {
        need_minus = !a_bigger;
    	} else {
        	need_minus = a_bigger;
    	}
	

		for (int i = 0; i < len_b; i++) {
        	if (a[i] < b[i]) {
            	for (int count_before_1 = i + 1; count_before_1 < len_a; count_before_1++) {
                	if (a[count_before_1] > 0) {
                    	a[count_before_1] -= 1;
                    	a[i] = ((a[i] + 10) - b[i]);
                    	for (int back = count_before_1 - 1; back > i; back -= 1) {
                        	a[back] = 9;
                    	}
                    	break;
                	}
            	}
        	}
        	else if ((a[i] > b[i]) || (a[i] == b[i])) {
            	a[i] = a[i] - b[i];
        	}
    	}
    	string result_str;
		while (len_a > 1 && a[len_a - 1] == 0) {
        	len_a--;
    	}
        for (int i = len_a - 1; i >= 0; i--) {
            result_str += to_string(a[i]);
        }

        delete[] a;
        delete[] b;

        if (result_str == "0") return LongNumber("0");
        if (need_minus) result_str = "-" + result_str;
        return LongNumber(result_str.c_str());
	}
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
	reverse(a, a + len_a);
	reverse(b, b + len_b);

	
	int len_c = len_a + len_b + 1;
	int* c = new int[len_c]();
	int sign_c;
	if(sign_a < sign_b || sign_a > sign_b) sign_c = -1;
	else sign_c = 1;

	if (len_a < len_b){ //a - more len than b
            swap(a, b);
			swap(len_a, len_b);
			swap(sign_a, sign_b);
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
    if (x.sign == 0) return LongNumber("0");

    LongNumber dividend = *this;
    dividend.sign = 1;
    LongNumber divisor = x;
    divisor.sign = 1;

    if (dividend < divisor) return *this;

    LongNumber remainder = dividend;
    LongNumber one("1");
    while (remainder > divisor || remainder == divisor) {
    remainder = remainder - divisor;
	}

    remainder.sign = this->sign;
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
	if(str[0] == '-'){
		start = 1; 
	}

	for(int i = start; str[i] != '\0'; i++){
		result++;
	}

	return result;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace bvs {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
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