
// **** WX_RENDERPASS *****
//
// PASSTYPE		'mask=3,  0=quad, 1=deferred, 2=forward, 3=shadow
// LIGHTTYPE	'mask=12, 0=none, 1=directional, 2=point, 3=spot
// SHADOWTYPE	'mask=16, 0=no shadows, 1=shadows
//
#ifndef WX_RENDERPASS
#define WX_RENDERPASS 0
#endif

#ifndef WX_FORWARDRENDERER
#define WX_FORWARDRENDERER 0
#endif

#ifndef WX_DEFERREDRENDERER
#define WX_DEFERREDRENDERER 0
#endif

#ifndef WX_SRGBOUTPUT
#define WX_SRGBOUTPUT 0
#endif

#define WX_PASSTYPE			((WX_RENDERPASS & 3))
#define WX_LIGHTTYPE			((WX_RENDERPASS & 12)>>2)
#define WX_SHADOWTYPE			((WX_RENDERPASS & 16)>>4)

#define WX_DIRECTIONALLIGHT	(WX_LIGHTTYPE==1)
#define WX_POINTLIGHT			(WX_LIGHTTYPE==2)
#define WX_SPOTLIGHT			(WX_LIGHTTYPE==3)

#define WX_QUADPASS			(WX_PASSTYPE==0)
#define WX_DEFERREDPASS		(WX_PASSTYPE==1)
#define WX_FORWARDPASS			(WX_PASSTYPE==2)
#define WX_SHADOWPASS			(WX_PASSTYPE==3)

#define WX_AMBIENTPASS			(WX_PASSTYPE==1 || WX_PASSTYPE==2)
#define WX_LIGHTINGPASS		(WX_LIGHTTYPE!=0 && WX_SHADOWPASS==0)
#define WX_COLORPASS			(WX_AMBIENTPASS || WX_LIGHTINGPASS)

// ***** WX_ATTRIBMASK *****
//
// Position		1
// Normal		2
// Color		4
// TexCoord0	8
// TexCoord1	16
// Tangent		32
// Weights		64
// Bones		128

#ifndef WX_ATTRIBMASK
#define WX_ATTRIBMASK 0
#endif
#define WX_TEXTURED			((WX_ATTRIBMASK & 24)!=0)
#define WX_BUMPMAPPED			((WX_ATTRIBMASK & 32)==32)
#define WX_BONED				((WX_ATTRIBMASK & 192)==192)

//***** CONSTS *****
//
const float pi=3.1415926535897932384626433832795;

//***** RENDER *****
//
uniform float r_Time;
uniform vec4 r_AmbientDiffuse;

uniform samplerCube r_SkyTextureCube;
uniform sampler2D r_SkyTexture2D;
uniform bool r_SkyCube;
uniform vec4 r_SkyColor;

uniform samplerCube r_EnvTextureCube;
uniform sampler2D r_EnvTexture2D;
uniform bool r_EnvCube;
uniform float r_EnvTextureMaxLod;
uniform vec4 r_EnvColor;
uniform mat3 r_EnvMatrix;

uniform float r_DepthNear;
uniform float r_DepthFar;
uniform float r_FogNear;
uniform float r_FogFar;
uniform vec4 r_FogColor;
uniform mat4 r_InverseProjectionMatrix;
uniform mat4 r_ProjectionMatrix;
uniform mat4 r_ViewMatrix;

// These only available in deferred renderer!
uniform sampler2D r_AccumBuffer;
uniform sampler2D r_ColorBuffer;
uniform sampler2D r_NormalBuffer;
uniform sampler2D r_DepthBuffer;
uniform vec2 r_BufferCoordScale;
uniform vec2 r_QuadCoordScale;
uniform vec2 r_QuadCoordTrans;

//***** LIGHTING *****
//
uniform mat4 r_LightViewMatrix;
uniform mat4 r_InverseLightViewMatrix;
uniform samplerCube r_LightCubeTexture;
uniform sampler2D r_LightTexture;
uniform vec4 r_LightColor;
uniform float r_LightRange;
uniform float r_LightInnerAngle;
uniform float r_LightOuterAngle;

