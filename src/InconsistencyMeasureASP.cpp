#include "InconsistencyMeasureASP.h"
#include "LTLMeasuresASP.h"
#include <iostream>

// Author: Isabelle Kuhlmann

double get_inconsistency_value(Kb& k, ImSettings config)
{

    if (config.measure_name == "contension-ltl")
    {
        return contension_measure_LTL(k,config.m);
    }
    else if (config.measure_name == "drastic-ltl")
    {
        return drastic_measure_LTL(k,config.m);
    }
    else
    {
        throw std::runtime_error("Unknown inconsistency measure");
    }
    return -1;
}

// int compute_optimum(std::string& program){

//     Clingo::Logger logger = [](Clingo::WarningCode, char const *message) {
//             std::cerr << message << std::endl;
//         };
//     Clingo::StringSpan string_span{"--opt-mode=opt"};
//     Clingo::Control control{string_span, logger, 20};
//     const char * program_char_array = program.c_str();

//     control.add("base", {}, program_char_array);
//     control.ground({{"base", {}}});

//     // compute models:
//     Clingo::SolveHandle sh = control.solve();
//     Clingo::Model m = sh.model();

//     // get minimum value:
//     int min_val = m.cost().at(0);
//     while(sh.next()){
//         Clingo::Model next_m = sh.model();
//         if(next_m.cost().at(0) < min_val)
//             min_val = m.cost().at(0);
//     }

//     return min_val;
// }

int compute_optimum_with_inf(std::string& program){
    Clingo::Logger logger = [](Clingo::WarningCode, char const *message) {
            std::cerr << message << std::endl;
        };
    Clingo::StringSpan string_span{"--opt-mode=opt"};
    Clingo::Control control{string_span, logger, 20};
    const char * program_char_array = program.c_str();

    control.add("base", {}, program_char_array);
    control.ground({{"base", {}}});

    // compute models:
    Clingo::SolveHandle sh = control.solve();

    Clingo::SolveResult sr = sh.get();
    if(!sr.is_satisfiable()){
        return -1;
    }
    else{
        Clingo::Model m = sh.model();

        // get minimum value:
        int min_val = m.cost().at(0);
        while(sh.next()){
            Clingo::Model next_m = sh.model();
            if(next_m.cost().at(0) < min_val)
                min_val = m.cost().at(0);
        }

        return min_val;
    }
}

bool answerSetExists(std::string& program){
    Clingo::Logger logger = [](Clingo::WarningCode, char const *message) {
            std::cerr << message << std::endl;
        };
    Clingo::StringSpan string_span{"--opt-mode=opt"};
    Clingo::Control control{string_span, logger, 20};
    const char * program_char_array = program.c_str();

    control.add("base", {}, program_char_array);
    control.ground({{"base", {}}});

    // compute models:
    Clingo::SolveHandle sh = control.solve();
    Clingo::Model m = sh.model();

    if(m){
        // std::cout << m << std::endl;
        return true;
    }
    else{
        return false;
    }
    
}