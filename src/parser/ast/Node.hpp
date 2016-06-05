// File: Node.hpp
#pragma once

#include <stdexcept>
#include <memory>

namespace vfn {

namespace ast {

class Value;
using ValuePtr = std::shared_ptr<Value>;

class Node
{
  public:
    virtual ~Node() { }

    virtual ValuePtr evaluate() = 0;

    virtual operator bool() const
    {
        throw std::runtime_error("Not castable");
    }

    virtual ValuePtr& lookup(const std::string& varname)
    {
        return parent->lookup(varname);
    }

    virtual void addVar(const std::string& varname)
    {
        parent->addVar(varname);
    }

    Node* parent;

  protected:
    Node()
        : parent(nullptr)
    { }
};

// shared_ptr needed because ValuePtr must use shared_ptr and might be
// stored as NodePtr in some places. ValuePtr needs to be a shared_ptr
// because sometimes it is returned as a new value and sometimes as an
// owning reference to an existing one.
using NodePtr = std::shared_ptr<Node>;

} // namespace ast

} // namespace vfn

#include "Value.hpp"      // Warning: Tricky order-dependent includes!
