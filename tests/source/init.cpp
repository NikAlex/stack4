#include "stack.cpp"
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
  REQUIRE(s.pop()>=0);
}

SCENARIO("operprisv", "[operprisv]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2;
  s2=s1;
  REQUIRE(s1.count()==s2.count());
}

SCENARIO("copy", "[copy]"){
    Stack<int> s;
    s.push(3);
    Stack<int> s2(s);
    REQUIRE(s2.count() == 1);
    REQUIRE(s2.pop() == 3);
}

SCENARIO("const", "[constr]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2=s1;
  REQUIRE(s1.count()==s2.count());
 }


SCENARIO("empty", "[empty]"){
  stack<int> s1;
  s1.push(1);
  REQUIRE(s1.empty()==false);
}

SCENARIO("empty2", "[empty2]"){
  stack<int> s1;
  s1.push(1);
  s1.pop();
  REQUIRE(s1.empty()==true);
}

SCENARIO("empty3", "[empty3]"){
  stack<int> s1;
  s1.push(1);
  s1.push(2);
  s1.pop();
  
  REQUIRE(s1.empty()==false);
}
