#include "vector.hpp"

#include <iostream>

using bvs::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 1;

template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = 1;
	arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (size_t i = 0; i < size; i++){
		if (arr[i] == value) return true;
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size) return false;

	if (size == capacity){
		capacity *= 2;
		T* arr_new = new T[capacity];
		for(size_t i = 0; i < size; i++){
			arr_new[i] = arr[i];
		}
		delete[] arr;
		arr = arr_new;
	}

	for(size_t i = size; i > position; i--){
		arr[i] = arr[i-1];
	}
	arr[position] = value;
	size++;
	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for(size_t i = 0; i < size; i++){
		std::cout << arr[i];
	}
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (size == capacity){
		capacity *= 2;
		T* arr_new = new T[capacity];
		for(size_t i = 0; i < size; i++){
			arr_new[i] = arr[i];
		}
		delete[] arr;
		arr = arr_new;
	}
	arr[size] = value;
	size++;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {

	for (size_t i = 0; i < size; i++){
		if (arr[i] == value){
			for(size_t j = i+1; j < size; j++){
				arr[j-1] = arr[j];
			}
			size--;
			return true;
		}
	}
	return false;
}