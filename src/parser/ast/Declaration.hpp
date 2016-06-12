// File: Declaration.hpp
#pragma once

#include <memory>

#include "Assign.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class Declaration : public Node
{
  public:
    Declaration(std::unique_ptr<Assign>&& assignment)
        : assignment(std::move(assignment))
    { }

    ValuePtr evaluate(Scope& scope) const override
    {
        ValuePtr result = assignment->evalOnlyValue(scope);
        return scope.addVar(assignment->variable) = std::move(result);
    }

  private:
    const std::unique_ptr<const Assign> assignment;
};

} // namespace ast

} // namespace vfn
