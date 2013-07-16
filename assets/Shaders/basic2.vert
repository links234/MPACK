uniform mat4 projection_matrix;

attribute  vec2 a_Vertex;

void main(void) 
{
	vec4 pos = vec4(a_Vertex, 1.0, 1.0);	
	gl_Position = projection_matrix * pos;	
}
