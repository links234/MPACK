#version 130

uniform sampler2D texture0;

float vx_offset;
float rt_w;
float rt_h;
float pixel_w;
float pixel_h;

in vec2 texCoord0;

out vec4 outColor;

void main()
{
	vx_offset = 0.5f;
	rt_w = 800.0f;
	rt_h = 600.0f;
	pixel_w = 5.0f;
	pixel_h = 5.0f;

    	float dx = pixel_w*(1./rt_w);
    	float dy = pixel_h*(1./rt_h);
    	vec2 coord = vec2(dx*floor(texCoord0.x/dx),dy*floor(texCoord0.y/dy));
    	outColor = vec4(texture(texture0, coord).rgb,1.0);
}