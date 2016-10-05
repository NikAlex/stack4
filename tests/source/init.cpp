#include "stack.cpp"
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("top", "[top]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  REQUIRE(s.top()==3);
}
  
SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("operprisv", "[operprisv]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2;
  s2=s1;
  REQUIRE(s1.count()==s2.count());
}

SCENARIO("copy", "[copy]"){
    stack<int> s1;
    s1.push(3);
    stack<int> s2(s1);
    REQUIRE(s2.count() == 1);
}

SCENARIO("const", "[constr]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2=s1;
  REQUIRE(s1.count()==s2.count());
 }
