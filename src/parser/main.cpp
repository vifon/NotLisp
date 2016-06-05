// File: main.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main(int argc, char *argv[])
{
    const char* PROGRAM = R"(
let v = 10;
let v2 = 0;
for (i in [1, 2, 3]) {
  let v3 = i + v;
  v2 = v2 + 2;
  print(i);
  print(v);
  print(v2);
  print(v3);
}

for (i in [1, 2, 3]) {
  print(v);
  let v = i + v;
  print(i);
  print(v);
}
)";

    std::stringstream stream{PROGRAM};
    vfn::Parser p{std::make_unique<vfn::Lexer>(stream)};

    p.parse()->evaluate();

    return 0;
}
