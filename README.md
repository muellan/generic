AM generic
==========

Header-only collection of generic programming tools for C++11.

**Note**: All classes and functions are work in progress.
Interfaces are still likely to change over time and documentation is limited to some comments so far. 


## Quick Overview

### Classes

#### integer&#95;sequence
  static integer sequence needed for variadic initialization/'exploding' something similar
  (and most likely better engineered) will be in the C++14 standard library
 
#### cached&#95;function
  std::function - like wrapper with return value cache
 
#### tuple&#95;hash
  xors std::hash values of tuple arguments together


### Type Traits
#### all
  maps logical AND over a variadic sequence of type traits
  modeled on std::integral&#95;constant<bool,.>

#### any
  maps logical OR over a variadic sequence of type traits
  modeled on std::integral&#95;constant<bool,.>


### Functions

#### make&#95;function&#95;composition
  composes multiple function objects into one
  
#### make&#95;application&#95;chain
  chains calls to 'apply(f&#95;i, args...)' for multiple function objects 
  
#### make&#95;uniform
  returns a copy of an object initialized with n times the same value

#### make&#95;generate
  returns a copy of an object initialized with n results obtained by
  n calls to a generator object

#### make&#95;copy&#95;elems
  returns a copy of an object initialized with n values obtained from
  n subscript calls (with indices 0...n-1) to a source object

#### apply(function object, tuple&lt;arguments...&gt;)
  explodes tuple arguments into function arguments

#### map(function object, tuple&lt;arguments...&gt;)
  applies a function object to each argument of a tuple of arguments<br/>
  returns a tuple of results<br/>
  map(f, {x1,x2,...,xn}) -> {f(x1),f(x2),...,f(xn)}
  

#### map(tuple&lt;function&#95;objects...&gt;, arguments...)
  applies each function object in a tuple to a series of arguments<br/>
  returns a tuple of results<br/>
  map({f1,f2,...,fn}, x1,x2,...,xm) -> {f1(x1,...,xm),...,fn(x1,...,xm)}
  

#### zip&#95;map(tuple&lt;function&#95;objects...&gt;, tuple&lt;arguments...&gt;)
  applies each function&#95;object to each argument 1-by-1<br/>
  returns a tuple of results<br/>
  zip&#95;map({f1,f2,...,fn}, {x1,x2,...,xn}) -> {f1(x1),f2(x2),...,fn(xn)}


#### for&#95;each&#95;arg(function&#95;object, tuple&lt;arguments...&gt;)
  applies a function object to each argument in a tuple of arguments<br/>
  discards the results and returns void<br/>
  for&#95;each&#95;arg(f, {x1,x2,...,xn}): {f(x1); f(x2); ...; f(xn);}
  

#### for&#95;each&#95;function(tuple&lt;function...&gt;, arguments...)
  applies each function object to all arguments in turn<br/>
  discards the results and returns void<br/>
  for&#95;each&#95;function({f1,f2,...,fn}, x1,x2,...,xn): {f1(x1,...,xn); ...; fn(x1,...,xn);}
  

#### zip&#95;for&#95;each(tuple&lt;function&#95;objects...&gt;, tuple&lt;arguments...&gt;)
  applies each function object to each argument 1-by-1<br/>
  discards the results and returns void<br/>
  zip&#95;for&#95;each({f1,f2,...,fn}, {x1,x2,...,xn}) {f1(x1); f2(x2); ...; fn(xn);}


## Requirements
 - variadic templates
 - template aliases
 - std::tuple
 - std::array
 - std::unordered&#95;map
 - &lt;chrono&gt;
 - &lt;type&#95;traits&gt;

tested with g++ 4.7.2
