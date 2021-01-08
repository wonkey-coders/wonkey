
// ***** alpha surface shader *****

varying vec4 Color;

//@vertex

void transform( out vec4 viewpos ){

	viewpos=mx2_ModelViewMatrix * mx2_VertexPosition;
	
	Color=mx2_VertexColor * mx2_RenderColor;
}

//@fragment

void ambientPass( out vec4 ambient ){

	ambient=Color;
}

void lightingPass( out vec4 diffuse,out vec4 specular,out vec3 normal ){

}

