#include <clingo.hh>
#include "Utils.h"
#include "Constants.h"

// Author: Isabelle Kuhlmann

double get_inconsistency_value(Kb& k, ImSettings config);

// int compute_optimum(std::string& program);

int compute_optimum_with_inf(std::string& program);

bool answerSetExists(std::string& program);