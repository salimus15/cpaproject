cpaproject
==========

Projet Compilation Avancée

Add to gcc a plugin wich checks if inner loops in a function can be vectorized or no, in a first time we do it 
dinamycaly (at run-time) for functions we passed to as parameter to a pragma, and then we will try to do it 
staticaly (at compil-time) for the same functions.

for exemple: 
- If we have the following function  

  void my_function( int ** tab){
    for( int i = 0; i < tabSize; ++i){
      for( int j = 0; j < tabSize, ++j){
        ********
        ********
      }
    }
    
- For testing if the inner loop in this function can be vectorized or no so we insert the following line
at the begining of the file:
   #pragma mihp vcheck my_function
   
- Then we look if the loop "for( int j = 0; j < tabSize, ++j)" can be vectorized.
