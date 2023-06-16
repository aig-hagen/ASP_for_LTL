#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

#include "Formula.h"
#include <memory>
#include <set>
#include <vector>

// Author: Anna Gessler

// This class represents a knowledge base.
class Kb
{
  private:
    std::vector<std::unique_ptr<Formula>> formulas_;

  public:
    Kb(){};
    // Copy-Constructor
    Kb(const Kb &a);
    Kb(const Formula &f);
    Kb(const std::vector<Formula> &formulas);

    void Add(const Formula &f);
    void Add(const Kb &other);

    std::vector<Formula> GetFormulas() const;
    inline int size() const
    {
        return this->formulas_.size();
    }

    // Get the set of unique atom names in this knowledge base.
    std::set<std::string> GetSignature() const;

    // Get the number of (non-unique) atom occurences in the knowledge base.
    int GetNumberOfAtomOccurences() const;

    // Overloaded operators
    friend std::ostream &operator<<(std::ostream &strm, const Kb &a);
    friend bool operator==(const Kb &a, const Kb &b);
    friend bool operator!=(const Kb &a, const Kb &b);
};

#endif /* KNOWLEDGEBASE_H */
