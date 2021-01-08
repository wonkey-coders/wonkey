namespace sokol.samples

#import "<libc>"
#import "<std>"
#import "<sokol>"

using std.memory..
using sokol..

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
	'// JUST-DO-IT!
end

function frame:void()
	'// JUST-DO-IT!
end

function cleanup:void()
	sapp_quit()
end

function fail:void(err:libc.const_char_t ptr)
	print "sapp fail: " + String.FromCString(err)
end

function event:void(e:sapp_event ptr)
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

'// Convert monkey 'string' to C/C++ 'const char*'
function CStr:libc.const_char_t Ptr( str:string )
	local cstr:= new DataBuffer(str.Length+1)
	str.ToCString(cstr.Data, cstr.Length)
	local cstrptr:= cast<libc.const_char_t ptr>(cstr.Data) 'mem leak?
	return cstrptr
end