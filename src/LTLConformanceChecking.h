#include <sstream>
#include <set>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Parser.h"
#include "Constants.h"
#include "InconsistencyMeasureASP.h"
#include <clingo.hh>

// Author: Isabelle Kuhlmann

std::string add_conjunction_rules_LTL_2VL();
std::string add_disjunction_rules_LTL_2VL();
std::string add_negation_rules_LTL_2VL();
std::string add_next_rules_2VL();
std::string add_until_rules_2VL();
std::string add_globally_rules_2VL();
std::string add_finally_rules_2VL();
std::string get_base_program_LTL_conformance_checking(Kb& kb);

std::string handle_formulas_in_kb_LTL_trace_intersection(Kb& kb, std::vector<std::string> trace);

bool intersection_is_empty(Formula f, std::vector<std::string> trace);

void conformance_checking_all_constraints(Kb& kb, std::string path_to_traces);
void conformance_checking_single_constraints(Kb& kb, std::string path_to_traces);
void conformance_checking_single_constraints_early_stopping(Kb& kb, std::string path_to_traces);

void model_checking(Kb& kb, std::string path_to_model);

std::vector<std::string> split_by_comma(std::string& input);
std::vector<std::string> get_pair(std::string& input);