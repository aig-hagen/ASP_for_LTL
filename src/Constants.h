#include <string>

// Author: Isabelle Kuhlmann

#ifndef INCONSISTENCY_MEASURE_ALGORITHMS_constants_h
#define INCONSISTENCY_MEASURE_ALGORITHMS_constants_h
namespace constants {
    static const std::string TRUTH_VALUE_T = "tv_t";
    static const std::string TRUTH_VALUE_B = "tv_b";
    static const std::string TRUTH_VALUE_F = "tv_f";

    static const std::string TRUTH_VALUE_PREDICATE = "truthValue";

    static const std::string ATOM = "atom";
    static const std::string KB_MEMBER = "kbMember";
    static const std::string FORMULA_PREFIX = "phi_";

    static const std::string CONJUNCTION = "conjunction";
    static const std::string CONJUNCT_OF = "conjunctOf";
    static const std::string NUM_CONJUNCTS = "numConjuncts";

    static const std::string DISJUNCTION = "disjunction";
    static const std::string DISJUNCT_OF = "disjunctOf";
    static const std::string NUM_DISJUNCTS = "numDisjuncts";

    static const std::string NEGATION = "negation";

    static const std::string FORMULA_IS_ATOM = "formulaIsAtom";

    static const std::string IS_NEXT = "next";
    static const std::string IS_UNTIL = "until";
    static const std::string IS_GLOBALLY = "globally";
    static const std::string IS_FINALLY = "finally";
    static const std::string IS_STATE = "state";
    static const std::string FINAL_STATE = "finalState";
    static const std::string NUM_B_IN_STATE = "numBInState";
    static const std::string SUM_B = "sumB";
    static const std::string AFFECTED_STATE = "as";

    static const std::string IS_TRUE = "true";
    static const std::string IN_TRACE = "inTrace";
    static const std::string ATOM_IN_FORMULA = "aInF";
    static const std::string INTERSECTION_SIZE = "interSize";
    static const std::string TRACE = "trace";

}
#endif