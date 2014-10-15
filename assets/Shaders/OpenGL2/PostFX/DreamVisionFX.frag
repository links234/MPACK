#version 130

uniform sampler2D texture0;

float gamma;
float numColors;

in vec2 texCoord0;

out vec4 outColor;

void main()
{
	outColor = texture(texture0, texCoord0);

	outColor += texture(texture0, texCoord0+0.001);
  	outColor += texture(texture0, texCoord0+0.003);
  	outColor += texture(texture0, texCoord0+0.005);
  	outColor += texture(texture0, texCoord0+0.007);
  	outColor += texture(texture0, texCoord0+0.009);
  	outColor += texture(texture0, texCoord0+0.011);

  	outColor += texture(texture0, texCoord0-0.001);
  	outColor += texture(texture0, texCoord0-0.003);
  	outColor += texture(texture0, texCoord0-0.005);
  	outColor += texture(texture0, texCoord0-0.007);
  	outColor += texture(texture0, texCoord0-0.009);
  	outColor += texture(texture0, texCoord0-0.011);

	outColor.rgb = vec3(outColor.r * 0.33+outColor.g * 0.59+outColor.b * 0.11);
  	outColor = outColor / 9.5;
}