//***** SHADOWS *****
//
uniform sampler2D r_ShadowCSMTexture;
uniform samplerCube r_ShadowCubeTexture;
uniform vec4 r_ShadowCSMSplits;
uniform mat4 r_ShadowMatrix0;
uniform mat4 r_ShadowMatrix1;
uniform mat4 r_ShadowMatrix2;
uniform mat4 r_ShadowMatrix3;
uniform float r_ShadowAlpha;

//***** INSTANCE *****
//
uniform mat4 i_ModelMatrix;
uniform mat4 i_ModelViewMatrix;
uniform mat4 i_ModelViewProjectionMatrix;
uniform mat3 i_ModelViewNormalMatrix;
uniform mat4 i_ModelBoneMatrices[96];
uniform vec4  i_Color;
uniform float i_Alpha;

//***** MATERIAL *****
//
uniform mat3 m_TextureMatrix;

//***** VARYINGS *****
//
varying vec2 v_ClipPosition;
varying vec2 v_BufferCoords;
varying vec3 v_Position;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec2 v_TexCoord0;
varying vec2 v_TexCoord1;
varying mat3 v_TanMatrix;

//@vertex

//***** ATTRIBUTES *****
//
attribute vec4 a_Position;	//mask=1
attribute vec3 a_Normal;	//mask=2
attribute vec4 a_Color;		//mask=4
attribute vec2 a_TexCoord0;	//mask=8
attribute vec2 a_TexCoord1;	//mask=16
attribute vec4 a_Tangent;	//mask=32
attribute vec4 a_Weights;	//mask=64
attribute vec4 a_Bones;		//mask=128

void transformLightQuadVertex(){

	//Careful! Bizarro angle/d3d bug...

	v_ClipPosition=a_Position.xy * r_QuadCoordScale + r_QuadCoordTrans;
	
	v_BufferCoords=v_ClipPosition * r_BufferCoordScale;
	
	gl_Position=vec4( v_ClipPosition * 2.0 - 1.0,-1.0,1.0 );
}

void transformQuadVertex(){

	v_ClipPosition=a_Position.xy;
	
	v_BufferCoords=v_ClipPosition.xy * r_BufferCoordScale;
	
	gl_Position=vec4( v_ClipPosition.xy * 2.0 - 1.0,-1.0,1.0 );
}

void transformSpriteVertex(){

	v_Position=(i_ModelViewMatrix * a_Position).xyz;

	v_TexCoord0=(m_TextureMatrix * vec3(a_TexCoord0,1.0)).st;

	v_Color=a_Color;
	
	gl_Position=i_ModelViewProjectionMatrix * a_Position;
}

void transformVertex(){
 
#if WX_BONED
	mat4 m0=i_ModelBoneMatrices[ int( a_Bones.x ) ];
	mat4 m1=i_ModelBoneMatrices[ int( a_Bones.y ) ];
	mat4 m2=i_ModelBoneMatrices[ int( a_Bones.z ) ];
	mat4 m3=i_ModelBoneMatrices[ int( a_Bones.a ) ];
	
	vec4 position=
		m0 * a_Position * a_Weights.x +
		m1 * a_Position * a_Weights.y +
		m2 * a_Position * a_Weights.z +
		m3 * a_Position * a_Weights.a;
#if WX_COLORPASS
	mat3 n0=mat3( m0[0].xyz,m0[1].xyz,m0[2].xyz );
	mat3 n1=mat3( m1[0].xyz,m1[1].xyz,m1[2].xyz );
	mat3 n2=mat3( m2[0].xyz,m2[1].xyz,m2[2].xyz );
	mat3 n3=mat3( m3[0].xyz,m3[1].xyz,m3[2].xyz );

	vec3 normal=normalize( 
		n0 * a_Normal * a_Weights.x +
		n1 * a_Normal * a_Weights.y +
		n2 * a_Normal * a_Weights.z +
		n3 * a_Normal * a_Weights.a );
#if WX_BUMPMAPPED
	vec4 tangent=vec4( normalize( 
		n0 * a_Tangent.xyz * a_Weights.x +
		n1 * a_Tangent.xyz * a_Weights.y +
		n2 * a_Tangent.xyz * a_Weights.z +
		n3 * a_Tangent.xyz * a_Weights.a ),a_Tangent.w );
#endif
#endif
#else	//WX_BONED
	vec4 position=a_Position;
#if WX_COLORPASS
	vec3 normal=a_Normal;
#if WX_BUMPMAPPED	
	vec4 tangent=a_Tangent;
#endif
#endif
#endif

	// view space position
	v_Position=( i_ModelViewMatrix * position ).xyz;

#if WX_COLORPASS
	// viewspace normal
	v_Normal=i_ModelViewNormalMatrix * normal;
	// vertex color
	v_Color=a_Color * i_Color;
	v_Color.a*=i_Alpha;
#if WX_TEXTURED
	// texture coord0
	v_TexCoord0=(m_TextureMatrix * vec3(a_TexCoord0,1.0)).st;
	v_TexCoord1=a_TexCoord1;//(m_TextureMatrix * vec3(a_TexCoord1,1.0)).st;
#if WX_BUMPMAPPED
	// viewspace tangent matrix
	v_TanMatrix[2]=normalize( v_Normal );
	v_TanMatrix[0]=normalize( i_ModelViewNormalMatrix * tangent.xyz );
	v_TanMatrix[1]=cross( v_TanMatrix[0],v_TanMatrix[2] ) * tangent.a;
#endif
#endif
#endif	//WX_COLORPASS
	
	gl_Position=i_ModelViewProjectionMatrix * position;
}

