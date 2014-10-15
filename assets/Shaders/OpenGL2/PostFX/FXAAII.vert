#version 130

uniform mat4 projection_matrix;

float FXAA_SUBPIX_SHIFT = 1.0/4.0;

float rt_w = 800.0f;
float rt_h = 600.0f;

in vec2 a_Vertex;
in vec2 a_TexCoord0;

out vec4 texCoord0;

void main(void) 
{
	vec2 rcpFrame = vec2(1.0/rt_w, 1.0/rt_h);
	texCoord0.xy = a_TexCoord0;
  	texCoord0.zw = texCoord0.xy - (rcpFrame * (0.5 + FXAA_SUBPIX_SHIFT));	

	vec4 pos = vec4(a_Vertex, 0.0, 1.0);	
	gl_Position = projection_matrix * pos;	
}
