
//@renderpasses 0

varying vec4 v_Color;

//@vertex

attribute vec4 a_Position;
attribute vec4 a_Color;

uniform mat4 r_ModelViewProjectionMatrix;

void main(){

	v_Color=a_Color;
	
	gl_Position=r_ModelViewProjectionMatrix * a_Position;
	
	gl_PointSize=1.0;
}

//@fragment

void main(){

	gl_FragColor=v_Color;
}
