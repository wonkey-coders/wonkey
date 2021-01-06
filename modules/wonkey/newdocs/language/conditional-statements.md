
@manpage Conditional statements

### Conditional statements

@#### If

The `If` statement allows you to conditionally execute a block of statements depending on the result of a series of boolean expressions.

The first boolean expression that evaluates to true will cause the associated block of statements to be executed. No further boolean expressions will be evaluated.

If no boolean expression evaluates to true, then the final else block will be executed if present.

The syntax for the `If` statement is:

`If` _Expression_ [ `Then` ]

     _Statements..._

`ElseIf` _Expression_ [ `Then` ]

     _Statements..._

`Else`

     _Statements..._

`EndIf`

There may be any number of `ElseIf` blocks, or none. The final `Else` block is optional.

`End` or `End If` may be used instead of `EndIf`, and `Else` If may be used instead of `ElseIf`.

In addition, a simple one line version of `If` is also supported:

`If` _Expression_ [ `Then` ] _Statement_ [ `Else` _Statement_ ]

@#### Select

The `Select` statement allows you to execute a block of statements depending on a series of comparisons.

The first comparison to produce a match will cause the associated block of statements to be executed.

If no comparisons produce a match, then the final `Default` block will be executed if present.

The syntax for the `Select` statement is:

`Select` _Expression_

`Case` _Expression_ [ , _Expression_... ]

     _Statements..._

`Default`

     _Statements..._

`End` [ `Select` ]

There may be any number of `Case` blocks, or none. The final `Default` block is optional. If the default block is present, it must appear after all `Case` blocks.

@#### ? Else

the `? Else` operator is used to assign a value with a condition:

_variable_=_Expression_ `?` _Expression-A_ `Else` _Expression-B_

the _variable_ will receive the value of _Expression-A_ if _Expression_ is True, else it will receive the value of _Expression-B_.

```
i=j>2 ? 5 else j+7
```

@#### ?Else

The 'Elvis operator' `?Else` can be used to return an alternate value if an expression is null.

_variable_=_Expression_ `?Else` _Expression-B_

For example:

```
r=x ?Else -1
```

This will assign the value of `x` to `r` if `x` is non-null otherwise, it will assign the value -1 to `r`.


