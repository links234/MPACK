/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "GLSLShader.hpp"

using std::string;
using std::ifstream;
using std::map;
using std::vector;

using namespace Core;

GLSLProgram* GLSLProgram::lastBindedShader=NULL;

GLSLProgram::GLSLProgram(const char* vertexShader, const char* fragmentShader, const char* header)
	: m_programID(0)
{
	if(header==NULL)
	{
		m_header="";
	}
	Core::Resource *vertexShaderResourcePointer=Core::LoadResource(vertexShader);
	vertexShaderResourcePointer->Open();
	m_vertexShader.source=string((const char*)(vertexShaderResourcePointer->Bufferize()));
	delete vertexShaderResourcePointer;

	Core::Resource *fragmentShaderResourcePointer=Core::LoadResource(fragmentShader);
	fragmentShaderResourcePointer->Open();
	m_fragmentShader.source=string((const char*)(fragmentShaderResourcePointer->Bufferize()));
	delete fragmentShaderResourcePointer;
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::Unload()
{
	glDetachShader(m_programID, m_vertexShader.id);
	glDetachShader(m_programID, m_fragmentShader.id);
	glDeleteShader(m_vertexShader.id);
	glDeleteShader(m_fragmentShader.id);
	glDeleteShader(m_programID);
}

bool GLSLProgram::Initialize()
{
	m_programID = glCreateProgram();
	m_vertexShader.id = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader.id = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_vertexShader.source.empty() || m_fragmentShader.source.empty())
	{
		return false;
	}

	const GLchar* tmp = static_cast<const GLchar*>(m_vertexShader.source.c_str());
	glShaderSource(m_vertexShader.id, 1, (const GLchar**)&tmp, NULL);

	tmp = static_cast<const GLchar*>(m_fragmentShader.source.c_str());
	glShaderSource(m_fragmentShader.id, 1, (const GLchar**)&tmp, NULL);

	if (!CompileShader(m_vertexShader) || !CompileShader(m_fragmentShader))
	{
		LOGE("Failed to compile shader");
		return false;
	}

	glAttachShader(m_programID, m_vertexShader.id);
	glAttachShader(m_programID, m_fragmentShader.id);

	glLinkProgram(m_programID);
	return true;
}

bool GLSLProgram::LinkProgram()
{
	GLint result=0xDEADBEAF;
	glLinkProgram(m_programID);
	glGetProgramiv(m_programID,GL_LINK_STATUS,&result);
	if(!result)
	{
		LOGE("Failed to link shader program");
		OutputProgramLog();
		return false;
	}
	return true;
}

GLuint GLSLProgram::GetUniformLocation(const string& name)
{
	map<string, GLuint>::iterator i = m_uniformMap.find(name);
	if (i == m_uniformMap.end())
	{
		GLuint location = glGetUniformLocation(m_programID, name.c_str());
		m_uniformMap.insert(std::make_pair(name, location));
		return location;
	}

	return (*i).second;
}

GLuint GLSLProgram::GetAttribLocation(const string& name)
{
	map<string, GLuint>::iterator i = m_attribMap.find(name);
	if (i == m_attribMap.end())
	{
		GLuint location = glGetAttribLocation(m_programID, name.c_str());
		m_attribMap.insert(std::make_pair(name, location));
		return location;
	}

	return (*i).second;
}

void GLSLProgram::SendUniform(const string& name, const int id)
{
	GLuint location = GetUniformLocation(name);
	glUniform1i(location, id);
}

void GLSLProgram::SendUniform4x4(const string& name, const float* matrix, bool transpose)
{
	GLuint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, transpose, matrix);
}

void GLSLProgram::SendUniform3x3(const string& name, const float* matrix, bool transpose)
{
	GLuint location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, transpose, matrix);
}

void GLSLProgram::SendUniform(const string& name, const float red, const float green,
				 const float blue, const float alpha)
{
	GLuint location = GetUniformLocation(name);
	glUniform4f(location, red, green, blue, alpha);
}

void GLSLProgram::SendUniform(const string& name, const float x, const float y,
				 const float z)
{
	GLuint location = GetUniformLocation(name);
	glUniform3f(location, x, y, z);
}

void GLSLProgram::SendUniform(const string& name, const float scalar)
{
	GLuint location = GetUniformLocation(name);
	glUniform1f(location, scalar);
}

void GLSLProgram::BindAttrib(unsigned int index, const string& attribName)
{
	glBindAttribLocation(m_programID, index, attribName.c_str());
}

void GLSLProgram::BindShader()
{
	if(lastBindedShader!=this)
	{
		lastBindedShader=this;
		glUseProgram(m_programID);
	}
}

bool GLSLProgram::CompileShader(const GLSLShader& shader)
{
	glCompileShader(shader.id);
	GLint result = 0xDEADBEEF;
	glGetShaderiv(shader.id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		LOGE("Failed to compile shader:\n %s",shader.source.c_str());
		OutputShaderLog(shader.id);
		return false;
	}
	return true;
}

void GLSLProgram::OutputShaderLog(unsigned int shaderID)
{
	GLint infoLen;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
	const int BUFFER_SIZE=4096;
	char buffer[BUFFER_SIZE];

	LOGE("Shader output log:");

	glGetShaderInfoLog(shaderID, BUFFER_SIZE, &infoLen, buffer);

	LOGE("\n%s",buffer);
}

void GLSLProgram::OutputProgramLog()
{
	GLint infoLen;
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLen);
	const int BUFFER_SIZE=4096;
	char buffer[BUFFER_SIZE];

	LOGE("Program output log: ");

	glGetProgramInfoLog(m_programID, BUFFER_SIZE, &infoLen, buffer);

	LOGE("\n%s",buffer);
}