//@fragment

vec4 FloatToRGBA( float value ){

	const float MaxFloat=0.9999999;
	value=clamp( value,0.0,MaxFloat );
	vec4 rgba=fract( vec4( 1.0, 255.0, 65025.0, 16581375.0 ) * value );
	return rgba-rgba.yzww * vec4( 1.0/255.0, 1.0/255.0, 1.0/255.0, 0.0 );
}

float RGBAToFloat( vec4 rgba ){

	return dot( rgba,vec4( 1.0, 1.0/255.0, 1.0/65025.0, 1.0/16581375.0 ) );
}

float viewDepth( float depthBufferDepth ){

	return r_DepthFar * r_DepthNear / ( r_DepthFar + depthBufferDepth * ( r_DepthNear - r_DepthFar ) );
}

#if WX_QUADPASS

vec3 fragmentPosition(){

	float depth=viewDepth( texture2D( r_DepthBuffer,v_BufferCoords ).r );

	vec4 vpos4=r_InverseProjectionMatrix * vec4( v_ClipPosition*2.0-1.0,-1.0,1.0 );
	
	vec3 vpos=vpos4.xyz/vpos4.w;
	
	//debug z coord...
	//
	if( abs( vpos.z-r_DepthNear)>0.00001 ){
//		gl_FragColor=vec4( 1.0,0.0,0.0,1.0 );
//		return vec3( 0.0 );
	}
	
	vec3 position=vpos/vpos.z*depth;
	
	return position;
}

#else

vec3 fragmentPosition(){

	return v_Position;
}

#endif

#if WX_LIGHTINGPASS && WX_SHADOWTYPE

float shadowColor( vec3 position ){

#if WX_DIRECTIONALLIGHT
 
	if( position.z>=r_ShadowCSMSplits.w ) return 1.0;
	
	vec4 vpos=vec4( position,1.0 );
	vec2 off;
	
	if( vpos.z<r_ShadowCSMSplits.x ){
		vpos=r_ShadowMatrix0 * vpos;
		off=vec2( 0.0,0.0 );
	}else if( vpos.z<r_ShadowCSMSplits.y ){
		vpos=r_ShadowMatrix1 * vpos;
		off=vec2( 0.5,0.0 );
	}else if( vpos.z<r_ShadowCSMSplits.z ){
		vpos=r_ShadowMatrix2 * vpos;
		off=vec2( 0.0,0.5 );
	}else{
		vpos=r_ShadowMatrix3 * vpos;
		off=vec2( 0.5,0.5 );
	}
	
	vec3 spos=vpos.xyz/vpos.w * vec3( 0.25,0.25,0.5 ) + vec3( 0.25,0.25,0.5 );
	
	float d=texture2D( r_ShadowCSMTexture,spos.xy+off ).r;
	
	if( spos.z>d ) return 1.0-r_ShadowAlpha;
	
	return 1.0;
	
#elif WX_POINTLIGHT

	vec4 vpos=vec4( position,1.0 );
	
	vec3 lpos=(r_ShadowMatrix0 * vpos).xyz;
	
	float d=RGBAToFloat( textureCube( r_ShadowCubeTexture,lpos ) );
	
	if( length(lpos) > d * r_LightRange ) return 1.0-r_ShadowAlpha;
	
	return 1.0;
	
#elif WX_SPOTLIGHT

	vec4 vpos=r_ShadowMatrix0 * vec4( position,1.0 );
	
	vec3 spos=vpos.xyz/vpos.w * vec3( 0.25,0.25,0.5 ) + vec3( 0.25,0.25,0.5 );

	float d=texture2D( r_ShadowCSMTexture,spos.xy ).r;
	
	if( spos.z>d ) return 1.0-r_ShadowAlpha;
	
	return 1.0;
	
#endif
}

