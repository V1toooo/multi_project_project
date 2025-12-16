#pragma once
#include "menu.hpp"

const MenuItem* show_menu (const MenuItem* current);
const MenuItem* exit_func (const MenuItem* current);
const MenuItem* study_go_back_func (const MenuItem* current);

const MenuItem* algebra_summ_func (const MenuItem* current);
const MenuItem* algebra_substract_func (const MenuItem* current);
const MenuItem* algebra_multiply_func (const MenuItem* current);
const MenuItem* algebra_divide_func (const MenuItem* current);
const MenuItem* algebra_go_back_func (const MenuItem* current);

const MenuItem* analysis_dif_func (const MenuItem* current);
const MenuItem* analysis_int_func (const MenuItem* current);
const MenuItem* analysis_go_back_func (const MenuItem* current);