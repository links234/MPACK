#version 130

uniform sampler2D texture0;

float mid_grey=0.3;

in vec2 texCoord0;

out vec4 outColor;

float map(float x, float y, float a, float b, float val)
{
	return a+(val-x)/(y-x)*(b-a);
}

float luma(vec4 color)
{
	const vec4 lumcoeff = vec4(0.299,0.587,0.114,0.);
	float lum=dot(color,lumcoeff);
	if(lum<0.5)
	{
		return map(0.0,0.5,0.0,mid_grey,lum);
	}
	return map(0.5,1.0,mid_grey,1.0,lum);
}

void main()
{
	outColor=vec4(luma(texture(texture0, texCoord0)));
}
