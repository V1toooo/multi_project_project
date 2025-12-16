#include "output.hpp"
#include <iostream>
#include <vector>
#include <string>

void srt::arr_output(const std::string& comment, const std::vector<int>& arr){
	std::cout << comment << ' ';
	for(int i : arr){
		std::cout << i << ' ';
	}
}