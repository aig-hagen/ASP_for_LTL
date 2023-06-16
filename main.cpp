#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cctype>

#include "src/InconsistencyMeasureASP.h"
#include "src/LTLConformanceChecking.h"
#include "LTLSatisfiabilityCheck.h"
#include "src/Parser.h"
#include "src/Utils.h"

// Authors: Anna Gessler, Isabelle Kuhlmann 

static void PrintCmdHelp()
{
    std::cerr << "Call ltl_app with the following arguments for conformance checking: ./ltl_app cc <kb_file> <trace_file> <variant>" << std::endl
              << "Call ltl_app with the following arguments for model checking: ./ltl_app mc <kb_file> <model_file>" << std::endl
              << "Call ltl_app with the following arguments for satisfiability checking (in declarative process specifications): ./ltl_app sat <kb_file> <m>" << std::endl
              << "\t for the general LTL_ff version, use 'sat-ltlff' instead of 'sat'" << std::endl
              << "Call ltl_app with the following arguments for inconsistency measurement: ./ltl_app im <kb_file> <measure> <m>" << std::endl
              << "'kb_file' is a path to a knowledge base file" << std::endl
              << "'trace_file' is a path to a file containing traces corresponding to the given knowledge base" << std::endl
              << "'model_file' is a path to a file containing an interpretation w.r.t. the given knowledge base" << std::endl
              << "'m' is the number of the final state" << std::endl
              << "possible 'variant' options: ac, sc, sc-es" << std::endl
              << "possible 'measure' options: contension-ltl, drastic-ltl" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        PrintCmdHelp();
        return -1;
    }
    std::string task = argv[1];
    std::transform(task.begin(), task.end(), task.begin(), ::tolower);
    std::set<std::string> tasks = {"im", "cc", "mc", "sat", "sat-ltlff"};
    if (tasks.find(task) == tasks.end())
    {
        std::cerr << "Error: " << task << " is not a valid mode" << std::endl;
        return -1;
    }

    if (task == "im"){
        if (argc != 5)
        {
            PrintCmdHelp();
            return -1;
        }

        std::string measure = argv[3];
        std::transform(measure.begin(), measure.end(), measure.begin(), ::tolower);
        std::set<std::string> measures = {"contension-ltl", "drastic-ltl"};
        if (measures.find(measure) == measures.end())
        {
            std::cerr << "Error: " << measure << " is not a valid inconsistency measure" << std::endl;
            return -1;
        }

        std::string m_str = argv[4];
        if (!is_number(m_str))
        {
            std::cerr << "Error: " << m_str << " is not a digit" << std::endl;
            return -1;
        }

        std::string file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(file);

        ImSettings config;
        config.measure_name = measure;

        double result {};

        int m = stoi(m_str);
        config.m = m;

        result = get_inconsistency_value(k, config);

        std::string result_string = std::to_string(result);
        if (result == -1)
        {
            result_string = "INF";
        }

        
        std::cout << result_string << std::endl;
    }

    else if (task == "cc"){

        std::string kb_file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(kb_file);

        std::string trace_file = argv[3];

        std::string variant = argv[4];
        
        if (variant == "ac"){
            conformance_checking_all_constraints(k, trace_file);
        }
        else if (variant == "sc"){
            conformance_checking_single_constraints(k, trace_file);
        }
        else if (variant == "sc-es"){
            conformance_checking_single_constraints_early_stopping(k, trace_file);
        }
        else{
            std::cout << "No valid variant provided. Using default variant 'ac'." << std::endl;
            conformance_checking_all_constraints(k, trace_file);
        }
    }

    else if (task == "mc"){

        std::string kb_file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(kb_file);

        std::string model_file = argv[3];
        
        model_checking(k, model_file);
    }

    else if (task == "sat"){

        std::string kb_file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(kb_file);

        std::string m_str = argv[3];
        if (!is_number(m_str))
        {
            std::cerr << "Error: " << m_str << " is not a digit" << std::endl;
            return -1;
        }
        int m = stoi(m_str);

        check_satisfiability(k, m);
    }

    else if (task == "sat-ltlff"){

        std::string kb_file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(kb_file);

        std::string m_str = argv[3];
        if (!is_number(m_str))
        {
            std::cerr << "Error: " << m_str << " is not a digit" << std::endl;
            return -1;
        }
        int m = stoi(m_str);

        check_satisfiability_LTL(k, m);
    }
    

    return 0;
}
