precision mediump float;
precision mediump int;

float rt_w = 1920.0;
float rt_h = 1080.0;
float inv_w_size = 1.0/rt_w;
float inv_h_size = 1.0/rt_h;
vec2 inv_screen_size = vec2(inv_w_size,inv_h_size);

#define FXAA_EDGE_THRESHOLD      (1.0/8.0)
#define FXAA_EDGE_THRESHOLD_MIN  (1.0/24.0)
#define FXAA_SEARCH_STEPS        32
#define FXAA_SEARCH_THRESHOLD    (1.0/4.0)
#define FXAA_SUBPIX              1
#define FXAA_SUBPIX_FASTER       0
#define FXAA_SUBPIX_CAP          (3.0/4.0)
#define FXAA_SUBPIX_TRIM         (1.0/4.0)
#define FXAA_SUBPIX_TRIM_SCALE (1.0/(1.0 - FXAA_SUBPIX_TRIM))

#define FxaaBool2Float(a) mix(0.0, 1.0, (a))
#define FxaaPow3(x, y) pow(x, y)
#define FxaaSel3(f, t, b) mix((f), (t), (b))
#define FxaaTexLod0(t, p) texture2D(t, p)
#define FxaaTexOff(t, p, o) texture2D(t, p + o*inv_screen_size)
#define FxaaTovec3(a) vec3((a), (a), (a))

float FxaaLuma(vec3 rgb) 
{
	return rgb.y * (0.587/0.299) + rgb.x; 
} 

vec3 FxaaLerp3(vec3 a, vec3 b, float amountOfA) 
{
	return (vec3(-amountOfA) * b) + ((a * vec3(amountOfA)) + b); 
}

