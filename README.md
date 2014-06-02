AM generic
==========

Collection of some tools for generic programming in C++11

Note: 
All classes and functions are work in progress. Interfaces are still likely 
to change over time and documentation is very poor so far. 


All components are header-only.


Classes
-------
- timer<br/>
<p>
  simple start-stop timer based on std::chrono
</p>
  
- integer_sequence<br/>
<p>
  static integer sequence needed for variadic initialization/'exploding' 
  something similar (and most likely better engineered) will be in the C++14
  standard library
</p> 
 
- cached_function<br/>
<p>
  std::function - like wrapper with return value cache
</p>
 
- tuple_hash<br/>
<p> 
  xors std::hash values of tuple arguments together
</p>

Type Traits
- all<br/>
<p>
  maps logical AND over a variadic sequence of type traits modeled on 
  std::integral_constant<bool,.>
</p>

- any<br/>
<p>
  maps logical OR over a variadic sequence of type traits modeled on 
  std::integral_constant<bool,.>
</p>


Functions
---------
- make_function_composition<br/>
<p>
  composes multiple functors into one
</p>
  
- make_application_chain<br/>
<p>
  chains calls to 'apply(f_i, args...)' for multiple functors 
</p>
  
- make_uniform<br/>
<p>
  returns a copy of an object initialized with n times the same value
</p>

- make_generate<br/>
<p>
  returns a copy of an object initialized with n results obtained by 
  n calls to a generator object
</p>
  
- make_copy_elems<br/><p>
  returns a copy of an object initialized with n values obtained from n
  subscript calls (with indices 0...n-1) to a source object
</p>
  

- apply(functor, tuple&lt;arguments...&gt;)<br/>
<p>
  explodes tuple arguments into function arguments
</p>
  

- map(functor, tuple&lt;arguments...&gt;)<br/>
<p>
  applies a functor to each argument of a tuple of arguments<br/>
  returns a tuple of results<br/>
  map(f, {x1,x2,...,xn}) -> {f(x1),f(x2),...,f(xn)}
</p>
  

- map(tuple&lt;functors...&gt;, arguments...)<br/>
<p>
  applies each functor in a tuple to a series arguments<br/>
  returns a tuple of results<br/>
  map({f1,f2,...,fn}, x1,x2,...,xn) -> {f1(x1,...,xn),...,fn(x1,...,xn)}
</p>
  

- zip_map(tuple&lt;functors...&gt;, tuple&lt;arguments...&gt;)<br/>
<p>
  applies each functor to each argument 1-by-1<br/>
  returns a tuple of results<br/>
  zip_map({f1,f2,...,fn}, {x1,x2,...,xn}) -> {f1(x1),f2(x2),...,fn(xn)}
</p>
  

- act(functor, tuple&lt;arguments...&gt;)<br/>
<p>
  applies a functor to each argument in a tuple of arguments<br/>
  discards the results and returns void<br/>
  act(f, {x1,x2,...,xn}): {f(x1); f(x2); ...; f(xn);}
</p>
  

- act(tuple&lt;functors...&gt;, arguments...)<br/>
<p>
  applies each functor to all arguments in turn<br/>
  discards the results and returns void<br/>
  act({f1,f2,...,fn}, x1,x2,...,xn): {f1(x1,...,xn); ...; fn(x1,...,xn);}
</p>
  
  
- zip_act(tuple&lt;functors...&gt;, tuple&lt;arguments...&gt;)<br/>
<p>
  applies each functor to each argument 1-by-1<br/>
  discards the results and returns void<br/>
  zip_act({f1,f2,...,fn}, {x1,x2,...,xn}) {f1(x1); f2(x2); ...; fn(xn);}
</p>


Requirements
------------
 - variadic templates
 - template aliases
 - std::tuple
 - std::array
 - std::unordered_map
 - &lt;chrono&gt;
 - &lt;type_traits&gt;

tested with g++ 4.7.2
