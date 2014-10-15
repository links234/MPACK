#version 130

uniform sampler2D texture0;

in vec2 texCoord0;

out vec4 outColor;

void main()
{
    	vec3 pixcol = texture(texture0, texCoord0).rgb;
    	vec3 colors[3];
    	colors[0] = vec3(0.,0.,1.);
    	colors[1] = vec3(1.,1.,0.);
    	colors[2] = vec3(1.,0.,0.);
    	float lum = dot(vec3(0.30, 0.59, 0.11), pixcol.rgb);
    	int ix = (lum < 0.5)? 0:1;
    	outColor = vec4(mix(colors[ix],colors[ix+1],(lum-float(ix)*0.5)/0.5),1.0);
}