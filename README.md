AM generic
==========

Collection of some tools for generic programming in C++11

All components are header-only.


Classes
-------
- timer
  simple start-stop timer based on std::chrono
  
- integer_sequence
  static integer sequence needed for variadic initialization
  something similar (and most likely better engineered) will be in the C++14
  standard library
  
- cached_function
  std::function - like wrapper with return value cache
    
- tuple_hash 
  xors std::hash values of tuple arguments together

Type Traits
- map_bool_trait
  maps a type traits modeled on std::integral_constant<bool,...> to
  a variadic type sequence "variadic AND of type trait application" 


Functions
---------
- function_composition
  composes multiple functors into one

- make_application_chain
  chains calls to 'apply(f_i, args...)' for multiple functors 

- make_uniform
  returns a copy of an object initialized with n times the same value 

- make_generate
  returns a copy of an object initialized with n results obtained by 
  n calls to a generator object
  
- make_copy_elems
  returns a copy of an object initialized with n values obtained from n
  subscript calls (with indices 0...n-1) to a source object
  

- apply(function/functor/lambda, tuple of arguments)


Requirements
------------
 - variadic templates
 - template aliases
 - <tuple>
 - <array>
 - <unordered_map>
 - <chrono>
 - <type_traits>

tested with g++ 4.7.2
