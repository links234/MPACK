#include "ShaderTypes.hpp"
#include "ShaderUniform.hpp"
#include "Vertex.hpp"

ProgramType_Vertex3fPos4fColor::ProgramType_Vertex3fPos4fColor(const char* vertexShader, const char* fragmentShader, const char* header)
	: AbstractProgramType(vertexShader, fragmentShader, header)
{}
ProgramType_Vertex3fPos4fColor::~ProgramType_Vertex3fPos4fColor()
{}
void ProgramType_Vertex3fPos4fColor::BindAttributeLocations()
{
	BindAttrib(0, "a_Vertex");
	BindAttrib(1, "a_Color");
}
void ProgramType_Vertex3fPos4fColor::UpdateUniforms()
{
	SendUniform4x4("modelviewprojection_matrix",(GLfloat*)(&ShaderUniform::modelviewprojectionMatrix));
}
void ProgramType_Vertex3fPos4fColor::UpdateFrameUniforms()
{
}
void ProgramType_Vertex3fPos4fColor::InitUniforms()
{
	SendUniform4x4("modelviewprojection_matrix",(GLfloat*)(&ShaderUniform::modelviewprojectionMatrix));
}
void ProgramType_Vertex3fPos4fColor::SendVertexBuffer()
{
	glVertexAttribPointer((GLint)0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*7,BUFFER_OFFSET(0));
	glVertexAttribPointer((GLint)1,4,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*7,BUFFER_OFFSET(sizeof(GLfloat)*3));
}
void ProgramType_Vertex3fPos4fColor::SendVertexBuffer(GLfloat *VA)
{
	glVertexAttribPointer((GLint)0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*7,VA);
	glVertexAttribPointer((GLint)1,4,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*7,(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat))*3));
}
void ProgramType_Vertex3fPos4fColor::EnableVertexAttributes()
{
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
void ProgramType_Vertex3fPos4fColor::DisableVertexAttributes()
{
	glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


ProgramType_Sprite::ProgramType_Sprite(const char* vertexShader, const char* fragmentShader, const char* header)
	: AbstractProgramType(vertexShader, fragmentShader, header)
{
}
ProgramType_Sprite::~ProgramType_Sprite()
{
}
void ProgramType_Sprite::BindAttributeLocations()
{
	BindAttrib(0, "a_Vertex");
	BindAttrib(1, "a_TexCoord");
	BindAttrib(2, "a_Color");
	BindAttrib(3, "a_ShadeType");
}
void ProgramType_Sprite::UpdateUniforms()
{
	SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
}
void ProgramType_Sprite::UpdateFrameUniforms()
{
}
void ProgramType_Sprite::InitUniforms()
{
	SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
	SendUniform("texture0",0);
}
void ProgramType_Sprite::SendVertexBuffer()
{
	glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(0));
	glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*2));
	glVertexAttribPointer((GLint)2,4,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*4));
	glVertexAttribPointer((GLint)3,1,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*8));
}
void ProgramType_Sprite::SendVertexBuffer(GLfloat *VA)
{
	glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),VA);
	glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*2)));
	glVertexAttribPointer((GLint)2,4,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*4)));
	glVertexAttribPointer((GLint)3,1,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*8)));
}
void ProgramType_Sprite::EnableVertexAttributes()
{
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}
void ProgramType_Sprite::DisableVertexAttributes()
{
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}

ProgramType_Basic2::ProgramType_Basic2(const char* vertexShader, const char* fragmentShader, const char* header)
	: AbstractProgramType(vertexShader, fragmentShader, header)
{
}
ProgramType_Basic2::~ProgramType_Basic2()
{
}
void ProgramType_Basic2::BindAttributeLocations()
{
	BindAttrib(0, "a_Vertex");
}
void ProgramType_Basic2::UpdateUniforms()
{
	SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
}
void ProgramType_Basic2::UpdateFrameUniforms()
{
}
void ProgramType_Basic2::InitUniforms()
{
	SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
}
void ProgramType_Basic2::SendVertexBuffer()
{
	glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(Vector2f),BUFFER_OFFSET(0));
}
void ProgramType_Basic2::SendVertexBuffer(GLfloat *VA)
{
	glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(Vector2f),VA);
}
void ProgramType_Basic2::EnableVertexAttributes()
{
	glEnableVertexAttribArray(0);
}
void ProgramType_Basic2::DisableVertexAttributes()
{
	glEnableVertexAttribArray(0);
}

