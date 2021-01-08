
//@renderpasses 1,7,11,15,2,6,10,14,22,26,30

//@import "pbr"

//@vertex

void main(){

	transformVertex();
}

//@fragment

#if WX_COLORPASS	//is this a color pass?

#if WX_TEXTURED
uniform sampler2D m_ColorTexture;
uniform sampler2D m_AmbientTexture;
uniform sampler2D m_EmissiveTexture;
uniform sampler2D m_MetalnessTexture;
uniform sampler2D m_RoughnessTexture;
uniform sampler2D m_OcclusionTexture;
#if WX_BUMPMAPPED
uniform sampler2D m_NormalTexture;
#endif
#endif

uniform vec4 m_ColorFactor;
uniform vec4 m_AmbientFactor;
uniform vec4 m_EmissiveFactor;
uniform float m_MetalnessFactor;
uniform float m_RoughnessFactor;

void main(){

#if WX_TEXTURED
	vec4 color=texture2D( m_ColorTexture,v_TexCoord0 );
	color.rgb=pow( color.rgb,vec3( 2.2 ) );
	color*=m_ColorFactor;
	
	vec3 ambient=pow( texture2D( m_AmbientTexture,v_TexCoord1 ).rgb,vec3( 2.2 ) ) * m_AmbientFactor.rgb;
	
	vec3 emissive=pow( texture2D( m_EmissiveTexture,v_TexCoord0 ).rgb,vec3( 2.2 ) ) * m_EmissiveFactor.rgb;
	
	float metalness=texture2D( m_MetalnessTexture,v_TexCoord0 ).b * m_MetalnessFactor;
	
	float roughness=texture2D( m_RoughnessTexture,v_TexCoord0 ).g * m_RoughnessFactor;
	
	float occlusion=texture2D( m_OcclusionTexture,v_TexCoord0 ).r;
	
#if WX_BUMPMAPPED
	vec3 normal=texture2D( m_NormalTexture,v_TexCoord0 ).xyz * 2.0 - 1.0;
	normal=normalize( v_TanMatrix * normal );
#else
	vec3 normal=normalize( v_Normal );
#endif

#else	//untextured...

	vec4 color=m_ColorFactor;
	
	vec3 ambient=m_AmbientFactor.rgb;
	
	vec3 emissive=m_EmissiveFactor.rgb;
	
	float metalness=m_MetalnessFactor;
	
	float roughness=m_RoughnessFactor;
	
	float occlusion=1.0;
	
	vec3 normal=normalize( v_Normal );
#endif

	emitPbrFragment( color,ambient,emissive,metalness,roughness,occlusion,normal );
}

#else	//if not a color pass, must be a shadow pass...

void main(){

	emitShadowFragment();
}

#endif
