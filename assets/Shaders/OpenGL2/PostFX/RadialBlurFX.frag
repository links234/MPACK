#version 130

uniform sampler2D texture0;
 
const float sampleDist = 1.0;
const float sampleStrength = 2.2; 

in vec2 texCoord0;

out vec4 outColor;

void main(void)
{
	float samples[10] =
	float[](-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08);
 
	vec2 dir = 0.5 - texCoord0; 
 
	float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
 
	dir = dir/dist; 

	vec4 color = texture(texture0,texCoord0); 
 
	vec4 sum = color;
 
	for (int i = 0; i < 10; i++)
	{
		sum += texture( texture0, texCoord0 + dir * samples[i] * sampleDist );
	}

	sum *= 1.0/11.0;

	float t = dist * sampleStrength;
	t = clamp( t ,0.0,1.0); 
 
	outColor = mix( color, sum, t );
} 