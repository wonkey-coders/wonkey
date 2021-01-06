
//@renderpasses 4,5

varying vec2 v_TexCoord0;
varying vec2 v_LightPos;
varying vec4 v_Color;

varying vec2 v_GBufferCoords;
varying vec2 v_FragPos;

//@vertex

attribute vec4 a_Position;
attribute vec2 a_TexCoord0;
attribute vec2 a_TexCoord1;
attribute vec4 a_Color;

uniform mat4 r_ModelViewMatrix;
uniform mat4 r_ModelViewProjectionMatrix;

uniform vec2 r_ViewportOrigin;
uniform vec2 r_ViewportSize;
uniform vec2 r_ViewportClip;

uniform vec2 r_GBufferScale;

uniform vec4 m_ImageColor;

void main(){

	v_TexCoord0=a_TexCoord0;
	v_LightPos=a_TexCoord1;
	v_FragPos=a_Position.xy;
	v_Color=m_ImageColor * a_Color;

	gl_Position=r_ModelViewProjectionMatrix * a_Position;
	
	vec2 vpcoords=(gl_Position.xy * 0.5 + 0.5) * r_ViewportSize;
	
	v_GBufferCoords=(vpcoords + r_ViewportOrigin) * r_GBufferScale;
}

//@fragment

uniform sampler2D m_ImageTexture0;				//image texture
uniform float m_LightDepth;

uniform sampler2D r_GBuffer0;					//gbuffer diffuse
uniform sampler2D r_GBuffer1;					//gbuffer normal

void main(){

	vec3 normal=texture2D( r_GBuffer1,v_GBufferCoords ).xyz;
	
	float gloss=normal.z;
	
	normal.xy=normal.xy * 2.0 - 1.0;
	
	normal.z=sqrt( 1.0-dot( normal.xy,normal.xy ) );
	
	//diffuse...
	//	
	vec3 lvec=normalize( vec3( v_LightPos-v_FragPos,m_LightDepth ) );
	
	float ndotl=max( dot( normal,lvec ),0.0 );
	
	vec4 tcolor=texture2D( m_ImageTexture0,v_TexCoord0 ) * v_Color;

	vec4 diffuse=texture2D( r_GBuffer0,v_GBufferCoords ) * tcolor * ndotl;
	
	//specular...
	//
	vec3 hvec=normalize( lvec+vec3( 0.0,0.0,1.0 ) );
	
	float ndoth=max( dot( normal,hvec ),0.0 );
	
	vec4 specular=tcolor * pow( ndoth,128.0 ) * gloss;
	
#if WX_RENDERPASS==5

	float shadow=texture2D( r_GBuffer0,v_GBufferCoords ).a;
	
	diffuse*=shadow;
	
	specular*=shadow;

#endif
	
	//tada!
	//
	gl_FragColor=vec4( diffuse.rgb+vec3( specular.a ),0.0 );
}
