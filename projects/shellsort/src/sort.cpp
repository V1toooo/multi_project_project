#include "sort.hpp"
#include <iostream>
#include <vector>
void srt::sort::shellsort(std::vector<int>& a){
	for (int d = a.size() / 2; d > 0; d = d / 2) {
        for (int i = d; i < a.size(); i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= d && a[j - d] > temp; j = j - d) {
                a[j] = a[j - d];
            }
            a[j] = temp;
        }
    }
}