#endif

/*
float mipmapLod( vec2 tc ){
    vec2 dx=dFdx( tc );
    vec2 dy=dFdy( tc );
    float dsqr=max( dot( dx,dx ),dot( dy,dy ) );
    float lod=log2( dsqr ) * 0.5;
    return max( lod,0.0 );
}

float mipmapLodCube( vec3 tv ){
	vec2 tc;
	vec3 at=abs( tv );
	if( at.x>at.y && at.x>at.z ){
		tc=vec2( tv.y,tv.z )/tv.x;
	}else if( at.y>at.z ){
		tc=vec2( tv.x,tv.z )/tv.y;
	}else{
		tc=vec2( tv.x,tv.y )/tv.z;
	}
	return mipmapLod( (tc+1.0)*0.5 );
}
*/

vec3 sampleEnv( vec3 viewVec,float roughness ){

	vec3 tv=r_EnvMatrix * viewVec;

	if( r_EnvCube ){
		
//#ifdef GL_ES
		float lod=textureCube( r_EnvTextureCube,tv ).a * 255.0;
		if( lod==0.0 ) lod=textureCube( r_EnvTextureCube,tv,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;
		return pow( textureCube( r_EnvTextureCube,tv,max( roughness*r_EnvTextureMaxLod-lod,0.0 ) ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
//#else
//		return pow( textureCube( r_EnvTextureCube,tv,roughness*r_EnvTextureMaxLod ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
//#endif
		
	}else{
	
		float p=-atan( tv.y,sqrt( tv.x*tv.x+tv.z*tv.z ) ) / pi + 0.5;
		float y=atan( tv.x,tv.z ) / pi * 0.5 + 0.5;
		vec2 tc=vec2( y,p );
		
//#ifdef GL_ES
		float lod=texture2D( r_EnvTexture2D,tc ).a * 255.0;
		if( lod==0.0 ) lod=texture2D( r_EnvTexture2D,tc,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;
		return pow( texture2D( r_EnvTexture2D,tc,max( roughness*r_EnvTextureMaxLod-lod,0.0 ) ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
//else
//		return pow( texture2DLod( r_EnvTexture2D,tc,max( mipmapLod( tc ),roughness*r_EnvTextureMaxLod ) ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
	
//#endif
	}
}

#if WX_FORWARDRENDERER || WX_FORWARDPASS

void emitLinearFragment( vec4 color ){

#if WX_SRGBOUTPUT
	gl_FragColor=vec4( pow( color.rgb*color.a,vec3( 1.0/2.2 ) ),color.a );
#else
	gl_FragColor=vec4( color.rgb*color.a,color.a );
#endif
}

void emitColorFragment( vec4 color ){

	float fog=clamp( (length( v_Position )-r_FogNear)/(r_FogFar-r_FogNear),0.0,1.0 ) * r_FogColor.a;
	
	color.rgb=mix( color.rgb,r_FogColor.rgb,fog );
	
	emitLinearFragment( color );
}

#endif

#if WX_SHADOWPASS

void emitShadowFragment(){

#if WX_DIRECTIONALLIGHT || WX_SPOTLIGHT
	gl_FragColor=vec4( vec3( gl_FragCoord.z ),1.0 );
#elif WX_POINTLIGHT
	gl_FragColor=FloatToRGBA( min( length( v_Position )/r_LightRange,1.0 ) );
#endif
}

#endif


