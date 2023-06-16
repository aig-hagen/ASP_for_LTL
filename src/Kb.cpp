#include "Kb.h"

#include <iostream>

#include "Utils.h"

// Author: Anna Gessler

Kb::Kb(const Kb &a)
{
    auto formulas = a.GetFormulas();
    for (auto i = formulas.begin(); i != formulas.end(); ++i)
    {
        this->formulas_.emplace_back(std::make_unique<Formula>(*i));
    }
}

Kb::Kb(const Formula &f)
{
    this->formulas_.emplace_back(std::make_unique<Formula>(f));
}

Kb::Kb(const std::vector<Formula> &formulas)
{
    for (Formula f : formulas)
    {
        this->formulas_.emplace_back(std::make_unique<Formula>(f));
    }
}

std::vector<Formula> Kb::GetFormulas() const
{
    std::vector<Formula> result;
    for (auto i = this->formulas_.begin(); i != this->formulas_.end(); ++i)
    {
        result.emplace_back(**i);
    }
    return result;
}

std::set<std::string> Kb::GetSignature() const
{
    std::set<std::string> sig;
    for (auto i = this->formulas_.begin(); i != this->formulas_.end(); ++i)
    {
        std::set<std::string> formula_sig = (**i).GetSignature();
        sig.insert(formula_sig.begin(), formula_sig.end());
    }
    return sig;
}

int Kb::GetNumberOfAtomOccurences() const
{
    int o = 0;
    for (auto i = this->formulas_.begin(); i != this->formulas_.end(); ++i)
    {
        o += (**i).GetNumberOfAtomOccurences();
    }
    return o;
}

void Kb::Add(const Formula &f)
{
    this->formulas_.emplace_back(std::make_unique<Formula>(f));
}

void Kb::Add(const Kb &other)
{
    auto formulas = other.GetFormulas();
    for (auto i = formulas.begin(); i != formulas.end(); ++i)
    {
        this->formulas_.emplace_back(std::make_unique<Formula>(*i));
    }
}

std::ostream &operator<<(std::ostream &strm, const Kb &a)
{
    if (a.formulas_.empty())
    {
        return strm << "{}";
    }

    strm << "{";
    for (auto i = a.formulas_.begin(); i != a.formulas_.end(); ++i)
    {
        if ((i != a.formulas_.end()) && (i + 1 == a.formulas_.end()))
        {
            strm << **i;
        }
        else
        {
            strm << (**i) << ",";
        }
    }
    return strm << "}";
}

bool operator==(const Kb &a, const Kb &b)
{
    for (auto i = a.formulas_.begin(); i != a.formulas_.end(); ++i)
    {
        bool found = false;
        for (auto j = b.formulas_.begin(); j != b.formulas_.end(); ++j)
        {
            if ((**i) == (**j))
            {
                found = true;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Kb &a, const Kb &b)
{
    return !(a == b);
}
