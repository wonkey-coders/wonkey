namespace sokol.samples

#import "<libc>"
#import "<std>"
#import "<sokol>"

using std.memory..
using std.geom..
using sokol..

const MSAA_SAMPLES:= 4

struct state_t
	field pip:sg_pipeline
	field bind:sg_bindings
	field pass:sg_pass
	field pass_action:sg_pass_action
end

global defaults:= new state_t
global offscreen:= new state_t

'/* rotation angles */
global rx:float, ry:float

struct vs_params_t
	field mvp:Mat4f '4x4
end

function Main()
	local desc:sapp_desc
	desc.window_title = CStr("sokol-offscreen")
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
	
	'/* a default pass action to framebuffer to gray */
	defaults.pass_action.colors[0].action = SG_ACTION_CLEAR
	defaults.pass_action.colors[0].val[0] = 0.12
	defaults.pass_action.colors[0].val[1] = 0.12
	defaults.pass_action.colors[0].val[2] = 0.2
	defaults.pass_action.colors[0].val[3] = 1.0
		
	'/* a offscreen pass action to framebuffer to blacks */
	offscreen.pass_action.colors[0].action = SG_ACTION_CLEAR
	offscreen.pass_action.colors[0].val[0] = 0.5
	offscreen.pass_action.colors[0].val[1] = 0.5
	offscreen.pass_action.colors[0].val[2] = 0.5
	offscreen.pass_action.colors[0].val[3] = 1.0
	
	'/* a render pass with one color- and one depth-attachment image */
	local img_desc:sg_image_desc
	img_desc.render_target = true
	img_desc.width = 256
	img_desc.height = 256
	img_desc.pixel_format = SG_PIXELFORMAT_RGBA8
	img_desc.min_filter = SG_FILTER_LINEAR
	img_desc.mag_filter = SG_FILTER_LINEAR
	img_desc.sample_count = MSAA_SAMPLES
	img_desc.label = CStr("color-image")
	
	local color_img:sg_image = sg_make_image(varptr img_desc)
	
	img_desc.pixel_format = SG_PIXELFORMAT_DEPTH
	img_desc.label = CStr("depth-image")
	
	local depth_img:sg_image = sg_make_image(varptr img_desc)
	
	local pass_desc:sg_pass_desc
	pass_desc.color_attachments[0].image = color_img
	pass_desc.depth_stencil_attachment.image = depth_img
	pass_desc.label = CStr("offscreen-pass")
	offscreen.pass = sg_make_pass(varptr pass_desc)
	

	'/* cube vertex buffer with positions, colors and tex coords */
	local vertices:= new float[](
		'/* pos              color                   uvs */
		-1.0, -1.0, -1.0,    1.0, 0.5, 0.5, 1.0,     0.0, 0.0,
         1.0, -1.0, -1.0,    1.0, 0.5, 0.5, 1.0,     1.0, 0.0,
         1.0,  1.0, -1.0,    1.0, 0.5, 0.5, 1.0,     1.0, 1.0,
        -1.0,  1.0, -1.0,    1.0, 0.5, 0.5, 1.0,     0.0, 1.0,

        -1.0, -1.0,  1.0,    0.5, 1.0, 0.5, 1.0,     0.0, 0.0,
         1.0, -1.0,  1.0,    0.5, 1.0, 0.5, 1.0,     1.0, 0.0,
         1.0,  1.0,  1.0,    0.5, 1.0, 0.5, 1.0,     1.0, 1.0,
        -1.0,  1.0,  1.0,    0.5, 1.0, 0.5, 1.0,     0.0, 1.0,

        -1.0, -1.0, -1.0,    0.5, 0.5, 1.0, 1.0,     0.0, 0.0,
        -1.0,  1.0, -1.0,    0.5, 0.5, 1.0, 1.0,     1.0, 0.0,
        -1.0,  1.0,  1.0,    0.5, 0.5, 1.0, 1.0,     1.0, 1.0,
        -1.0, -1.0,  1.0,    0.5, 0.5, 1.0, 1.0,     0.0, 1.0,

         1.0, -1.0, -1.0,    1.0, 0.5, 0.0, 1.0,     0.0, 0.0,
         1.0,  1.0, -1.0,    1.0, 0.5, 0.0, 1.0,     1.0, 0.0,
         1.0,  1.0,  1.0,    1.0, 0.5, 0.0, 1.0,     1.0, 1.0,
         1.0, -1.0,  1.0,    1.0, 0.5, 0.0, 1.0,     0.0, 1.0,

        -1.0, -1.0, -1.0,    0.0, 0.5, 1.0, 1.0,     0.0, 0.0,
        -1.0, -1.0,  1.0,    0.0, 0.5, 1.0, 1.0,     1.0, 0.0,
         1.0, -1.0,  1.0,    0.0, 0.5, 1.0, 1.0,     1.0, 1.0,
         1.0, -1.0, -1.0,    0.0, 0.5, 1.0, 1.0,     0.0, 1.0,

        -1.0,  1.0, -1.0,    1.0, 0.0, 0.5, 1.0,     0.0, 0.0,
        -1.0,  1.0,  1.0,    1.0, 0.0, 0.5, 1.0,     1.0, 0.0,
         1.0,  1.0,  1.0,    1.0, 0.0, 0.5, 1.0,     1.0, 1.0,
         1.0,  1.0, -1.0,    1.0, 0.0, 0.5, 1.0,     0.0, 1.0)
		
	local vb:sg_buffer_desc
	vb.size = vertices.Length * libc.sizeof<float>()
	vb.content = vertices.Data
	vb.label = CStr("cube-vertices")
	vb.type = SG_BUFFERTYPE_VERTEXBUFFER
	
	
	'/* an index buffer for the cube */
	local indices:= new ushort[](
		0, 1, 2, 0, 2, 3,
		6, 5, 4, 7, 6, 4,
		8, 9, 10, 8, 10, 11,
		14, 13, 12,	15, 14, 12,
		16, 17, 18,	16, 18, 19,
		22, 21, 20,	23, 22, 20)
		
	local ib:sg_buffer_desc
	ib.size = indices.Length * libc.sizeof<ushort>()
	ib.content = indices.Data
	ib.label = CStr("cube-indices")
	ib.type = SG_BUFFERTYPE_INDEXBUFFER
	
	'/* create offscreen shader */
	local opp:sg_pipeline_desc, shoff:sg_shader_desc
	shoff.label = CStr("offscreen-shader")
	
