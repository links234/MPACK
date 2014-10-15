#version 130

uniform sampler2D texture0;

in vec2 texCoord0;

out vec4 outColor;

void main(void) 
{	
	float gamma=0.22;
	float numColors=8.0;

	vec4 sum = vec4(0);
   	int j;
   	int i;

   	for( i= -4 ;i < 4; i++)
   	{
        	for (j = -3; j < 3; j++)
        	{
            		sum += texture(texture0, texCoord0 + vec2(j, i)*0.003) * 0.25;
        	}
   	}
  	outColor=texture(texture0, texCoord0);
       if (outColor.r < 0.3)
    	{
       		outColor = sum*sum*0.012 + texture(texture0, texCoord0);
    	}
    	else
    	{
        	if (outColor.r < 0.5)
        	{
            		outColor = sum*sum*0.009 + texture(texture0, texCoord0);
        	}
        	else
        	{
            		outColor = sum*sum*0.0075 + texture(texture0, texCoord0);
        	}
    	}
}
