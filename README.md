# Calculator
  To Compile: c++ calculator.cpp -o calculator
  To Run:     ./calculator
  
# Overview
 Lexical analyzer works
 Parser does not fully work. Seg faults with larger expressions.
 For example 12 + 5, 12 gets set to LHS, plus gets set to operator, but 5
 does not get set to RHS. No error checking.... Anywhere... Sorry.
