
@manpage Enums

### Enums

An enum is a user defined data type that contains a set of named integer constants. Enums are frequently used to implement typesafe 'flags' or 'bitmasks'.

Unintialized enum members are automatically assigned constant integer values starting with 0 and increasing by 1 for each successive enum member:

```
Enum MyEnum
	A,B,C			'A, B, C will be assigned the values 0, 1, 2.
	D,E,F			'D, E, F will be assigned the values 4, 5, 6.
End
```

You can also initialize enum members with a constant integer value:

```
Enum MyEnum
	A=10,B=20,C=30	'A, B, C will be assigned the values 10,20,30
	D,E,F			'D, E, F will be assigned the values 31, 32, 33.
End
```

Enum members are accessed using the 'dot' operator:

```
Local e:MyEnum=MyEnum.A
```

Enum values can be implictly converted to any integer type, and can be used with the `&` (bitwise 'and'), `|` (bitwise 'or') and `~` (bitwise 'exclusive-or') binary operators. This allows you to use enums to represent 'bitmasks'.

Enum values can also be compared with enum values of the same type, or with a `Null` which represents an enum value with the integer value 0.

