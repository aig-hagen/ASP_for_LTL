#include <fstream>
#include <chrono>

#include "LTLConformanceChecking.h"
#include "LTLMeasuresASP.h"
#include "InconsistencyMeasureASP.h"

using namespace constants;

// Author: Isabelle Kuhlmann

std::string add_conjunction_rules_LTL_2VL(){
    std::string conjunction_rules = "";
    conjunction_rules += IS_TRUE + "(Y,S):-" + CONJUNCTION + "(Y)," + IS_STATE + "(S),N{" + IS_TRUE + "(X,S):" + CONJUNCT_OF + "(X,Y)}N," + NUM_CONJUNCTS + "(Y,N).";
    return conjunction_rules;
}

std::string add_disjunction_rules_LTL_2VL(){
    std::string disjunction_rules = "";
    disjunction_rules += IS_TRUE + "(Y,S):-" + DISJUNCTION + "(Y)," + IS_STATE + "(S),1{" + IS_TRUE + "(X,S):" + DISJUNCT_OF + "(X,Y)}." ;
    return disjunction_rules;
}

std::string add_negation_rules_LTL_2VL(){
    std::string negation_rules = "";
    negation_rules += IS_TRUE + "(Y,S):-" + NEGATION + "(X,Y)," + IS_STATE + "(S),not " + IS_TRUE + "(X,S).";
    return negation_rules;
}

std::string add_next_rules_2VL(){
    std::string next_rules = "";
    next_rules += IS_TRUE + "(F,S1):-" + IS_NEXT + "(F,G)," + IS_STATE + "(S1),S2=S1+1,S1<M," + FINAL_STATE + "(M)," + IS_TRUE + "(G,S2).";
    return next_rules;
}

std::string add_until_rules_2VL(){
    std::string until_rules = "";
    until_rules += IS_TRUE + "(F,S1):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
        + IS_TRUE + "(G,S):" + IS_STATE + "(S),S>=S1,S<S2}X,X=S2-S1," + IS_TRUE + "(H,S2).";
    return until_rules;
}

std::string add_globally_rules_2VL(){
    std::string gobally_rules = "";
    gobally_rules += IS_TRUE + "(F,S1):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),X{" + IS_TRUE + "(G,S):" + IS_STATE + "(S),S>S1}X," + FINAL_STATE + "(M),X=M-S1.";
    return gobally_rules;
}

std::string add_finally_rules_2VL(){
    std::string finally_rules = "";
    finally_rules += IS_TRUE + "(F,S1):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1)," + IS_TRUE + "(G,S2)," + IS_STATE + "(S2),S2>S1.";
    return finally_rules;
}

std::string handle_formulas_in_kb_LTL_trace_intersection(Kb& kb, std::vector<std::string> trace){
    std::vector<Formula> formulas = kb.GetFormulas();
    std::string formula_rules = "";
    for (int i = 0; i < formulas.size(); i++){

        std::set<std::string> signature = formulas.at(i).GetSignature();

        std::vector<std::string> intersection;
        std::set_intersection(trace.begin(), trace.end(), signature.begin(), signature.end(), std::back_inserter(intersection));

        if (intersection.size() == 0){
            continue;
        }
        else{
            std::string formula_name = FORMULA_PREFIX + std::to_string(i);
            std::string kb_member_rule = KB_MEMBER + "(" + formula_name + ").";
            formula_rules += kb_member_rule;

            std::string curr_formula_rules = "";
            ltl_to_asp(formulas.at(i), formula_name, curr_formula_rules);
            formula_rules += curr_formula_rules;
        }
    }

    return formula_rules;
}

bool intersection_is_empty(Formula f, std::vector<std::string> trace){
    std::set<std::string> signature = f.GetSignature();

    std::vector<std::string> intersection;
    std::set_intersection(trace.begin(), trace.end(), signature.begin(), signature.end(), std::back_inserter(intersection));
    if (intersection.size() == 0)
        return true;
    else
        return false;
}

