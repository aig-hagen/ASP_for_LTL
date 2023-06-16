#ifndef UTILS_H
#define UTILS_H

#include "Formula.h"
#include "Kb.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

// This structs collects configuration settings
// for a specific GetInconsistencyValue call.
// Author: Anna Gessler
struct ImSettings
{
    std::string measure_name;       // name of the measure
    int m;                          // m
};

bool is_number(const std::string& s);

#endif /* UTILS_H */
