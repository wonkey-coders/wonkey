
//@renderpasses 2,6,10

//@import "std"

//@vertex

void main(){

	transformSpriteVertex();
}

//@fragment

uniform sampler2D m_ColorTexture;
uniform vec4 m_ColorFactor;
uniform float m_AlphaDiscard;

void main(){

	vec4 color=texture2D( m_ColorTexture,v_TexCoord0 ) * m_ColorFactor * v_Color;
	
	if( color.a<m_AlphaDiscard ) discard;
		
	emitColorFragment( color );
}