std::string get_base_program_LTL_conformance_checking(Kb& kb){

    std::string program = "";

    program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";


    // add integrity constraint:
    program += ":-not " + IS_TRUE + "(X,0)," + KB_MEMBER + "(X)," + IS_STATE + "(0).";

    // add rule for each atom in the signature:
    program += add_atom_rules(kb);

    // add rules for each formula:
    program += handle_formulas_in_kb_LTL(kb);

    // add universal rules for formulas consisting of single atoms:
    program += IS_TRUE + "(F,S):-" + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + IS_TRUE + "(A,S).";

    if(program.find(CONJUNCTION) != std::string::npos)
        program += add_conjunction_rules_LTL_2VL();
    if(program.find(DISJUNCTION) != std::string::npos)
        program += add_disjunction_rules_LTL_2VL();
    if(program.find(NEGATION) != std::string::npos)
        program += add_negation_rules_LTL_2VL();
    if(program.find(IS_NEXT) != std::string::npos)
        program += add_next_rules_2VL();
    if(program.find(IS_UNTIL) != std::string::npos)
        program += add_until_rules_2VL();
    if(program.find(IS_GLOBALLY) != std::string::npos)
        program += add_globally_rules_2VL();
    if(program.find(IS_FINALLY) != std::string::npos)
        program += add_finally_rules_2VL();

    return program;
}


std::vector<std::string> split_by_comma(std::string& input){
    std::stringstream sstr(input);
    std::vector<std::string> result;
    while(sstr.good())
    {
        std::string substr;
        getline(sstr, substr, ',');

        if (std::islower(substr[0])){
            result.push_back(substr);
        }
    }

    return result;
}

std::vector<std::string> get_pair(std::string& input){
    std::stringstream sstr(input);
    std::vector<std::string> result;
    while(sstr.good())
    {
        std::string substr;
        getline(sstr, substr, ',');
        result.push_back(substr);
    }

    return result;
}

