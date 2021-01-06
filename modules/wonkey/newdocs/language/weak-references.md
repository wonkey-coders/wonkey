
@manpage Weak References

# Weak References

A weak reference is a special kind of reference to an object that does not prevent that object from being garbage collected. Normally, storing a reference to an object in a variable will prevent that object from ever being garbage collected as long as the variable itself remains alive. However, weak references allow you store a reference will still allowing the object to be garbage collected.

The object a weak reference refers to is called the 'target' object. To create a weak reference, you must create a WeakRef object with the target object. Then, when you want to obtain the target object from a weak reference, you should use the Target property.

Here is a simple example:

```
Local weakref:WeakRef=New WeakRef( someObject )
'Some time later...
Local target:Object=weakref.Target	'May return Null if someObject has been garbage collected.
```

The Target property will return the object the weak reference was created with unless the object has been garbage collected, in which case it will return null.

A weak reference itself is just an object so will also be garbage collected when it is itself no longer referenced by any variables.

Weak references are often used for creating 'cache' systems.
