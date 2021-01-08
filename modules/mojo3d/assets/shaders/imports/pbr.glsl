
//@import "std"

//@vertex

//@fragment

float pointAtten( float d,float r ){

//	float atten=1.0-min( (d*d)/(r*r),1.0 );atten*=atten;

	float atten=1.0-min( d/r,1.0 );atten*=atten;
	
//	float atten=1.0/(1.0+d*d);

	return atten;
}

#if WX_QUADPASS && WX_LIGHTINGPASS

void emitPbrFragment( vec3 color,float metalness,float roughness,vec3 position,vec3 normal ){

	float glosiness=1.0-roughness;
	vec3 color0=vec3( 0.04,0.04,0.04 );
	vec3 diffuse=color * (1.0-metalness);
	vec3 specular=(color-color0) * metalness + color0;
	
#if WX_DIRECTIONALLIGHT

	vec3 lvec=normalize( -r_LightViewMatrix[2].xyz );

	float atten=1.0;
	
#elif WX_POINTLIGHT

	vec3 lvec=r_LightViewMatrix[3].xyz-position;

	float atten=pointAtten( length( lvec ),r_LightRange );
	
	lvec=normalize( lvec );
	
#elif WX_SPOTLIGHT

	vec3 lvec=r_LightViewMatrix[3].xyz-position;
	
	float atten=pointAtten( length( lvec ),r_LightRange );
	
	lvec=normalize( lvec );
	
	float cosangle=dot( -lvec,r_LightViewMatrix[2].xyz );
	if( cosangle<0.0 ) return;				//behind spotlight direction
	
	float angle=acos( cosangle );
	if( angle>r_LightOuterAngle ) return;	//outside outer cone

	atten*=1.0-max( (angle-r_LightInnerAngle)/(r_LightOuterAngle-r_LightInnerAngle),0.0 );
	
#endif

	vec3 vvec=normalize( -position );
	vec3 hvec=normalize( lvec+vvec );

	float hdotl=max( dot( hvec,lvec ),0.0 );
	float ndotl=max( dot( normal,lvec ),0.0 );
	float ndoth=max( dot( normal,hvec ),0.0 );
	
	float spow=pow( 2.0,glosiness * 12.0 );
//	float spow=pow( 2048.0,glosiness );

	float fnorm=(spow+2.0)/8.0;
	
	vec3 fschlick=specular + (1.0-specular) * pow( 1.0-hdotl,5.0 ) * glosiness;

	specular=fschlick * pow( ndoth,spow ) * fnorm;
	
	vec3 light=r_LightColor.rgb * ndotl * atten;
	
#if WX_POINTLIGHT

	vec3 lpos=(r_InverseLightViewMatrix * vec4( position,1.0 )).xyz;
	light*=pow( textureCube( r_LightCubeTexture,lpos ).rgb,vec3( 2.2 ) );

#elif WX_SPOTLIGHT

	vec3 lpos=(r_InverseLightViewMatrix * vec4( position,1.0 )).xyz;
	lpos.xy=lpos.xy/lpos.z * 0.5 + 0.5;
	lpos.y=1.0-lpos.y;
	light*=pow( texture2D( r_LightTexture,lpos.xy ).rgb,vec3( 2.2 ) ); 

#endif
	
#if WX_SHADOWTYPE
	light*=shadowColor( position );
#endif

	vec3 frag=(diffuse+specular) * light;
		
	gl_FragColor=vec4( frag,1.0 );
}

#endif

#if WX_COLORPASS && WX_DEFERREDPASS

//deferred PBR lighting
//
void emitPbrFragment( vec4 color,vec3 ambient,vec3 emissive,float metalness,float roughness,float occlusion,vec3 normal ){

	color*=v_Color;

	float glosiness=1.0-roughness;
	vec3 color0=vec3( 0.04,0.04,0.04 );
	vec3 diffuse=color.rgb * (1.0-metalness);
	vec3 specular=(color.rgb-color0) * metalness + color0;
	
	vec3 vvec=normalize( -v_Position );
	float ndotv=max( dot( normal,vvec ),0.0 );
	
	vec3 ambEnv=sampleEnv( reflect( v_Position,normal ),roughness );
	
	/*
	vec3 rvec=r_EnvMatrix * reflect( v_Position,normal );

	float lod=textureCube( r_EnvTexture,rvec,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;
	if( lod>0.0 ) lod=textureCube( r_EnvTexture,rvec ).a * 255.0;

//	float lod=textureCube( r_EnvTexture,rvec ).a * 255.0;
//	if( lod==0.0 ) lod=textureCube( r_EnvTexture,rvec,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;

	vec3 ambEnv=pow( textureCube( r_EnvTexture,rvec,max( roughness*r_EnvTextureMaxLod-lod,0.0 ) ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
	*/

	vec3 fschlick0=specular + (1.0-specular) * pow( 1.0-ndotv,5.0 ) * glosiness;

	vec3 ambDiffuse=diffuse * (r_AmbientDiffuse.rgb+ambient);
		
	vec3 ambSpecular=fschlick0 * ambEnv;
	
	vec3 frag=(ambDiffuse + ambSpecular) * occlusion + emissive;
	
#if WX_DEFERREDRENDERER
	//write ambient
	gl_FragData[0]=vec4( min( frag,8.0 ),1.0 );
	
	//write color/metalness
	gl_FragData[1]=vec4( color.rgb,metalness );
	
	//write normal/roughness
	gl_FragData[2]=vec4( normal * 0.5 + 0.5,roughness );
#endif
}

