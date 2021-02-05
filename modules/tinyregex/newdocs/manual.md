@manpage The tinyregex module

# tiny-regex-c

# A small regex implementation in C

### Description

Small and portable [[https://en.wikipedia.org/wiki/Regular_expression|Regular Expression]] (regex) library written in C. 

Design is inspired by Rob Pike's regex-code for the book *"Beautiful Code"* [[http://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html|available online here]].

Supports a subset of the syntax and semantics of the Python standard library implementation (the `re`-module).

**I will gladly accept patches correcting bugs.**

### Design goals

The main design goal of this library is to be small, correct, self contained and use few resources while retaining acceptable performance and feature completeness. Clarity of the code is also highly valued.

### Notable features and omissions

- Small code and binary size: 500 SLOC, ~3kb binary for x86. Statically #define'd memory usage / allocation.

- No use of dynamic memory allocation (i.e. no calls to `malloc` / `free`).

- To avoid call-stack exhaustion, iterative searching is preferred over recursive by default (can be changed with a pre-processor flag).

- No support for capturing groups or named capture: `(^P<name>group)` etc.

- Thorough testing : [[https://github.com/asciimoo/exrex|exrex]] is used to randomly generate test-cases from regex patterns, which are fed into the regex code for verification. Try `make test` to generate a few thousand tests cases yourself.

- Provides character length of matches.

- Compiled for x86 using GCC 7.2.0 and optimizing for size, the binary takes up ~2-3kb code space and allocates ~0.5kb RAM :

```
> gcc -Os -c re.c
> size re.o
    text     data     bss     dec     hex filename
    2404        0     304    2708     a94 re.o
```

### API

This is the public / exported API:
```
' Typedef'd pointer to hide implementation details.
Alias re_t:Void Ptr

' Compiles regex string pattern to a regex_t-array.
Function re_compile:re_t( pattern:CString )

' Finds matches of the compiled pattern inside text.
Function re_matchp:Int( pattern:re_t, text:CString, matchlength:Int Ptr )

' Finds matches of pattern inside text (compiles first automatically).
Function re_match:Int( pattern:CString, text:CString, matchlength:Int Ptr )
```

### Supported regex-operators
The following features / regex-operators are supported by this library.

NOTE: inverted character classes are buggy - see the test harness for concrete examples.


  -  `.`         Dot, matches any character

  -  `^`         Start anchor, matches beginning of string

  -  `$`         End anchor, matches end of string

  -  `*`         Asterisk, match zero or more (greedy)

  -  `+`         Plus, match one or more (greedy)

  -  `?`         Question, match zero or one (non-greedy)

  -  `[abc]`     Character class, match if one of {'a', 'b', 'c'}

  -  `[^abc]`   Inverted class, match if NOT one of {'a', 'b', 'c'}

  -  `[a-zA-Z]` Character ranges, the character set of the ranges { a-z | A-Z }

  -  `\\s`       Whitespace, \\t \\f \\r \\n \\v and spaces

  -  `\\S`       Non-whitespace

  -  `\\w`       Alphanumeric, [a-zA-Z0-9_]

  -  `\\W`       Non-alphanumeric

  -  `\\d`       Digits, [0-9]

  -  `\\D`       Non-digits

### Usage
Compile a regex from ASCII-string (char-array) to a custom pattern structure using `re\_compile()`.

Search a text-string for a regex and get an index into the string, using `re\_match()` or `re\_matchp()`.

The returned index points to the first place in the string, where the regex pattern matches.

The integer pointer passed will hold the length of the match.

If the regular expression doesn't match, the matching function returns an index of -1 to indicate failure.

### Examples
Example of usage:

```
#Import "<tinyregex>"

Using tinyregex

Function Main()
	' Standard int to hold length of match
	Local match_length:Int

	' Standard null-terminated C-string to search:
	Local string_to_search := "ahem.. 'hello world !' .."

	' Compile a simple regular expression Using character classes, meta-char And greedy + non-greedy quantifiers:
	Local pattern := re_compile("[Hh]ello [Ww]orld\s*[!]?")

	' Check if the regex matches the text:
	Local match_idx := re_matchp(pattern, string_to_search, Varptr match_length)
	If match_idx <> -1
		Print "match at idx "+match_idx+", "+match_length+" chars long."
	Endif
End
```

For more usage examples I encourage you to look at the code in the `tests`-folder.

### TODO

- Fix the implementation of inverted character classes.

- Fix implementation of branches (`|`), and see if that can lead us closer to groups as well, e.g. `(a|b)+`.

- Add `example.c` that demonstrates usage.

- Add `tests/test_perf.c` for performance and time measurements.

- Testing: Improve pattern rejection testing.

### FAQ
- *Q: What differentiates this library from other C regex implementations?*

  A: Well, the small size for one. 500 lines of C-code compiling to 2-3kb ROM, using very little RAM.

### License
All material in this repository is in the public domain.



 
