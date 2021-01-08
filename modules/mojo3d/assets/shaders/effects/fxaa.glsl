
//@renderpasses 0

uniform sampler2D r_SourceBuffer;
uniform vec2 r_SourceBufferSize;
uniform vec2 r_SourceBufferScale;

varying vec2 v_SourceBufferCoords;

//@vertex

attribute vec2 a_Position;
	
void main(){

	v_SourceBufferCoords=a_Position * r_SourceBufferScale;

	gl_Position=vec4( a_Position * 2.0 - 1.0,-1.0,1.0 );
}

//@fragment

#ifndef FXAA_REDUCE_MIN
    #define FXAA_REDUCE_MIN   (1.0/ 128.0)
#endif
#ifndef FXAA_REDUCE_MUL
    #define FXAA_REDUCE_MUL   (1.0 / 8.0)
#endif
#ifndef FXAA_SPAN_MAX
    #define FXAA_SPAN_MAX     8.0
#endif

vec4 fxaa(){

    vec4 color;
    
    vec2 inverseVP=1.0/r_SourceBufferSize;
    
    vec2 v_rgbM=v_SourceBufferCoords;
    
    vec2 v_rgbNW=v_rgbM+vec2(-inverseVP.x,-inverseVP.y);
    vec2 v_rgbNE=v_rgbM+vec2( inverseVP.x,-inverseVP.y);
    vec2 v_rgbSW=v_rgbM+vec2(-inverseVP.x, inverseVP.y);
    vec2 v_rgbSE=v_rgbM+vec2( inverseVP.x, inverseVP.y);
    
    vec3 rgbNW = texture2D(r_SourceBuffer, v_rgbNW).xyz;
    vec3 rgbNE = texture2D(r_SourceBuffer, v_rgbNE).xyz;
    vec3 rgbSW = texture2D(r_SourceBuffer, v_rgbSW).xyz;
    vec3 rgbSE = texture2D(r_SourceBuffer, v_rgbSE).xyz;
    
    vec4 texColor = texture2D(r_SourceBuffer, v_rgbM);
    
    vec3 rgbM  = texColor.xyz;
    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
    
    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) *
                          (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
    
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
              max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
              dir * rcpDirMin)) * inverseVP;
    
    vec3 rgbA = 0.5 * (
        texture2D(r_SourceBuffer, v_rgbM + dir * (1.0 / 3.0 - 0.5)).xyz +
        texture2D(r_SourceBuffer, v_rgbM  + dir * (2.0 / 3.0 - 0.5)).xyz);
    vec3 rgbB = rgbA * 0.5 + 0.25 * (
        texture2D(r_SourceBuffer, v_rgbM + dir * -0.5).xyz +
        texture2D(r_SourceBuffer, v_rgbM + dir * 0.5).xyz);

    float lumaB = dot(rgbB, luma);
    if ((lumaB < lumaMin) || (lumaB > lumaMax))
        color = vec4(rgbA, texColor.a);
    else
        color = vec4(rgbB, texColor.a);
    return color;
}


void main(){

	vec4 color=fxaa();
	
	gl_FragColor=color;
}
