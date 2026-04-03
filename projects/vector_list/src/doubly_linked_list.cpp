#include "doubly_linked_list.hpp"

#include <iostream>

using bvs::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = begin;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	size_t count = 0;
	Node* current = begin;
	while(current != nullptr){
		count++;
		current = current->next;
	}
	return count;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;
	while(current != nullptr){
		if(current->value == value){
			return true;
		}
		current = current->next;
	}
	return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* current = begin;
	while(current != nullptr){
		std::cout << current->value << ' ';
		current = current->next;
	}
	std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	 Node* current = new Node(value);
	 if (begin == nullptr){
		end = current;
		begin = current;
	 } else {
		end->next = current;
		current->prev = end;
		end = current;
	 }
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = begin;
	while(current != nullptr){
		if(current->value == value){

			if(current->prev != nullptr){
				current->prev->next = current->next;
			} else {
				begin = current->next;
			}

			if(current->next != nullptr){
				current->next->prev = current->prev;
			} else {
				end = current->prev;
			}

			delete current;
			return true;
		}
		current = current->next;
	}
	return false;
}