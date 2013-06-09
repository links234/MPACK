uniform mat4 modelviewprojection_matrix;

attribute vec3 a_Vertex;
attribute vec4 a_Color;

varying vec4 color;

void main(void) 
{
	vec4 pos = vec4(a_Vertex, 1.0);
	gl_Position = modelviewprojection_matrix * pos;
	color=a_Color;
}
