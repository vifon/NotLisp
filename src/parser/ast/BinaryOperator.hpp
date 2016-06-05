// File: BinaryOperator.hpp
#pragma once

#include <sstream>

#include "Node.hpp"
#include "NumberValue.hpp"

namespace vfn {

namespace ast {

class BinaryOperator : public Node
{
  public:
    BinaryOperator(Keyword op, NodePtr&& lhs, NodePtr&& rhs)
        : op(op)
        , lhs(std::move(lhs))
        , rhs(std::move(rhs))
    {
        this->lhs->parent = this;
        this->rhs->parent = this;
    }

    ValuePtr evaluate() override
    {
        ValuePtr lhs_val = lhs->evaluate();
        ValuePtr rhs_val = rhs->evaluate();
        ValuePtr result;

        switch (op) {
        case Keyword::Equals:
            result.reset(new NumberValue(*lhs_val == *rhs_val));
            break;
        case Keyword::NotEquals:
            result.reset(new NumberValue(!(*lhs_val == *rhs_val)));
            break;
        case Keyword::Plus:
            result.reset(new NumberValue(lhs_val->asInt() + rhs_val->asInt()));
            break;
        case Keyword::Minus:
            result.reset(new NumberValue(lhs_val->asInt() - rhs_val->asInt()));
            break;
        case Keyword::Mult:
            result.reset(new NumberValue(lhs_val->asInt() * rhs_val->asInt()));
            break;
        case Keyword::Div:
            result.reset(new NumberValue(lhs_val->asInt() / rhs_val->asInt()));
            break;
        default:
            std::stringstream ss{"Invalid operator: "};
            ss << op;
            throw std::runtime_error(ss.str());
        }

        return result;
    }

  private:
    const Keyword op;
    NodePtr lhs;
    NodePtr rhs;
};

} // namespace ast

} // namespace vfn
