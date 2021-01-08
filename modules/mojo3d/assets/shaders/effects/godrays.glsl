
//@renderpasses 0

uniform sampler2D r_SourceBuffer;

uniform sampler2D r_DepthBuffer;

uniform vec2 r_BufferCoordScale;

varying vec2 v_BufferCoords;

//@vertex

attribute vec4 a_Position;
	
void main(){

	v_BufferCoords=a_Position.xy * r_BufferCoordScale;

	gl_Position=vec4( a_Position.xy * 2.0 - 1.0,0.0,1.0 );
}

//@fragment

uniform vec2 m_LightPosBufferCoords;

#ifdef GL_ES
const int m_NumSamples=100;
#else
uniform int m_NumSamples;
#endif

uniform float m_Exposure;

uniform float m_Decay;

uniform float m_Density;

uniform vec4 m_Color;

uniform float m_Weight;

void main(){

	vec2 coords=v_BufferCoords;

	vec2 delta=m_LightPosBufferCoords-coords;
	
	delta*=1.0/float( m_NumSamples ) * m_Density;
	
	vec3 fragColor=vec3( 0.0 );
	
	vec3 color=m_Color.rgb * m_Weight;
	
	for( int i=0;i<m_NumSamples;++i ){
	
		coords+=delta;

		float depth=texture2D( r_DepthBuffer,coords ).r;
		
		vec3 sample=(depth==1.0) ? color : vec3( 0.0 );
		
		fragColor+=sample;
	}
	
	gl_FragColor=vec4( fragColor * m_Exposure,1.0 );

/*
	float depth=texture2D( r_DepthBuffer,v_BufferCoords ).r;
	
//	depth=1.0;
	
//	gl_FragColor=vec4( v_BufferCoords,0.0,1.0 );

	gl_FragColor=vec4( depth,0.0,0.0,1.0 );
*/
}
