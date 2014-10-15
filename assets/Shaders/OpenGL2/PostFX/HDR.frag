#version 130

uniform sampler2D texture0;
uniform sampler2D texture1;

float exposure=0.9;
float blurAmount=0.5;
float effectAmount=0.5;
float gamma=0.9;

in vec2 texCoord0;

out vec4 outColor;

/*
float vignette(vec2 pos, float inner, float outer)
{
	float r = length(pos);
	r = 1.0 - smoothstep(inner, outer, r);
	return r;
}
*/

vec4 radial(sampler2D tex,
              vec2 texcoord,
              int samples,
              float startScale = 1.0,
              float scaleMul = 0.9)
{
	vec4 c = vec4(0.0);
	float scale = startScale;
	for(int i=0; i<samples; i++) 
	{
		vec2 uv = ((texcoord-0.5)*scale)+0.5;
		vec4 s = texture(tex, uv);
		c += s * scale;
		scale *= scaleMul;
	}
	c /= samples;
	return c;
}

void main()
{
	outColor = texture(texture0, texCoord0) + radial(texture0, texCoord0, 30, 1.0, 0.95) * effectAmount;

	outColor = outColor * exposure;
	
	outColor.rgb = pow(outColor.rgb, vec3(gamma));
}
