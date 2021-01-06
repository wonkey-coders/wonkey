
@manpage Lambda functions

### What are 'lambda functions'?

A lambda function is a special type of function that can be declared in the middle of an expression.

You can think of a lambda function a bit like a ‘temporary’ function – instead of having to declare an entirely separate function to do what you need, you can just declare a lambda function ‘on the fly’ in the middle of an expression.

 A lambda function is anonymous. It has no name so can only be used by the expression it is declared within.

A lambda functions can make use of the same local variables as the expression it is declared within. It does this by ‘capturing’ these variables, which means the lambda function receives a copy of the local variable’s value at the point the lambda function is declared. This means that a lambda function will not ‘see’ any  future modifications to local variables. A lambda function cannot ‘see’ local variables that have not been declared yet!

If a lambda function is declared within a method, it can also see (and modify) object fields, and call object methods.

Here is a simple example:

@example
Function Test( func:Void() )
   
   func()

End

Function Main()

   Test( Lambda()

      Print "Hello from lambda!"

   End )

End
@end
