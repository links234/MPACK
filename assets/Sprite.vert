#define NONE 			0.
#define ALPHA_TEST 		1.
#define ALPHA_BLEND		2.

uniform mat4 projection_matrix;

attribute  vec2  a_Vertex;
attribute  vec2  a_TexCoord;
attribute  vec4  a_Color;
attribute  float a_ShadeType;

varying vec2  texCoord;
varying vec4  color;
varying float shadeType;

void main(void)
{
	texCoord = a_TexCoord;
	color=a_Color;
	shadeType=a_ShadeType;
	
	if(shadeType!=ALPHA_BLEND)
	{
		color.w=1.0;
	}
	
	vec4 pos = vec4(a_Vertex, 1.0, 1.0);
	gl_Position = projection_matrix * pos;
}