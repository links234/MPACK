#version 130

uniform sampler2D texture0;

float rt_w;
float rt_h;

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

in vec2 texCoord0;

out vec4 outColor;

void main()
{
	rt_w=800.0f;
	rt_h=600.0f;
    	outColor = texture(texture0, texCoord0) * weight[0];
    	for (int i=1; i<3; i++)
    	{
      		outColor += texture(texture0, texCoord0 + vec2(offset[i])/rt_w, 0.0) * weight[i];
      		outColor += texture(texture0, texCoord0 - vec2(offset[i])/rt_w, 0.0) * weight[i];
    	}
}
