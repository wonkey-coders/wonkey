
@manpage Streams

# Streams

The std module includes a simple stream system for reading and writing data sequentially to and from files and other data sources.

The stream system is built around the abstract [[Stream]] class, which provides a number of core abstract methods for reading and writing raw binary data such as [[Stream.Read]] and [[Stream.Write]], as well as a number of utility methods for reading and writing typed data such as integers, float point values and so on, for example [[Stream.ReadInt]] and [[Stream.WriteFloat]] etc.

The Stream class is extended by a number of concrete classes including:

| Stream subclass	| Description
|:------------------|:-----------
| [[FileStream]]	| For reading/writing files.
| [[DataStream]]	| For reading/writing databuffers.
| [[SocketStream]]	| For reading/writing sockets.
| [[ProcessStream]]	| For reading/writing processes.

The easiest way to open a stream is to use the [[Stream.Open]] function. This takes a string `path` parameter and attempts to open a concrete stream type based on the contents of the path. The stream path may contain a number of prefixs:

| Stream path prefix	| Supported targets | Description
|:----------------------|:------------------|:-----------
| `asset::`				| All				| Open a stream for reading an app asset.
| `internal::`			| Mobile			| Open a stream for reading/writing internal app storage.
| `external::`			| Android			| Open a stream for reading/writing external app storage.
| `home::`				| Desktop 			| Open a stream for reading/writing a file in the user's home directory.
| `desktop::`			| Desktop 			| Open a stream for reading/writing a file in the user's desktop directory.

The remainder of a stream path that begins with such a prefix generally resembles a normal file path, however it is important to remember that such paths are NOT actually OS file system paths.

Some types of strems must be explictly created by construction and cannot be opened using Stream.Open. For example, a DataStream provides the ability to read/write databuffers, and must therefore be created directly by passing a DataBuffer to a DataStream constructor - see [[DataStream.New]].






