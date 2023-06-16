# ASP-Based Framework for Solving Problems Related to Declarative Process Specifications
Framework containing ASP-based implementations for problems related to linear temporal logic (on fixed traces), specifically geared towards declarative process specifications.

## Setup & Notes
* To generate a Makefile using cmake the packages **bison** and **re2c** need
to be installed, otherwise the Clingo library cannot be compiled

## Usage

### Conformance Checking
```
./ltl_app cc <kb_file> <trace_file> <variant>
```
* `<kb_file>`: path to specification
* `<trace_file>`: path to traces
* `<variant>`: select a variant from:
    * `ac` ($\mathrm{ASP_{AC}}$: all constraints are checked within a single solver call) 
    * `sc` ($\mathrm{ASP_{SC}}$: each constraint is checked in an individual solver call)
    * `sc-es` ($\mathrm{ASP_{SC}}$ with early stopping)

Example:
```
./ltl_app cc ../examples/specifications/specification_01.txt ../examples/trace_files/traces_01.txt ac
```

### Model Checking
```
./ltl_app mc <kb_file> <trace_file>
```
* `<kb_file>`: path to specification / knowledge base
* `<model_file>`: path to a file containing an interpretation 

Example:
```
./ltl_app mc ../examples/specifications/specification_01.txt ../examples/model_files/model_01.txt
```

### Satisfiability Checking in Declarative Process Specifications
```
./ltl_app sat <kb_file> <m>
```
* `<kb_file>`: path to specification
* `<m>`: number of final state

Example (with $m$ = 5):
```
./ltl_app sat ../examples/specifications/specification_01.txt 5
```


### Satisfiability Checking in $\mathrm{LTL_{ff}}$
```
./ltl_app sat-ltlff <kb_file> <m>
```
* `<kb_file>`: path to specification / knowledge base
* `<m>`: number of final state

Example (with $m$ = 5):
```
./ltl_app sat-ltlff ../examples/specifications/specification_01.txt 5
```

### Inconsistency Measurement
A definition of the two inconsistency measures can be found [here](https://arxiv.org/pdf/2206.07080.pdf).
```
./ltl_app im <kb_file> <im> <m>
```
* `<kb_file>`: path to specification / knowledge base
* `<im>`: inconsistency measure (`contension-ltl` or `drastic-ltl`)
* `<m>`: number of final state

Example (with $m$ = 5): 
```
./ltl_app im ../examples/specifications/specification_02.txt contension-ltl 5
```

## Input Formats

See the `examples` folder for some example files.

### Specifications
In order to represent $\mathrm{LTL_{ff}}$ formulas we take the format [TweetyProject](http://tweetyproject.org/api/1.23/org/tweetyproject/logics/pl/parser/PlParser.html) uses for propositional logic formulas and extend it as follows:

* "\<X>" denotes the *next* operator
* "\<U>" denotes the *until* operator
* "\<G>" denotes the *globally* operator
* "\<F>" denotes the *eventually* operator

### Traces
A trace file contains a set of traces (like an event log).
Each line in the file represents an individual trace, and the atoms within a trace are separated by commas.

### Models/Interpretations
A model file contains a single interpretation. Each line consists of a pair <atom, state>, separated by a comma. 