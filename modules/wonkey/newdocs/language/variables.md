
@manpage Variables

### Variables

@#### Local variables

Local variables live on the stack. To declare a local variable:

<div class=syntax>
`Local` _identifier_ `:` _Type_ [ `=` _Expression_ ]
</div>

...or...

<div class=syntax>
`Local` _identifier_ `:=` _Expression_
</div>


@#### Global variables

Global variables live in global memory and exist for the lifetime of the application. To declare a global variable:

<div class=syntax>
`Global` _Identifier_ `:` _Type_ [ `=` _Expression_ ]
</div>

...or...

<div class=syntax>
`Global` _Identifier_ `:=` _Expression_
</div>

@#### Consts

Consts are stored in the same way as globals, but cannot be modified after they are initialized. To declare a const:

<div class=syntax>
`Const` _Identifier_ `:` _Type_ `=` _Expression_
</div>

...or...

<div class=syntax>
`Const` _Identifier_ `:=` _Expression_
</div>

