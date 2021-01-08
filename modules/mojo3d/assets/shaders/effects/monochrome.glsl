//@renderpasses 0

uniform sampler2D r_SourceBuffer;
uniform vec2 r_SourceBufferScale;

varying vec2 v_SourceBufferCoords;

//@vertex

attribute vec2 a_Position;
	
void main(){

	v_SourceBufferCoords=a_Position * r_SourceBufferScale;

	gl_Position=vec4( a_Position * 2.0 - 1.0,-1.0,1.0 );
}

//@fragment

uniform float m_Level;

void main(){

	vec4 color=texture2D( r_SourceBuffer,v_SourceBufferCoords );

	float i=(color.r+color.g+color.b)/3.0;
	
	gl_FragColor=vec4( mix( color.rgb,vec3( i ),m_Level ),color.a );
}
