
//@renderpasses 0,1,2

varying vec2 v_TexCoord0;
varying mat2 v_TanMatrix;
varying vec4 v_Color;

//@vertex

attribute vec4 a_Position;
attribute vec2 a_TexCoord0;
attribute vec2 a_TexCoord1;
attribute vec4 a_Color;

uniform mat4 r_ModelViewProjectionMatrix;

uniform vec4 r_AmbientLight;

uniform vec4 m_ImageColor;

void main(){

	v_TexCoord0=a_TexCoord0;

#if WX_RENDERPASS==2

	v_TanMatrix=mat2( a_TexCoord1.x,a_TexCoord1.y,-a_TexCoord1.y,a_TexCoord1.x );
	
#endif

#if WX_RENDERPASS==0

	v_Color=r_AmbientLight * m_ImageColor * a_Color;
	
#else

	v_Color=m_ImageColor * a_Color;
	
#endif
	
	gl_Position=r_ModelViewProjectionMatrix * a_Position;
}

//@fragment

uniform sampler2D m_ImageTexture0;

uniform sampler2D m_ImageTexture1;

void main(){

	vec4 diffuse=texture2D( m_ImageTexture0,v_TexCoord0 ) * v_Color;

#if WX_RENDERPASS==0		//ambient

	gl_FragColor=diffuse;

#elif WX_RENDERPASS==1		//diffuse

	gl_FragColor=diffuse;
	
#elif WX_RENDERPASS==2		//normal

	vec3 normal=texture2D( m_ImageTexture1,v_TexCoord0 ).xyz;
	
	normal.xy=v_TanMatrix * (normal.xy * 2.0 - 1.0) * 0.5 + 0.5;

	gl_FragColor=vec4( normal*diffuse.a,diffuse.a );

#endif

}
