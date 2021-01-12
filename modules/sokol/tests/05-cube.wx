namespace sokol.samples

#import "<libc>"
#import "<std>"
#import "<sokol>"

using std.memory..
using std.geom..
using sokol..

'/* application state */
struct state_t
	field pip:sg_pipeline
	field bind:sg_bindings
	field pass_action:sg_pass_action

	'// cube rotation
	field rx:float, ry:float
end

global state:= new state_t
const SAMPLE_COUNT:= 4

struct vs_params_t
	field mvp:Mat4f '4x4
end


function Main()
	local desc:sapp_desc
	desc.window_title = CStr("sokol-cube")
	desc.width = 800
	desc.height = 600
	desc.sample_count = SAMPLE_COUNT
	
	'// callbacks
	desc.init_cb = init
	desc.frame_cb = frame
	desc.event_cb = event
	desc.fail_cb = fail
	desc.cleanup_cb = cleanup
	
	sapp_run(varptr desc)
end

function init:void()
	local desc:sg_desc
	desc.gl_force_gles2 = sapp_gles2()
	desc.mtl_device = sapp_metal_get_device()
	desc.mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor
	desc.mtl_drawable_cb = sapp_metal_get_drawable
	desc.d3d11_device = sapp_d3d11_get_device()
	desc.d3d11_device_context = sapp_d3d11_get_device_context()
	desc.d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view
	desc.d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
	sg_setup(varptr desc)

	'/* cube vertex buffer */
	local vertices:= new float[](
		'// position		// color
	-1.0,-1.0,-1.0,		1.0, 0.0, 0.0, 1.0,
	 1.0,-1.0,-1.0,		1.0, 0.0, 0.0, 1.0,
	 1.0, 1.0,-1.0,		1.0, 0.0, 0.0, 1.0,
	-1.0, 1.0,-1.0,		1.0, 0.0, 0.0, 1.0,

	-1.0,-1.0, 1.0,		0.0, 1.0, 0.0, 1.0,
	 1.0,-1.0, 1.0,		0.0, 1.0, 0.0, 1.0,
	 1.0, 1.0, 1.0,		0.0, 1.0, 0.0, 1.0,
	-1.0, 1.0, 1.0,		0.0, 1.0, 0.0, 1.0,

	-1.0,-1.0,-1.0,		0.0, 0.0, 1.0, 1.0,
	-1.0, 1.0,-1.0,		0.0, 0.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,		0.0, 0.0, 1.0, 1.0,
	-1.0,-1.0, 1.0,		0.0, 0.0, 1.0, 1.0,

	 1.0,-1.0,-1.0,		1.0, 0.5, 0.0, 1.0,
	 1.0, 1.0,-1.0,		1.0, 0.5, 0.0, 1.0,
	 1.0, 1.0, 1.0,		1.0, 0.5, 0.0, 1.0,
	 1.0,-1.0, 1.0,		1.0, 0.5, 0.0, 1.0,

	-1.0,-1.0,-1.0,		0.0, 0.5, 1.0, 1.0,
	-1.0,-1.0, 1.0,		0.0, 0.5, 1.0, 1.0,
	 1.0,-1.0, 1.0,		0.0, 0.5, 1.0, 1.0,
	 1.0,-1.0,-1.0,		0.0, 0.5, 1.0, 1.0,

	-1.0, 1.0,-1.0,		1.0, 0.0, 0.5, 1.0,
	-1.0, 1.0, 1.0,		1.0, 0.0, 0.5, 1.0,
	 1.0, 1.0, 1.0,		1.0, 0.0, 0.5, 1.0,
	 1.0, 1.0,-1.0,		1.0, 0.0, 0.5, 1.0)
		
	local vb:sg_buffer_desc
	vb.size = vertices.Length * libc.sizeof<float>()
	vb.content = vertices.Data
	vb.label = CStr("cube-vertices")
	vb.type = SG_BUFFERTYPE_VERTEXBUFFER
	state.bind.vertex_buffers[0] = sg_make_buffer(varptr vb)
	
	'/* an index buffer with 2 triangles */
	local indices:= new ushort[](
		0, 1, 2,		0, 2, 3,
		6, 5, 4,		7, 6, 4,
		8, 9, 10,		8, 10, 11,
		14, 13, 12,	15, 14, 12,
		16, 17, 18,	16, 18, 19,
		22, 21, 20,	23, 22, 20)
		
	local ib:sg_buffer_desc
	ib.size = indices.Length * libc.sizeof<ushort>()
	ib.content = indices.Data
	ib.label = CStr("cube-indices")
	ib.type = SG_BUFFERTYPE_INDEXBUFFER
	state.bind.index_buffer = sg_make_buffer(varptr ib)

	'/* create shader */
	local shdesc:sg_shader_desc
	shdesc.label = CStr("cube-shader")
	
