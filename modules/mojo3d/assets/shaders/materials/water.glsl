
//@renderpasses 1

//@import "pbr"

//@vertex

void main(){

	transformVertex();
}

//@fragment

uniform sampler2D m_ColorTexture;
uniform vec4 m_ColorFactor;

uniform float m_Metalness;
uniform float m_Roughness;

uniform sampler2D m_NormalTexture0;
uniform sampler2D m_NormalTexture1;

uniform vec2 m_Velocity0;
uniform vec2 m_Velocity1;

void main(){

	vec4 color=texture2D( m_ColorTexture,v_TexCoord0 );
	color.rgb=pow( color.rgb,vec3( 2.2 ) );
	color*=m_ColorFactor;

	vec3 normal0=texture2D( m_NormalTexture0,v_TexCoord0 + m_Velocity0 * r_Time ).xyz * 2.0 - 1.0;
	
	vec3 normal1=texture2D( m_NormalTexture1,v_TexCoord0 + m_Velocity1 * r_Time ).xyz * 2.0 - 1.0;
	
	vec3 normal=normalize( v_TanMatrix * vec3( normal0+normal1 ) );
	
	vec3 ambient=vec3( 0.0 );
	
	vec3 emissive=vec3( 0.0 );
	
	float metalness=0.0;
	
	float roughness=0.0;
	
	float occlusion=1.0;

	emitPbrFragment( color,ambient,emissive,metalness,roughness,occlusion,normal );
}
