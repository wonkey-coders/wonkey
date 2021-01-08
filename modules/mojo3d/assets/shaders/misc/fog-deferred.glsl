
//@renderpasses 0

//@import "std"

//@vertex

void main(){

	transformQuadVertex();
}

//@fragment

void main(){

	float fog=0.0;

	float depth=texture2D( r_DepthBuffer,v_BufferCoords ).r;
	
	if( depth<1.0 ){

		depth=viewDepth( depth );
		
		vec4 vpos4=r_InverseProjectionMatrix * vec4( v_ClipPosition*2.0-1.0,-1.0,1.0 );
		
		vec3 vpos=vpos4.xyz/vpos4.w;
		
		vec3 position=vpos/vpos.z*depth;
		
		fog=clamp( (length( position )-r_FogNear)/(r_FogFar-r_FogNear),0.0,1.0 ) * r_FogColor.a;
	}
	
	gl_FragColor=vec4( r_FogColor.rgb * fog,fog );
}
