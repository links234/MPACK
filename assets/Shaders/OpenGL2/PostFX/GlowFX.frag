#version 130

uniform sampler2D texture0;
 
float pixelWidth = 1.0/800.0;
float pixelHeight = 1.0/600.0;
 
in vec2 texCoord0;

out vec4 outColor;

void main()
{
	vec2 texel = vec2(texCoord0);
	vec4 pixel = vec4(texture(texture0, texel));
     
	vec4 bloom = vec4(0);
     
	for(float x = -2; x <= 2; ++x)
	{
		for(float y = -2; y <= 2; ++y)
		{
			bloom += (texture(texture0, texCoord0 + vec2(x*pixelWidth, y*pixelHeight)) - 0.4);
		}
	}

	bloom = clamp(bloom / 25.0, 0.0, 1.0);

	outColor = pixel + bloom;
}

