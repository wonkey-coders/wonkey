
@manpage Loop Statements

### Loop statements

@#### While

The `While` loop allows you to execute a block of statements repeatedly while a boolean expression evaluates to true.

Note that a `While` loop may never actually execute any of it's statements if the expression evaluates to false when the loop is entered.

The syntax for the `While` loop is:

`While` _Expression_

     _Statements..._

`Wend`

`End` or `End While` may be used instead of `Wend`.

`Exit` and `Continue` may be used within a While loop to abruptly terminate or continue loop execution.

@#### Repeat

Like the `While` loop, the `Repeat` loop also allows you to execute a block of statement repeatedly while a boolean expression evaluates to true.

However, unlike a `While` loop, a `Repeat` loop is guaranteed to execute at least once, as the boolean expression is not evaluated until the end of the loop.

The syntax for `Repeat`/`Until` loops is:

`Repeat`

     _Statements..._

`Until` _Expression_

..or..

`Repeat`

     _Statements..._

`Forever`

`Exit` and `Continue` may be used within a Repeat loop to abruptly terminate or continue loop execution.

@#### For

A numeric `For` loop will continue executing until the value of a numeric index variable reaches an exit value.

The index variable is automatically updated every loop iteration by adding a constant step value.

The syntax for a numeric `For` loop is:


`For` [ `Local` ] _IndexVariable_ [:]= _FirstValue_ `To` | `Until` _LastValue_ [ `Step` _StepValue_ ]

     _Statements..._

`Next`


`End` or `End For` may be used instead of `Next`.

If present, `Local` will create a new local index variable that only exists for the duration of the loop. In addition, IndexVariable must include the variable type, or `:=` must be used instead of `=` to implicitly set the variable's type.

If `Local` is not present, IndexVariable must be a valid, existing variable.

The use of `To` or `Until` determines whether LastValue should be inclusive or exclusive.

If `To` is used, the loop will exit once the index variable is greater than LastValue (or less than if StepValue is negative).

If `Until` is used, the loop will exit once the index variable is greater than or equal to LastValue (or less than or equal to if StepValue is negative).

If omitted, StepValue defaults to 1.

`Exit` and `Continue` may be used within a numeric For loop to abruptly terminate or continue loop execution.

@#### For Eachin

A `For` `EachIn` loop allows you to iterate through the elements of a collection.

A collection is either an array, a string, or a specially designed object.

The syntax for a `For` `EachIn` loop is:

`For` [ `Local` ] _IndexVariable_ [:]= `EachIn` _Collection_

     _Statements..._

`Next`

`End` or `End For` may be used instead of `Next`.

If present, `Local` will create a new local index variable that only exists for the duration of the loop. In addition, IndexVariable must include the variable type, or `:=` must be used instead of `=` to implicitly set the variable's type.

If `Local` is not present, IndexVariable must be a valid, existing variable.

If Collection is an array, the loop will iterate through each element of the array, and the type of the index variable must match the element type of the array.

If Collection is a string, the loop will iterate through each character code of the string, and the type of the index variable must be numeric.

If Collection is an object, it must implement the [[std:std.collections.IContainer]] interface.

@#### Exit

`Exit` can be used within `While`, `Repeat` and `For` loops to abruptly exit the loop before the loop termination condition has been met.

@#### Continue

Continue can be used within `While`, `Repeat` and `For` loops to force the loop to abruptly skip to the next loop iteration, skipping over any statements that may be remaining in the current loop iteration.
