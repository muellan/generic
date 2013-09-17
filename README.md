AM generic
==========

Collection of some tools for generic programming in C++11

All components are header-only.


Classes
-------
- timer</br>
<p>
  simple start-stop timer based on std::chrono
</p>
  
- integer_sequence</br>
<p>
  static integer sequence needed for variadic initialization
  something similar (and most likely better engineered) will be in the C++14
  standard library
</p> 
 
- cached_function</br>
<p>
  std::function - like wrapper with return value cache
</p>
 
- tuple_hash</br>
<p> 
  xors std::hash values of tuple arguments together
</p>

Type Traits
- map_bool_trait</br>
<p>
  maps a type traits modeled on std::integral_constant<bool,...> to
  a variadic type sequence "variadic AND of type trait application" 
</p>


Functions
---------
- function_composition</br>
<p>
  composes multiple functors into one
</p>
  
- make_application_chain</br>
<p>
  chains calls to 'apply(f_i, args...)' for multiple functors 
</p>
  
- make_uniform</br>
<p>
  returns a copy of an object initialized with n times the same value
</p>

- make_generate</br>
<p>
  returns a copy of an object initialized with n results obtained by 
  n calls to a generator object
</p>
  
- make_copy_elems</br><p>
  returns a copy of an object initialized with n values obtained from n
  subscript calls (with indices 0...n-1) to a source object
</p>
  

- apply(function/functor/lambda, tuple of arguments)


Requirements
------------
 - variadic templates
 - template aliases
 - tuple
 - array
 - unordered_map
 - chrono
 - type_traits

tested with g++ 4.7.2
