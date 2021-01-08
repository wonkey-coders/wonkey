
//@renderpasses 0,1,2,3

uniform sampler2D r_SourceBuffer;
uniform vec2 r_SourceBufferSize;
uniform vec2 r_SourceBufferScale;

varying vec2 v_TexCoord0;

//@vertex

attribute vec2 a_Position;	//0...1 (1=viewport size)

void main(){

	v_TexCoord0=a_Position * r_SourceBufferScale;

	gl_Position=vec4( a_Position * 2.0 - 1.0,-1.0,1.0 );
}

//@fragment

const float weight0=0.227027,weight1=0.1945946,weight2=0.1216216,weight3=0.054054,weight4=0.016216;

//apparently the same if linear filter enabled in texture...
//const float weight0=0.2270270270,weight1=0.3162162162,weight2=0.0702702703;

void main(){

#if WX_RENDERPASS==3

	vec3 result=texture2D( r_SourceBuffer,v_TexCoord0 ).rgb;

#else

	vec2 texel_size=1.0/r_SourceBufferSize;
	
	vec3 result=texture2D( r_SourceBuffer,v_TexCoord0 ).rgb*weight0;
	
#if WX_RENDERPASS==0 || WX_RENDERPASS==2

	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(texel_size.x*1.0,0.0)).rgb * weight1;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(texel_size.x*1.0,0.0)).rgb * weight1;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(texel_size.x*2.0,0.0)).rgb * weight2;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(texel_size.x*2.0,0.0)).rgb * weight2;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(texel_size.x*3.0,0.0)).rgb * weight3;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(texel_size.x*3.0,0.0)).rgb * weight3;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(texel_size.x*4.0,0.0)).rgb * weight4;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(texel_size.x*4.0,0.0)).rgb * weight4;
	
#elif WX_RENDERPASS==1

	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(0.0,texel_size.y*1.0)).rgb * weight1;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(0.0,texel_size.y*1.0)).rgb * weight1;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(0.0,texel_size.y*2.0)).rgb * weight2;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(0.0,texel_size.y*2.0)).rgb * weight2;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(0.0,texel_size.y*3.0)).rgb * weight3;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(0.0,texel_size.y*3.0)).rgb * weight3;
	result+=texture2D(r_SourceBuffer,v_TexCoord0+vec2(0.0,texel_size.y*4.0)).rgb * weight4;
	result+=texture2D(r_SourceBuffer,v_TexCoord0-vec2(0.0,texel_size.y*4.0)).rgb * weight4;

#endif

#if WX_RENDERPASS==0

	result=max( result-1.0,0.0 );
	
#endif

#endif
	
	gl_FragColor=vec4( result,1.0 );
	
}
