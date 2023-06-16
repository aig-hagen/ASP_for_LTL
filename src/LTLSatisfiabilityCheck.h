#include <clingo.hh>
#include <chrono>
#include <fstream>

#include "Constants.h"
#include "LTLConformanceChecking.h"
#include "LTLMeasuresASP.h"

// Author: Isabelle Kuhlmann

void check_satisfiability(Kb& kb, int m);
void check_satisfiability_LTL(Kb& kb, int m);