vec3 FxaaPixelShader(
			vec2 pos,
			sampler2D tex,
			vec2 rcpFrame) 
{
    	vec3 rgbN = FxaaTexOff(tex, pos.xy, vec2( 0.0,-1.0)).xyz;
    	vec3 rgbW = FxaaTexOff(tex, pos.xy, vec2(-1.0, 0.0)).xyz;
    	vec3 rgbM = FxaaTexOff(tex, pos.xy, vec2( 0.0, 0.0)).xyz;
    	vec3 rgbE = FxaaTexOff(tex, pos.xy, vec2( 1.0, 0.0)).xyz;
    	vec3 rgbS = FxaaTexOff(tex, pos.xy, vec2( 0.0, 1.0)).xyz;
    	float lumaN = FxaaLuma(rgbN);
    	float lumaW = FxaaLuma(rgbW);
    	float lumaM = FxaaLuma(rgbM);
    	float lumaE = FxaaLuma(rgbE);
    	float lumaS = FxaaLuma(rgbS);
    	float rangeMin = min(lumaM, min(min(lumaN, lumaW), min(lumaS, lumaE)));
    	float rangeMax = max(lumaM, max(max(lumaN, lumaW), max(lumaS, lumaE)));
    	float range = rangeMax - rangeMin;      
    	if(range < max(FXAA_EDGE_THRESHOLD_MIN, rangeMax * FXAA_EDGE_THRESHOLD)) 
	{
       		return rgbM; 
	}
#if FXAA_SUBPIX > 0
 #if FXAA_SUBPIX_FASTER
	vec3 rgbL = (rgbN + rgbW + rgbE + rgbS + rgbM) * vec3(1.0/5.0);
 #else
	vec3 rgbL = rgbN + rgbW + rgbM + rgbE + rgbS;
 #endif
#endif        
    
#if FXAA_SUBPIX != 0
	float lumaL = (lumaN + lumaW + lumaE + lumaS) * 0.25;
	float rangeL = abs(lumaL - lumaM);
#endif        
#if FXAA_SUBPIX == 1
	float blendL = max(0.0, (rangeL / range) - FXAA_SUBPIX_TRIM) * FXAA_SUBPIX_TRIM_SCALE; 
	blendL = min(FXAA_SUBPIX_CAP, blendL);
#endif
#if FXAA_SUBPIX == 2
	float blendL = rangeL / range; 
#endif 

	vec3 rgbNW = FxaaTexOff(tex, pos.xy, vec2(-1.0,-1.0)).xyz;
	vec3 rgbNE = FxaaTexOff(tex, pos.xy, vec2( 1.0,-1.0)).xyz;
	vec3 rgbSW = FxaaTexOff(tex, pos.xy, vec2(-1.0, 1.0)).xyz;
	vec3 rgbSE = FxaaTexOff(tex, pos.xy, vec2( 1.0, 1.0)).xyz;
#if (FXAA_SUBPIX_FASTER == 0) && (FXAA_SUBPIX > 0)
	rgbL += (rgbNW + rgbNE + rgbSW + rgbSE);
	rgbL *= vec3(1.0/9.0);
#endif
	float lumaNW = FxaaLuma(rgbNW);
	float lumaNE = FxaaLuma(rgbNE);
	float lumaSW = FxaaLuma(rgbSW);
	float lumaSE = FxaaLuma(rgbSE);
	float edgeVert = 
		abs((0.25 * lumaNW) + (-0.5 * lumaN) + (0.25 * lumaNE)) +
		abs((0.50 * lumaW ) + (-1.0 * lumaM) + (0.50 * lumaE )) +
		abs((0.25 * lumaSW) + (-0.5 * lumaS) + (0.25 * lumaSE));
	float edgeHorz = 
		abs((0.25 * lumaNW) + (-0.5 * lumaW) + (0.25 * lumaSW)) +
		abs((0.50 * lumaN ) + (-1.0 * lumaM) + (0.50 * lumaS )) +
		abs((0.25 * lumaNE) + (-0.5 * lumaE) + (0.25 * lumaSE));
	bool horzSpan = edgeHorz >= edgeVert;
	float lengthSign = horzSpan ? -rcpFrame.y : -rcpFrame.x;
	if(!horzSpan) lumaN = lumaW;
	if(!horzSpan) lumaS = lumaE;
	float gradientN = abs(lumaN - lumaM);
	float gradientS = abs(lumaS - lumaM);
	lumaN = (lumaN + lumaM) * 0.5;
	lumaS = (lumaS + lumaM) * 0.5;
    
	bool pairN = gradientN >= gradientS;
	if(!pairN) lumaN = lumaS;
	if(!pairN) gradientN = gradientS;
	if(!pairN) lengthSign *= -1.0;
	vec2 posN;
	posN.x = pos.x + (horzSpan ? 0.0 : lengthSign * 0.5);
	posN.y = pos.y + (horzSpan ? lengthSign * 0.5 : 0.0);
    

	gradientN *= FXAA_SEARCH_THRESHOLD;

	vec2 posP = posN;
	vec2 offNP = horzSpan ? 
	vec2(rcpFrame.x, 0.0) :
	vec2(0.0, rcpFrame.y); 
	float lumaEndN = lumaN;
	float lumaEndP = lumaN;
	bool doneN = false;
	bool doneP = false;

	posN += offNP * vec2(-1.0, -1.0);
	posP += offNP * vec2( 1.0,  1.0);

	for(int i = 0; i < FXAA_SEARCH_STEPS; i++) 
	{
		if(!doneN) lumaEndN = FxaaLuma(FxaaTexLod0(tex, posN.xy).xyz);
		if(!doneP) lumaEndP = FxaaLuma(FxaaTexLod0(tex, posP.xy).xyz);

		doneN = doneN || (abs(lumaEndN - lumaN) >= gradientN);
		doneP = doneP || (abs(lumaEndP - lumaN) >= gradientN);
		if(doneN && doneP) break;
		if(!doneN) posN -= offNP;
		if(!doneP) posP += offNP; 
	}
    
	float dstN = horzSpan ? pos.x - posN.x : pos.y - posN.y;
	float dstP = horzSpan ? posP.x - pos.x : posP.y - pos.y;
	bool directionN = dstN < dstP;
	lumaEndN = directionN ? lumaEndN : lumaEndP;
    
	if(((lumaM - lumaN) < 0.0) == ((lumaEndN - lumaN) < 0.0)) 
		lengthSign = 0.0;
 
	float spanLength = (dstP + dstN);
	dstN = directionN ? dstN : dstP;
	float subPixelOffset = (0.5 + (dstN * (-1.0/spanLength))) * lengthSign;
	vec3 rgbF = FxaaTexLod0(tex, vec2(
					pos.x + (horzSpan ? 0.0 : subPixelOffset),
					pos.y + (horzSpan ? subPixelOffset : 0.0))).xyz;
#if FXAA_SUBPIX == 0
	return rgbF; 
#else        
	return FxaaLerp3(rgbL, rgbF, blendL); 
#endif
}

uniform sampler2D texture0;

varying vec2 texCoord0;

vec4 outColor;

void main()
{
	vec2 rcpFrame = vec2(1.0/rt_w, 1.0/rt_h);
	outColor=texture2D(texture0,texCoord0);
	if(texCoord0.x<0.0)
	{
		outColor=vec4(FxaaPixelShader(texCoord0,texture0,rcpFrame),1.0);
	}
	gl_FragColor=outColor;
}
