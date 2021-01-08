
// ***** alpha surface shader *****

varying vec4 Color;

varying vec2 TexCoord0;

//@vertex

void transform( out vec4 viewpos ){

	viewpos=mx2_ModelViewMatrix * mx2_VertexPosition;
	
	Color=mx2_VertexColor * mx2_RenderColor;
	
	TexCoord0=mx2_VertexTexCoord0;
}

//@fragment

uniform sampler2D u_Texture0;

void ambientPass( out vec4 ambient ){

	ambient=vec4( texture2D( u_Texture0,TexCoord0 ).a ) * Color;
}

void lightingPass( out vec4 diffuse,out vec4 specular,out vec3 normal ){

}

