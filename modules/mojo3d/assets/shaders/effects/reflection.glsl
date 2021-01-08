
TODO

//@renderpasses 0

//based on code by 'cireneikual' found at www.opengl.org - thanks!

//current accum buffer
uniform sampler2D r_SourceBuffer;
uniform vec2 r_SourceBufferSize;
uniform vec2 r_SourceBufferScale;

//deferred buffers
uniform sampler2D r_ColorBuffer;
uniform sampler2D r_NormalBuffer;
uniform sampler2D r_DepthBuffer;
uniform vec2 r_BufferCoordScale;

varying vec2 v_SourceCoords;
varying vec2 v_BufferCoords;

//@vertex

attribute vec2 a_Position;

void main(){

	v_SourceCoords=a_Position * r_SourceBufferScale;
	v_BufferCoords=a_Position * r_BufferCoordScale;

	gl_Position=vec4( a_Position * 2.0 - 1.0,-1.0,1.0 );
}

//@fragment

// Consts should help improve performance
const float rayStep = 0.25;
const float minRayStep = 0.1;
const float searchDist = 5.0;
const float searchDistInv = 0.2;

const float maxDDepth = 1.0;
const float maxDDepthInv = 1.0;

const float reflectionSpecularFalloffExponent = 3.0;

const int maxSteps = 20;
const int numBinarySearchSteps = 5;
  
float fragmentDepth( vec2 projCoord ){

	float dbdepth=texture2D( r_DepthBuffer,projCoord * r_BufferCoordScale ).r;
        
	return viewDepth( dbdepth );
}

vec2 projectedCoord( vec3 hitCoord ){

	vec4 projCoord = r_ProjectonMatrix * vec4( hitCoord,1.0 );
	
	projCoord.xy = projCoord.xy / projCoord.w * 0.5 + 0.5;
	
	return projCoord.xy;
}
 
vec3 binarySearch( vec3 dir,inout vec3 hitCoord,out float dDepth ){

	float depth;
 
    for( int i=0;i<numBinarySearchSteps; ++i ){
    
    	vec2 projCoord=projectedCoord( hitCoord );
        
        depth=fragmentDepth( projCoord );
 
        dDepth=hitCoord.z-depth;
        
        if( dDepth>0.0 ) hitCoord+=dir;
	        
        dir*=0.5;
        
        hitCoord-=dir;
    }
 
	vec2 projCoord=projectedCoord( hitCoord );
 
	return vec3( projCoord.xy,depth );
}
 
 
vec4 rayCast( vec3 dir,inout vec3 hitCoord,out float dDepth ){

    dir*=rayStep;
 
    for( int i=0;i<maxSteps;++i ){
    
    	hitCoord+=dir;
    	
        vec2 projCoord=projectedCoord( hitCoord );
        
        float depth=fragmentDepth( projCoord );
        
        dDepth=hitCoord.z-depth;
        
        if( dDepth<0.0 ) return vec4( binarySearch( dir,hitCoord,dDepth ),1.0 );
    }
 
    return vec4( 0.0 );
}
 
 
void main(){

	vec4 normal_r=texture2D( r_NormalBuffer,v_BufferCoords );
	
	if( normal_r.a==1.0 ){
		gl_FragColor=vec4( 0.0 );
		return;
	}
	
	vec3 position=fragmentPosition();
	
	vec3 reflected=normalize( reflect( normalize( position ),normalize( normal_r.rgb ) ) );
	
  // Ray cast
  
    vec3 hitPos=viewPos;
    float dDepth;
 
    vec4 coords=rayCast( reflected * max(minRayStep, -viewPos.z), hitPos, dDepth );
 
    vec2 dCoords = abs( vec2(0.5, 0.5)-coords.xy );
 
    float screenEdgefactor = clamp( 1.0-( dCoords.x + dCoords.y ),0.0,1.0 );
    
    vec3  color=texture2D( r_ColorBuffer,coords.xy * r_BufferCoordScale ).rgb;
    
	float alpha=
	
	pow( specular, reflectionSpecularFalloffExponent ) *
	screenEdgefactor * 
	clamp( -reflected.z, 0.0, 1.0 ) *
	clamp( ( searchDist-length( viewPos-hitPos )) * searchDistInv,0.0,1.0) *
	coords.w );
 
    gl_FragColor=vec4( color*alpha,alpha );
}
