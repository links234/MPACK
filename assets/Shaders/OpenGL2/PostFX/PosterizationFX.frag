#version 130

uniform sampler2D texture0;

float gamma;
float numColors;

in vec2 texCoord0;

out vec4 outColor;

void main()
{
	gamma=0.6;
	numColors=8.0;
	vec3 tempColor = texture(texture0, texCoord0).rgb;
  	tempColor = pow(tempColor, vec3(gamma, gamma, gamma));
  	tempColor = tempColor * numColors;
  	tempColor = floor(tempColor);
  	tempColor = tempColor / numColors;
  	tempColor = pow(tempColor, vec3(1.0/gamma));
  	outColor = vec4(tempColor, 1.0);
}