#if __TARGET__="macos"
	'/* metal shader format */
	shdesc.vs.uniform_blocks[0].size = 64
	shdesc.vs.source = CStr(
		"#include <metal_stdlib>~n"+
		"using namespace metal;~n"+
		"struct params_t {~n"+
        "  float4x4 mvp;~n"+
         "};~n"+
		"struct vs_in {~n"+
		"	float4 position [[attribute(0)]];~n"+
		"	float4 color [[attribute(1)]];~n"+
		"};~n"+
		"struct vs_out {~n"+
		"	float4 position [[position]];~n"+
		"	float4 color;~n"+
		"};~n"+
		"vertex vs_out _main(vs_in in [[stage_in]], constant params_t& params [[buffer(0)]]) {~n"+
		"	vs_out out;~n"+
		"	out.position = params.mvp * in.position;~n"+
		"	out.color = in.color;~n"+
		"	return out;~n"+
		"}~n")
	
	shdesc.fs.source = CStr(
		"#include <metal_stdlib>~n"+
		"using namespace metal;~n"+
		"fragment float4 _main(float4 color [[stage_in]]) {~n"+
		"	return color;~n"+
		"};~n")
#else
	'/* glsl330 shader format */
	shdesc.attrs[0].name = CStr("position")
	shdesc.attrs[1].name = CStr("color0")
	shdesc.vs.entry = CStr("main")
	shdesc.vs.uniform_blocks[0].size = 64
	shdesc.vs.uniform_blocks[0].uniforms[0].name = CStr("vs_params")
	shdesc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4
	shdesc.vs.uniform_blocks[0].uniforms[0].array_count = 4
	shdesc.vs.source = CStr(
		"#version 330~n"+
		"uniform vec4 vs_params[4];~n"+
		"in vec4 position;~n"+
		"in vec4 color0;~n"+
		"out vec4 color;~n"+
		"void main() {~n"+
		"  gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * position;~n"+
		"  color = color0;~n"+
		"}~n")
	shdesc.fs.entry = CStr("main")
	shdesc.fs.source = CStr(
		"#version 330~n"+
		"in vec4 color;~n"+
		"out vec4 frag_color;~n"+
		"void main() {~n"+
		"  frag_color = color;~n"+
		"}~n")
#end
		
	local shd:sg_shader = sg_make_shader(varptr shdesc)
	
	'/* create a pipeline object (default render states are fine for triangle) */
	local pp:sg_pipeline_desc
	pp.shader = shd
	pp.label = CStr("cube-pipeline")
	pp.index_type = SG_INDEXTYPE_UINT16
	
	'/* test to provide buffer stride, but no attr offsets */
	pp.layout.buffers[0].stride = 28

	'/* if the vertex layout doesn't have gaps, don't need to provide strides and offsets */
	pp.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3
	pp.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4
	
	'// depth/stencil
	pp.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL
	pp.depth_stencil.depth_write_enabled = true
	
	'// rasterizer
	pp.rasterizer.cull_mode = SG_CULLMODE_BACK
	pp.rasterizer.sample_count = SAMPLE_COUNT
	
	state.pip = sg_make_pipeline(varptr pp)
	
	'/* a pass action to framebuffer to gray */
	state.pass_action.colors[0].action = SG_ACTION_CLEAR
	state.pass_action.colors[0].val[0] = 0.12
	state.pass_action.colors[0].val[1] = 0.12
	state.pass_action.colors[0].val[2] = 0.2
	state.pass_action.colors[0].val[3] = 1.0
end

function frame:void()
	
	local w:= sapp_width()
	local h:= sapp_height()

	local proj:= Mat4f.Perspective(60, float(w) / float(h), 0.01, 100.0)
	local view:= Mat4f.LookAt(new Vec3f(0.0, 1.5, 6.0))
	local view_proj:= proj * view
	
	state.rx+= .01
	state.ry+= .02
	local model:= Mat4f.Rotation(state.rx, state.ry, 0.0)

	local vs_params:vs_params_t
	vs_params.mvp = view_proj * model

	sg_begin_default_pass(varptr state.pass_action, w, h)

	sg_apply_pipeline(state.pip)
	sg_apply_bindings(varptr state.bind)
	sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, varptr vs_params, libc.sizeof<vs_params_t>(vs_params))
	sg_draw(0, 36, 1)
	sg_end_pass()
	sg_commit()
end

function cleanup:void()
	sg_shutdown()
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
function CStr:libc.const_char_t ptr( str:string )
	local cstr:= new DataBuffer(str.Length+1)
	str.ToCString(cstr.Data, cstr.Length)
	local cstrptr:= cast<libc.const_char_t ptr>(cstr.Data) 'mem leak?
	return cstrptr
end

struct Mat4<T> extension

	function LookAt:Mat4<T>( eye:Vec3<T>, target:Vec3<T> = new Vec3<T>(0, 0, 0), up:Vec3<T> = new Vec3<T>(0, 1, 0))
		local k:= (target - eye).Normalize()
		local i:= k.Cross(up).Normalize()
		local j:= i.Cross(k)
		local t:= new Vec4<T>
		
		t.x = -i.x * eye.x - i.y * eye.y - i.z * eye.z
		t.y = -j.x * eye.x - j.y * eye.y - j.z * eye.z
		t.z = -k.x * eye.x - k.y * eye.y - k.z * eye.z
		t.w = 1.0

		local m:= new Mat4<T>()
		m.i = new Vec4<T>(i, 0.0)
		m.j = new Vec4<T>(j, 0.0)
		m.k = new Vec4<T>(k, 0.0)
		m.t = t
		return m
	end

end