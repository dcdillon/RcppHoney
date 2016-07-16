# RcppHoney

RcppHoney provides functions and operators with R semantics for any container type that has a const_iterator.  All operators and functions are implemented as expression templates to minimize temporary copies of containers.  It is integrated with Rcpp's wrap functionality so that results can easily be exported to R.

The goal is to provide full featured interoperability between any iterator based structures and R to reduce development time and simplify code.  It is currently in a pre-amp have state, but we hope to have a stable API in the next week or so.
