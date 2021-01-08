
//@renderpasses 0

//@import "std"

//@vertex

void main(){

	transformQuadVertex();
}

//@fragment

void main(){

	vec4 clip=r_InverseProjectionMatrix * vec4( v_ClipPosition*2.0-1.0,1.0,1.0 );
	
	vec3 tv=r_EnvMatrix * (clip.xyz/clip.w);
	
	vec3 frag;

	if( r_SkyCube ){

		frag=pow( textureCube( r_SkyTextureCube,tv ).rgb,vec3( 2.2 ) );

	}else{

		float p=-atan( tv.y,sqrt( tv.x*tv.x+tv.z*tv.z ) ) / pi + 0.5;
		
		float y=atan( tv.x,tv.z ) / pi * 0.5 + 0.5;
		
		frag=pow( texture2D( r_SkyTexture2D,vec2( y,p ) ).rgb,vec3( 2.2 ) );
	}
	
	frag*=r_SkyColor.rgb;
	
#if WX_DEFERREDRENDERER
	gl_FragData[0]=vec4( frag,1.0 );					//accum
	gl_FragData[1]=vec4( 0.0,0.0,0.0,1.0 );				//color_m
	gl_FragData[2]=vec4( 0.5,0.5,0.5,1.0 );				//normal_r
#else
	emitLinearFragment( vec4( frag,1.0 ) );
#endif
}
