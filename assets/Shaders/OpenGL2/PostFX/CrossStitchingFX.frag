#version 130

uniform sampler2D texture0;

float rt_w = 800.0f;
float rt_h = 600.0f;
float stitching_size = 6.0;
float invert = 1;

in vec2 texCoord0;

out vec4 outColor;

void main()
{
	float size = stitching_size;
	vec2 cPos = texCoord0 * vec2(rt_w, rt_h);
	vec2 tlPos = floor(cPos / vec2(size, size));
	tlPos *= size;
	int remX = int(mod(cPos.x, size));
	int remY = int(mod(cPos.y, size));
	if (remX == 0 && remY == 0)
		tlPos = cPos;
	vec2 blPos = tlPos;
	blPos.y += (size - 1.0);
	if ((remX == remY) || (((int(cPos.x) - int(blPos.x)) == (int(blPos.y) - int(cPos.y)))))
	{
		if (invert == 1)
			outColor = vec4(0.2, 0.15, 0.05, 1.0);
		else
      			outColor = texture2D(texture0, tlPos * vec2(1.0/rt_w, 1.0/rt_h)) * 1.4;
  	}
  	else
  	{
		if (invert == 1)
			outColor = texture2D(texture0, tlPos * vec2(1.0/rt_w, 1.0/rt_h)) * 1.4;
		else
			outColor = vec4(0.0, 0.0, 0.0, 1.0);
  	}
	
}
