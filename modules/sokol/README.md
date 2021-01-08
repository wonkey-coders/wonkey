# Sokol C-libraries binding for Monkey2

 https://github.com/floooh/sokol 

Simple [STB-style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt) cross-platform libraries for C and C++, written in C.

## Core libraries

- [**sokol_gfx.h**](https://github.com/floooh/sokol/blob/master/sokol_gfx.h): 3D-API wrapper (GL + Metal + D3D11)
- [**sokol_app.h**](https://github.com/floooh/sokol/blob/master/sokol_app.h): app framework wrapper (entry + window + 3D-context + input)
- [**sokol_time.h**](https://github.com/floooh/sokol/blob/master/sokol_time.h): time measurement
- [**sokol_audio.h**](https://github.com/floooh/sokol/blob/master/sokol_audio.h): minimal buffer-streaming audio playback
- [**sokol_fetch.h**](https://github.com/floooh/sokol/blob/master/sokol_fetch.h): asynchronous data streaming from HTTP and local filesystem
- [**sokol_args.h**](https://github.com/floooh/sokol/blob/master/sokol_args.h): unified cmdline/URL arg parser for web and native apps

## Utility libraries

- [**sokol_imgui.h**](https://github.com/floooh/sokol/blob/master/util/sokol_imgui.h): sokol_gfx.h rendering backend for [Dear ImGui](https://github.com/ocornut/imgui)
- [**sokol_gl.h**](https://github.com/floooh/sokol/blob/master/util/sokol_gl.h): OpenGL 1.x style immediate-mode rendering API on top of sokol_gfx.h
- [**sokol_fontstash.h**](https://github.com/floooh/sokol/blob/master/util/sokol_fontstash.h): sokol_gl.h rendering backend for [fontstash](https://github.com/memononen/fontstash)
- [**sokol_gfx_imgui.h**](https://github.com/floooh/sokol/blob/master/util/sokol_gfx_imgui.h): debug-inspection UI for sokol_gfx.h (implemented with Dear ImGui)
- [**sokol_debugtext.h**](https://github.com/floooh/sokol/blob/master/util/sokol_debugtext.h): a simple text renderer using vintage home computer fonts
- [**sokol_memtrack.h**](https://github.com/floooh/sokol/blob/master/util/sokol_memtrack.h): easily track memory allocations in sokol headers

## Notes

WebAssembly is a 'first-class citizen', one important motivation for the Sokol headers is to provide a collection of cross-platform APIs with a minimal footprint on the web platform while still being useful.

The core headers are standalone and can be used independently from each other.

Sample code is in a separate repo: https://github.com/floooh/sokol-samples

Command line tools: https://github.com/floooh/sokol-tools

Tiny 8-bit emulators: https://floooh.github.io/tiny8bit/

### Why C:

- easier integration with other languages
- easier integration into other projects
- adds only minimal size overhead to executables

A blog post with more background info: [A Tour of sokol_gfx.h](http://floooh.github.io/2017/07/29/sokol-gfx-tour.html)

See more :  https://github.com/floooh/sokol 

## Build module

__NOTE__: on macOS, Sokol need to add C/C++ compiler flag in './bin/env_macos.txt': `-fobjc-arc`

Launch commands :

```shell
mx2cc makemods -clean -config=debug sokol
mx2cc makemods -clean -config=release sokol
mx2cc makedocs sokol
```

## Minimal sample

```monkey2
namespace sokol.sample

#import "<libc>"
#import "<std>"
#import "<sokol>"

using std.memory..
using sokol..

'---------------------
' Main entry
'---------------------
function Main()
	local desc:sapp_desc
	desc.window_title = CStr("sokol-app")
	desc.width = 800
	desc.height = 600
	
	'// callbacks
	desc.init_cb = init
	desc.frame_cb = frame
	desc.event_cb = event
	desc.fail_cb = fail
	desc.cleanup_cb = cleanup
	
	sapp_run(varptr desc)
end

function init:void()
	' Init callback
end

function frame:void()
	'Frame callback
end

function cleanup:void()
 'Cleanup callback
	sapp_quit()
end

function fail:void(err:libc.const_char_t ptr)
 'Fail callback
 
	print "sapp fail: " + String.FromCString(err)
end

function event:void(e:sapp_event ptr)
 'Event callback
 
	select e->type
		case SAPP_EVENTTYPE_KEY_UP
			select e->key_code
				case SAPP_KEYCODE_ESCAPE
					sapp_request_quit()
			end
		case SAPP_EVENTTYPE_QUIT_REQUESTED
			print "Quit requested!"
	end
end

'// Helper : Convert monkey 'string' to C/C++ 'const char*'
function CStr:libc.const_char_t Ptr( str:string )
	local cstr:= new DataBuffer(str.Length+1)
	str.ToCString(cstr.Data, cstr.Length)
	local cstrptr:= cast<libc.const_char_t ptr>(cstr.Data)
	return cstrptr
end
```