// ac:
void conformance_checking_all_constraints(Kb& kb, std::string path_to_traces){

    int count = 0;
    std::ifstream file(path_to_traces);
    auto total_solving_time = 0.0;
    if (file.is_open()) {
        std::string line;
        int count = 1;

        std::map<std::string, bool> cache; 

        while (std::getline(file, line)) {

            // if the trace has been cached:
            if (cache.find(line) != cache.end()){
                if (cache.at(line)){
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "SAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }
                else{
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "UNSAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }

                count++;
                continue;
            }

            // if the trace has not been cached yet
            else {
                cache.insert({line, false});
            }

            std::vector<std::string> curr_trace = split_by_comma(line);

            // get trace length
            int trace_length = curr_trace.size();

            std::string program = "";

            // set number of states:
            program += FINAL_STATE + "(" + std::to_string(trace_length-1) + ").";

            program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

            // add integrity constraint:
            program += ":-not " + IS_TRUE + "(X,0)," + KB_MEMBER + "(X)," + IS_STATE + "(0).";

            // add rule for each atom in the signature:
            program += add_atom_rules(kb);

            // add rules for each formula: ...
            program += handle_formulas_in_kb_LTL_trace_intersection(kb,curr_trace);

            // add universal rules for formulas consisting of single atoms:
            program += IS_TRUE + "(F,S):-" + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + IS_TRUE + "(A,S).";

            if(program.find(CONJUNCTION) != std::string::npos)
                program += add_conjunction_rules_LTL_2VL();
            if(program.find(DISJUNCTION) != std::string::npos)
                program += add_disjunction_rules_LTL_2VL();
            if(program.find(NEGATION) != std::string::npos)
                program += add_negation_rules_LTL_2VL();
            if(program.find(IS_NEXT) != std::string::npos)
                program += add_next_rules_2VL();
            if(program.find(IS_UNTIL) != std::string::npos)
                program += add_until_rules_2VL();
            if(program.find(IS_GLOBALLY) != std::string::npos)
                program += add_globally_rules_2VL();
            if(program.find(IS_FINALLY) != std::string::npos)
                program += add_finally_rules_2VL();

            for (int i = 0; i < curr_trace.size(); i++){
                program += IS_TRUE + "(" + curr_trace.at(i) + "," + std::to_string(i) + ").";
            }

            auto start = std::chrono::high_resolution_clock::now();
            bool is_sat = answerSetExists(program); 
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            total_solving_time += (double)duration.count();       
            
            if (is_sat){
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "SAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                cache.at(line) = true;
            }
            else{
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "UNSAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
            }

            count++;
        }
    file.close();
    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;
    }
}

// sc:
void conformance_checking_single_constraints(Kb& kb, std::string path_to_traces){

    // iterate over traces:
    int count = 0;
    std::ifstream file(path_to_traces);
    if (file.is_open()) {
        std::string line;
        int count = 1;

        std::map<std::string, bool> cache; 

        auto total_solving_time = 0.0;

        while (std::getline(file, line)) {

            // if the trace has been cached:
            if (cache.find(line) != cache.end()){
                if (cache.at(line)){
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "SAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }
                else{
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "UNSAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }

                continue;
            }

            // if the trace has not been cached yet
            else {
                cache.insert({line, false});
            }

            std::vector<std::string> curr_trace = split_by_comma(line);

            // get trace length
            int trace_length = curr_trace.size();

            // initialize program string:
            std::string program = "";

            // set number of states:
            program += FINAL_STATE + "(" + std::to_string(trace_length-1) + ").";

            for (int i = 0; i < curr_trace.size(); i++){
                program += IS_TRUE + "(" + curr_trace.at(i) + "," + std::to_string(i) + ").";
            }

            program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

            // add integrity constraint:
            program += ":-not " + IS_TRUE + "(X,0)," + KB_MEMBER + "(X)," + IS_STATE + "(0).";

            // add universal rules for formulas consisting of single atoms:
            program += IS_TRUE + "(F,S):-" + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + IS_TRUE + "(A,S).";

            bool kb_is_sat = true;

            for (auto f: kb.GetFormulas()){

                if(intersection_is_empty(f, curr_trace)){
                    // current constraint is vacuously true/sat?
                    continue;
                }
                else{
                    // std::cout << "ELSE" << std::endl;
                    std::string curr_program = program;

                    // add rule for each atom in the signature:
                    curr_program += add_atom_rules_formula(f);

                    // add rules for current constraint:
                    curr_program += handle_single_formula_in_kb_LTL(f);

                    if(curr_program.find(CONJUNCTION) != std::string::npos)
                        curr_program += add_conjunction_rules_LTL_2VL();
                    if(curr_program.find(DISJUNCTION) != std::string::npos)
                        curr_program += add_disjunction_rules_LTL_2VL();
                    if(curr_program.find(NEGATION) != std::string::npos)
                        curr_program += add_negation_rules_LTL_2VL();
                    if(curr_program.find(IS_NEXT) != std::string::npos)
                        curr_program += add_next_rules_2VL();
                    if(curr_program.find(IS_UNTIL) != std::string::npos)
                        curr_program += add_until_rules_2VL();
                    if(curr_program.find(IS_GLOBALLY) != std::string::npos)
                        curr_program += add_globally_rules_2VL();
                    if(curr_program.find(IS_FINALLY) != std::string::npos)
                        curr_program += add_finally_rules_2VL();

                    auto start = std::chrono::high_resolution_clock::now();
                    // check if answer set exists:
                    bool curr_constraint_is_sat = answerSetExists(curr_program);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    total_solving_time += (double)duration.count();

                    if(!curr_constraint_is_sat){
                        kb_is_sat = false;
                    }
                }

            }

            if (kb_is_sat){
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "SAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                cache.at(line) = true;
            }
            else{
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "UNSAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
            }

            count++;
        }
    file.close();
    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;
    }
}

// sc-es:
void conformance_checking_single_constraints_early_stopping(Kb& kb, std::string path_to_traces){

    // iterate over traces:
    int count = 0;
    std::ifstream file(path_to_traces);
    if (file.is_open()) {
        std::string line;
        int count = 1;

        std::map<std::string, bool> cache; 

        auto total_solving_time = 0.0;

        while (std::getline(file, line)) {

            // if the trace has been cached:
            if (cache.find(line) != cache.end()){
                if (cache.at(line)){
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "SAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }
                else{
                    std::cout << "---------------------------------------------------" << std::endl;
                    std::cout << "Trace: ";
                    std::cout << line << std::endl;
                    std::cout << "Result: ";
                    std::cout << "UNSAT" << std::endl;
                    std::cout << "---------------------------------------------------" << std::endl;
                }

                continue;
            }

            // if the trace has not been cached yet
            else {
                cache.insert({line, false});
            }

            std::vector<std::string> curr_trace = split_by_comma(line);

            // get trace length
            int trace_length = curr_trace.size();

            // initialize program string:
            std::string program = "";

            // set number of states:
            program += FINAL_STATE + "(" + std::to_string(trace_length-1) + ").";

            for (int i = 0; i < curr_trace.size(); i++){
                program += IS_TRUE + "(" + curr_trace.at(i) + "," + std::to_string(i) + ").";
            }

            program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

            // add integrity constraint:
            program += ":-not " + IS_TRUE + "(X,0)," + KB_MEMBER + "(X)," + IS_STATE + "(0).";

            // add universal rules for formulas consisting of single atoms:
            program += IS_TRUE + "(F,S):-" + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + IS_TRUE + "(A,S).";

            bool kb_is_sat = true;

            for (auto f: kb.GetFormulas()){

                if(intersection_is_empty(f, curr_trace)){
                    // current constraint is vacuously true/sat?
                    continue;
                }
                else{
                    // std::cout << "ELSE" << std::endl;
                    std::string curr_program = program;

                    // add rule for each atom in the signature:
                    curr_program += add_atom_rules_formula(f);

                    // add rules for current constraint:
                    curr_program += handle_single_formula_in_kb_LTL(f);

                    if(curr_program.find(CONJUNCTION) != std::string::npos)
                        curr_program += add_conjunction_rules_LTL_2VL();
                    if(curr_program.find(DISJUNCTION) != std::string::npos)
                        curr_program += add_disjunction_rules_LTL_2VL();
                    if(curr_program.find(NEGATION) != std::string::npos)
                        curr_program += add_negation_rules_LTL_2VL();
                    if(curr_program.find(IS_NEXT) != std::string::npos)
                        curr_program += add_next_rules_2VL();
                    if(curr_program.find(IS_UNTIL) != std::string::npos)
                        curr_program += add_until_rules_2VL();
                    if(curr_program.find(IS_GLOBALLY) != std::string::npos)
                        curr_program += add_globally_rules_2VL();
                    if(curr_program.find(IS_FINALLY) != std::string::npos)
                        curr_program += add_finally_rules_2VL();

                    auto start = std::chrono::high_resolution_clock::now();
                    // check if answer set exists:
                    bool curr_constraint_is_sat = answerSetExists(curr_program);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    total_solving_time += (double)duration.count();

                    if(!curr_constraint_is_sat){
                        kb_is_sat = false;
                        break;
                    }
                }

            }

            if (kb_is_sat){
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "SAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                cache.at(line) = true;
            }
            else{
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Trace: ";
                std::cout << line << std::endl;
                std::cout << "Result: ";
                std::cout << "UNSAT" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
            }

            count++;

        }
    file.close();
    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;
    }
}

// ---------------------------------------------------------------------------
// model checking
void model_checking(Kb& kb, std::string path_to_model){

    // initialize program string:
    std::string program = "";
    
    program += get_base_program_LTL_conformance_checking(kb);

    int max_state = 0;
    std::ifstream file(path_to_model);
    auto total_solving_time = 0.0;
    if (file.is_open()) {
        std::string line;
        int count = 1;

        std::map<std::string, bool> cache; 

        while (std::getline(file, line)) {

            std::vector<std::string> curr_pair = get_pair(line);
            
            std::string curr_atom = curr_pair.at(0);
            int curr_state = stoi(curr_pair.at(1));
            if (curr_state > max_state){
                max_state = curr_state;
            }

            program += IS_TRUE + "(" + curr_atom + "," + std::to_string(curr_state) + ").";
        }
    }
    file.close();

    program += FINAL_STATE + "(" + std::to_string(max_state) + ").";

    auto start = std::chrono::high_resolution_clock::now();
    bool is_sat = answerSetExists(program); 
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    total_solving_time += (double)duration.count();       
    
    if (is_sat){
        std::cout << "SAT" << std::endl;
    }
    else{
        std::cout << "UNSAT" << std::endl;
    }

    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;
}