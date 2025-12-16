#include "menu_items.hpp"
#include "menu_functions.hpp"

const MenuItem ALGEBRA_SUMM = {"1 - Хочу научиться складывать!", algebra_summ_func, &ALGEBRA};
const MenuItem ALGEBRA_SUBSTRACT = {"2 - Хочу научиться вычитать!", algebra_substract_func, &ALGEBRA};
const MenuItem ALGEBRA_MULTIPLY = {"3 - Хочу научиться умножать!", algebra_multiply_func, &ALGEBRA};
const MenuItem ALGEBRA_DIVIDE = {"4 - Хочу научиться делить!", algebra_divide_func, &ALGEBRA};
const MenuItem ALGEBRA_GO_BACK = {"0 - Выйти в главное меню!", algebra_go_back_func, &ALGEBRA};

const MenuItem ANALYSIS_DIF = {"1 - Хочу изучить дифференциальное исчисление!", analysis_dif_func, &ANALYSIS};
const MenuItem ANALYSIS_INT = {"2 - Хочу изучить интегральное исчисление!", analysis_int_func, &ANALYSIS};
const MenuItem ANALYSIS_GO_BACK = {"0 - Выйти в главное меню!", analysis_go_back_func, &ANALYSIS};


namespace{
    const MenuItem* const algebra_children[] = {
        &ALGEBRA_GO_BACK,
        &ALGEBRA_SUMM,
        &ALGEBRA_SUBSTRACT,
        &ALGEBRA_MULTIPLY,
        &ALGEBRA_DIVIDE,
    };
};
const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
const MenuItem ALGEBRA = {"1 - Хочу изучать алгебру!", show_menu, &STUDY, algebra_children, algebra_size}; 


namespace{
    const MenuItem* const analysis_children[] = {
        &ANALYSIS_GO_BACK,
        &ANALYSIS_DIF,
        &ANALYSIS_INT,
    };
};
const int analysis_size = sizeof(analysis_children) / sizeof(analysis_children[0]);
const MenuItem ANALYSIS = {"2 - Хочу изучать математический анализ!", show_menu, &STUDY, analysis_children, analysis_size};

const MenuItem STUDY_GO_BACK = {"0 - Выйти в главное меню!", study_go_back_func, &STUDY};
namespace{
    const MenuItem* const study_children[] = {
        &STUDY_GO_BACK,
        &ALGEBRA, 
        &ANALYSIS, 
    };  
}
const int study_size = sizeof(study_children) / sizeof(study_children[0]);
const MenuItem STUDY = {"1 - Хочу учиться!", show_menu, &MAIN, study_children, study_size};


const MenuItem EXIT = {"0 - Лучше пойду полежу...", exit_func, &MAIN};


namespace{
    const MenuItem* const main_children[] = {&EXIT, &STUDY};
}

const int main_size = sizeof(main_children) / sizeof(main_children[0]);
const MenuItem MAIN = {nullptr, show_menu, nullptr, main_children, main_size};