#endif

#if WX_COLORPASS && WX_FORWARDPASS

//forward PBR lighting
//
void emitPbrFragment( vec4 color,vec3 ambient,vec3 emissive,float metalness,float roughness,float occlusion,vec3 normal ){

	color*=v_Color;

	const vec3 color0=vec3( 0.04,0.04,0.04 );
	
	float glosiness=1.0-roughness;
	vec3 diffuse=color.rgb * (1.0-metalness);
	vec3 specular=(color.rgb-color0) * metalness + color0;
	
	vec3 vvec=normalize( -v_Position );
	float ndotv=dot( normal,vvec );
	
	vec3 frag=vec3( 0.0 );
	
#if WX_AMBIENTPASS
	//ambient color
	vec3 ambEnv=sampleEnv( reflect( v_Position,normal ),roughness );
/*	
	vec3 rvec=r_EnvMatrix * reflect( v_Position,normal );
	
	float lod=textureCube( r_EnvTexture,rvec,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;
	if( lod>0.0 ) lod=textureCube( r_EnvTexture,rvec ).a * 255.0;
		
//	float lod=textureCube( r_EnvTexture,rvec ).a * 255.0;
//	if( lod==0.0 ) lod=textureCube( r_EnvTexture,rvec,r_EnvTextureMaxLod ).a * 255.0 - r_EnvTextureMaxLod;

	vec3 ambEnv=pow( textureCube( r_EnvTexture,rvec,max( roughness*r_EnvTextureMaxLod-lod,0.0 ) ).rgb,vec3( 2.2 ) ) * r_EnvColor.rgb;
*/
	
	vec3 fschlick0=specular + (1.0-specular) * pow( 1.0-ndotv,5.0 ) * glosiness;
	
	vec3 ambDiffuse=diffuse * (r_AmbientDiffuse.rgb+ambient);
	
	vec3 ambSpecular=fschlick0 * ambEnv;

	frag+=( ambDiffuse + ambSpecular ) * occlusion + emissive;
#endif

#if WX_LIGHTINGPASS
	//lighting color
	float spow=pow( 2.0,glosiness * 12.0 );				//specular power
//	float spow=pow( 4096.0,glosiness );
	float fnorm=(spow+2.0)/8.0;							//normalization factor
	
#if WX_DIRECTIONALLIGHT

	vec3 lvec=normalize( -r_LightViewMatrix[2].xyz );
	
	float atten=1.0;
	
#elif WX_POINTLIGHT

	vec3 lvec=r_LightViewMatrix[3].xyz-v_Position;
	
	float atten=pointAtten( length( lvec ),r_LightRange );
	
	lvec=normalize( lvec );
	
#elif WX_SPOTLIGHT

	vec3 lvec=r_LightViewMatrix[3].xyz-v_Position;
	
	float atten=pointAtten( length( lvec ),r_LightRange );
	
	lvec=normalize( lvec );
	
	float cosangle=dot( -lvec,r_LightViewMatrix[2].xyz );
	if( cosangle<0.0 ) return;				//behind spotlight direction
	
	float angle=acos( cosangle );
	if( angle>r_LightOuterAngle ) return;	//outside outer cone

	atten*=1.0-max( (angle-r_LightInnerAngle)/(r_LightOuterAngle-r_LightInnerAngle),0.0 );
	
#endif
	vec3 hvec=normalize( lvec+vvec );

	float ndotl=max( dot( normal,lvec ),0.0 );
	float ndoth=max( dot( normal,hvec ),0.0 );
	float hdotl=max( dot( hvec,lvec ),0.0 );
	
	vec3 fschlick=specular + (1.0-specular) * pow( 1.0-hdotl,5.0 ) * glosiness;
	
	vec3 fspecular=fschlick * pow( ndoth,spow ) * fnorm;
	
	vec3 light=r_LightColor.rgb * ndotl * atten;
	
	light=(diffuse+fspecular) * light;

#if WX_SHADOWTYPE
	light*=shadowColor( v_Position );
#endif

	frag+=light;
	
#endif	//WX_LIGHTINGPASS

	color.rgb=frag;
	
	emitColorFragment( color );
}

#endif