#if __TARGET__="macos"
	'/* metal shader format */
	shoff.vs.uniform_blocks[0].size = 64
	shoff.vs.source = CStr(
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
	
	shoff.fs.source = CStr(
		"#include <metal_stdlib>~n"+
		"using namespace metal;~n"+
		"fragment float4 _main(float4 color [[stage_in]]) {~n"+
		"	return color;~n"+
		"};~n")
	
#else
	'/* glsl330 shader format */
	shoff.attrs[0].name = CStr("position")
	shoff.attrs[1].name = CStr("color0")
	shoff.vs.entry = CStr("main")
	shoff.vs.uniform_blocks[0].size = 64
	shoff.vs.uniform_blocks[0].uniforms[0].name = CStr("vs_params")
	shoff.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4
	shoff.vs.uniform_blocks[0].uniforms[0].array_count = 4
	shoff.vs.source = CStr(
		"#version 330~n"+
		"uniform vec4 vs_params[4];~n"+
		"in vec4 position;~n"+
		"in vec4 color0;~n"+
		"out vec4 color;~n"+
		"void main() {~n"+
		"  gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * position;~n"+
		"  color = color0;~n"+
		"}~n")
	shoff.fs.entry = CStr("main")
	shoff.fs.source = CStr(
		"#version 330~n"+
		"in vec4 color;~n"+
		"out vec4 frag_color;~n"+
		"void main() {~n"+
		"  frag_color = color;~n"+
		"}~n")
#end

	'/* pipeline-state-object for offscreen-rendered cube, don't need texture coord here */
	opp.shader = sg_make_shader(varptr shoff)
	opp.label = CStr("offscreen-pipeline")
	opp.index_type = SG_INDEXTYPE_UINT16

	'/* need to provide stride, because the buffer's texcoord is skipped */
	opp.layout.buffers[0].stride = 36
	
	'/* but don't need to provide attr offsets, because pos and color are continuous */
	opp.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3 '0=position
	opp.layout.attrs[1].format = SG_VERTEXFORMAT_UBYTE4N '1=color0
	
	'// depth/stencil
	opp.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL
	opp.depth_stencil.depth_write_enabled = true
	
	'// blend
	opp.blend.color_format = SG_PIXELFORMAT_RGBA8
	opp.blend.depth_format = SG_PIXELFORMAT_DEPTH
	
	'// rasterizer
	opp.rasterizer.cull_mode = SG_CULLMODE_BACK
	opp.rasterizer.sample_count = MSAA_SAMPLES
	
	offscreen.pip = sg_make_pipeline(varptr opp)
	offscreen.bind.vertex_buffers[0] = sg_make_buffer(varptr vb)
	offscreen.bind.index_buffer = sg_make_buffer(varptr ib)
	
	'/* and another pipeline-state-object for the default pass */
	local dpp:sg_pipeline_desc, shdef:sg_shader_desc
	
	'/* create default shader */
	shdef.label = CStr("default-shader")
	
#if __TARGET__="macos"
	'/* metal shader format */
	shdef.vs.uniform_blocks[0].size = 64
	shdef.vs.source = CStr(
		"#include <metal_stdlib>~n"+
		"using namespace metal;~n"+
		"struct params_t {~n"+
		"  float4x4 mvp;~n"+
		"};~n"+
		"struct vs_in {~n"+
		"  float4 position [[attribute(0)]];~n"+
		"  float4 color [[attribute(1)]];~n"+
		"  float2 uv [[attribute(2)]];~n"+
		"};~n"+
		"struct vs_out {~n"+
		"  float4 pos [[position]];~n"+
		"  float4 color;~n"+
		"  float2 uv;~n"+
		"};~n"+
		"vertex vs_out _main(vs_in in [[stage_in]], constant params_t& params [[buffer(0)]]) {~n"+
		"  vs_out out;~n"+
		"  out.pos = params.mvp * in.position;~n"+
		"  out.color = in.color;~n"+
		"  out.uv = in.uv;~n"+
		"  return out;~n"+
		"}~n")
	shdef.fs.source = CStr(
		"#include <metal_stdlib>~n"+
		"using namespace metal;~n"+
		"struct fs_in {~n"+
		"  float4 color;~n"+
		"  float2 uv;~n"+
		"};~n"+
		"fragment float4 _main(fs_in in [[stage_in]],~n"+
		"  texture2d<float> tex [[texture(0)]],~n"+
		"  sampler smp [[sampler(0)]])~n"+
		"{~n"+
		"  return float4(tex.sample(smp, in.uv).xyz + in.color.xyz * 0.5, 1.0);~n"+
		"};~n")
	
#else
	'/* glsl330 shader format */
	shdef.attrs[0].name = CStr("position")
	shdef.attrs[1].name = CStr("color0")
	shdef.attrs[2].name = CStr("texcoord0")
	shdef.vs.entry = CStr("main")
	shdef.vs.uniform_blocks[0].size = 64
	shdef.vs.uniform_blocks[0].uniforms[0].name = CStr("vs_params")
	shdef.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4
	shdef.vs.uniform_blocks[0].uniforms[0].array_count = 4
	shdef.vs.source = CStr(
		"#version 330~n"+
		"uniform vec4 vs_params[4];~n"+
		"in vec4 position;~n"+
		"in vec4 color0;~n"+
		"in vec2 texcoord0;~n"+
		"out vec4 color;~n"+
		"out vec2 uv;~n"+
		"void main() {~n"+
		"  gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * position;~n"+
		"  color = color0;~n"+
		"  uv = texcoord0;~n"+
		"}~n")
	shdef.fs.entry = CStr("main")
	shdef.fs.source = CStr(
		"#version 330~n"+
		"uniform sampler2D tex;~n"+
		"in vec4 color;~n"+
		"in vec2 uv;~n"+
		"out vec4 frag_color;~n"+
		"void main() {~n"+
		"  frag_color = texture(tex, uv) + (color * 0.8);~n"+
		"}~n")
#end

	shdef.fs.images[0].name = CStr("tex")
	shdef.fs.images[0].type = SG_IMAGETYPE_2D
	
	dpp.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3 '0=position
	dpp.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4 '1=color0
	dpp.layout.attrs[2].format = SG_VERTEXFORMAT_FLOAT2 '2=texcoord0
	dpp.shader = sg_make_shader(varptr shdef)
	dpp.index_type = SG_INDEXTYPE_UINT16
	dpp.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL
	dpp.depth_stencil.depth_write_enabled = true
	dpp.rasterizer.cull_mode = SG_CULLMODE_BACK
	dpp.rasterizer.sample_count = MSAA_SAMPLES
	dpp.label = CStr("default-pipeline")
	
	defaults.pip = sg_make_pipeline(varptr dpp)
	defaults.bind.vertex_buffers[0] = sg_make_buffer(varptr vb)
	defaults.bind.index_buffer = sg_make_buffer(varptr ib)
	defaults.bind.fs_images[0] = color_img
end

function frame:void()
	
	'/* compute model-view-projection matrix for vertex shader, this will be
	'   used both for the offscreen-pass, and the display-pass */
	local w:= sapp_width()
	local h:= sapp_height()

	local proj:= Mat4f.Perspective(60, float(w) / float(h), 0.01, 100.0)
	local view:= Mat4f.LookAt(new Vec3f(0.0, 1.5, 6.0))
	local view_proj:= proj * view
	
	rx+= .01
	ry+= .02
	local model:= Mat4f.Rotation(rx, ry, 0.0)

	local vs_params:vs_params_t
	vs_params.mvp = view_proj * model

	'/* the offscreen pass, rendering an rotating, untextured cube into a render target image */
	sg_begin_pass(offscreen.pass, varptr offscreen.pass_action)
	sg_apply_pipeline(offscreen.pip)
	sg_apply_bindings(varptr offscreen.bind)
	sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, varptr vs_params, libc.sizeof<vs_params_t>(vs_params))
	sg_draw(0, 36, 1)
	sg_end_pass()
	
	'/* and the display-pass, rendering a rotating, textured cube, using the
	'   previously rendered offscreen render-target as texture */
	sg_begin_default_pass(varptr defaults.pass_action, w, h)
	sg_apply_pipeline(defaults.pip)
	sg_apply_bindings(varptr defaults.bind)
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