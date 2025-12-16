#include "menu_functions.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

const MenuItem* exit_func(const MenuItem* current){
    exit(0);
    return nullptr;
}

const MenuItem* show_menu(const MenuItem* current){
    cout << "Приветствую тебя, мой юный ученик!" << endl;
    for (int i = 1; i < current->children_count; i++){
        cout << current->children[i]->title << endl;
    }
    cout << current->children[0]->title << endl;
    cout << "Обучайка > ";

    int user_input;
    cin >> user_input;
    cout << endl;

    return current->children[user_input];
}

const MenuItem* algebra_summ_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* algebra_substract_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* algebra_multiply_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* algebra_divide_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* algebra_go_back_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent->parent->parent;
};


const MenuItem* analysis_dif_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* analysis_int_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent;
};
const MenuItem* analysis_go_back_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent->parent->parent;
};


const MenuItem* study_go_back_func(const MenuItem* current){
    cout << current->title << endl;
    return current->parent->parent;
};
