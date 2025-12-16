#include "sort.hpp"
#include "output.hpp"
#include <vector>

int main(){
	std::vector<int> a = {10,9,8,7,6,5,4,3,2,1,0};
	srt::sort::shellsort(a);
	srt::arr_output("Вывод", a);
}
