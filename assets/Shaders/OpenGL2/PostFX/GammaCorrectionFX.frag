#version 130

uniform sampler2D texture0;

float gamma;

in vec2 texCoord0;

out vec4 outColor;

void main(void)
{
	gamma=0.9;
    	outColor.rgb = pow(texture(texture0, texCoord0).rgb, vec3(1.0 / gamma));
  	outColor.a = 1.0;
}