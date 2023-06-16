#include "LTLSatisfiabilityCheck.h"

using namespace constants;

// Author: Isabelle Kuhlmann

void check_satisfiability(Kb& kb, int m){

    // initialize program string:
    std::string program = "";

    // guessing part:
    program += "1{" + IN_TRACE + "(A,S):" + ATOM + "(A)}1:-" + IS_STATE + "(S).";
    program += IS_TRUE + "(A,S):-" + IN_TRACE + "(A,S).";
    
    program += get_base_program_LTL_conformance_checking(kb);

    std::vector<Formula> formulas = kb.GetFormulas();
    for (int i = 0; i < formulas.size(); i++){
        std::string formula_name = FORMULA_PREFIX + std::to_string(i);

        for (auto atom: formulas.at(i).GetSignature()){
            std::transform(atom.begin(), atom.end(), atom.begin(),
            [](unsigned char c){ return std::tolower(c); });
            program += ATOM_IN_FORMULA + "(" + atom + "," + formula_name + ").";
        }
    }

    // get size of intersection of constraint signature and trace signature:
    program += INTERSECTION_SIZE + "(F,X):-#count{A:" + ATOM_IN_FORMULA + "(A,F)," + IN_TRACE + "(A,_)}=X," + KB_MEMBER + "(F).";

    // check if kbElement is vacuously true:
    program += IS_TRUE + "(F,0):-" + KB_MEMBER + "(F)," + INTERSECTION_SIZE + "(F,0).";

    // set number of states:
    program += FINAL_STATE + "(" + std::to_string(m) + ").";

    auto start = std::chrono::high_resolution_clock::now();
    bool is_sat = answerSetExists(program);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double total_solving_time = (double)duration.count();

    if (is_sat){
        std::cout << "SAT" << std::endl;
    }
    else{
        std::cout << "UNSAT" << std::endl;
    }

    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;

}

void check_satisfiability_LTL(Kb& kb, int m){

    // initialize program string:
    std::string program = "";

    // guessing part:
    program += "{" + IS_TRUE + "(A,S):" + ATOM + "(A)}:-" + IS_STATE + "(S).";
    
    program += get_base_program_LTL_conformance_checking(kb);

    // set number of states:
    program += FINAL_STATE + "(" + std::to_string(m) + ").";

    auto start = std::chrono::high_resolution_clock::now();
    bool is_sat = answerSetExists(program);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double total_solving_time = (double)duration.count();

    if (is_sat){
        std::cout << "SAT" << std::endl;
    }
    else{
        std::cout << "UNSAT" << std::endl;
    }

    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;

}