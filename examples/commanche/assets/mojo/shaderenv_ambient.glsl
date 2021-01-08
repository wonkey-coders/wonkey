
// ***** ambient shaderenv *****

uniform mat4 mx2_ModelViewMatrix;
uniform mat4 mx2_ProjectionMatrix;
uniform vec4 mx2_AmbientLight;
uniform vec4 mx2_RenderColor;

//@vertex

attribute vec4 mx2_VertexPosition;
attribute vec2 mx2_VertexTexCoord0;
attribute vec2 mx2_VertexTangent;
attribute vec4 mx2_VertexColor;

void transform( out vec4 viewpos );

void main(){

	vec4 position;
	
	transform( position );
	
	gl_Position=mx2_ProjectionMatrix * position;
}

//@fragment

void ambientPass( out vec4 ambient );

void main(){

	vec4 ambient;
	
	ambientPass( ambient );
	
	gl_FragColor=ambient;
}
