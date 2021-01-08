
//@renderpasses 0

uniform sampler2D r_SourceBuffer;
uniform vec2 r_SourceBufferScale;

varying vec2 v_SourceBufferCoords;

//@vertex

attribute vec2 a_Position;
attribute vec2 a_TexCoord0;

void main(){

	v_SourceBufferCoords=a_TexCoord0 * r_SourceBufferScale;

	gl_Position=vec4( a_Position*2.0-1.0,-1.0,1.0 );
}

//@fragment

void main(){

	gl_FragColor=vec4( pow( texture2D( r_SourceBuffer,v_SourceBufferCoords ).rgb,vec3( 1.0/2.2 ) ),1.0 );
}
