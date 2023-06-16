target_sources(ltl_app
    PRIVATE
    	Formula.cpp
    	Formula.h
    	Kb.cpp
    	Kb.h
    	Parser.cpp
    	Parser.h
      	Utils.cpp
      	Utils.h
		InconsistencyMeasureASP.h
		InconsistencyMeasureASP.cpp
		LTLConformanceChecking.h
		LTLConformanceChecking.cpp 
		LTLSatisfiabilityCheck.h
		LTLSatisfiabilityCheck.cpp
		LTLMeasuresASP.h
		LTLMeasuresASP.cpp
		Constants.h
)

target_include_directories(ltl_app PUBLIC ${CMAKE_CURRENT_LIST_DIR})
