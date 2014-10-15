/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef GLSLSHADER_HPP
#define GLSLSHADER_HPP

#include "Types.hpp"
#include "Resource.hpp"
#include "Log.hpp"

#include <map>
#include <string>
#include <vector>

using std::string;
using std::ifstream;
using std::map;
using std::vector;

using namespace Core;

class GLSLProgram
{
public:
    struct GLSLShader
    {
        unsigned int id;
        string source;
    };

    GLSLProgram(const char* vertexShader, const char* fragmentShader, const char* header=NULL)
    	: m_programID(0)
    {
    	if(header==NULL)
    	{
    		m_header="";
    	}
    	Resource *vertexShaderResourcePointer=LoadResource(vertexShader);
    	vertexShaderResourcePointer->Open();
    	m_vertexShader.source=string((const char*)(vertexShaderResourcePointer->Bufferize()));
    	delete vertexShaderResourcePointer;

    	Resource *fragmentShaderResourcePointer=LoadResource(fragmentShader);
		fragmentShaderResourcePointer->Open();
		m_fragmentShader.source=string((const char*)(fragmentShaderResourcePointer->Bufferize()));
		delete fragmentShaderResourcePointer;
    }

    virtual ~GLSLProgram()
    {
    }

    void Unload()
    {
        glDetachShader(m_programID, m_vertexShader.id);
        glDetachShader(m_programID, m_fragmentShader.id);
        glDeleteShader(m_vertexShader.id);
        glDeleteShader(m_fragmentShader.id);
        glDeleteShader(m_programID);
    }
	
    bool Initialize()
    {
        m_programID = glCreateProgram();
        m_vertexShader.id = glCreateShader(GL_VERTEX_SHADER);
        m_fragmentShader.id = glCreateShader(GL_FRAGMENT_SHADER);

        if (m_vertexShader.source.empty() || m_fragmentShader.source.empty())
        {
        	LOGE("Shader sources empty!");
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

	bool LinkProgram()
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

    GLuint GetUniformLocation(const string& name)
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

    GLuint GetAttribLocation(const string& name)
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

    void SendUniform(const string& name, const int id)
    {
        GLuint location = GetUniformLocation(name);
        glUniform1i(location, id);
    }

    void SendUniform4x4(const string& name, const float* matrix, bool transpose=false)
    {
        GLuint location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, transpose, matrix);
    }

    void SendUniform3x3(const string& name, const float* matrix, bool transpose=false)
    {
        GLuint location = GetUniformLocation(name);
        glUniformMatrix3fv(location, 1, transpose, matrix);
    }

    void SendUniform(const string& name, const float red, const float green,
                     const float blue, const float alpha)
    {
		GLuint location = GetUniformLocation(name);
		glUniform4f(location, red, green, blue, alpha);
    }

    void SendUniform(const string& name, const float x, const float y,
                     const float z)
    {
		GLuint location = GetUniformLocation(name);
		glUniform3f(location, x, y, z);
    }
	
    void SendUniform(const string& name, const float scalar)
    {
		GLuint location = GetUniformLocation(name);
		glUniform1f(location, scalar);
    }

    void BindAttrib(unsigned int index, const string& attribName)
    {
        glBindAttribLocation(m_programID, index, attribName.c_str());
    }

    void BindShader()
    {
		if(lastBindedShader!=this)
		{
			lastBindedShader=this;
			glUseProgram(m_programID);
		}
    }

private:
	static GLSLProgram* lastBindedShader;

    bool CompileShader(const GLSLShader& shader)
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

    void OutputShaderLog(unsigned int shaderID)
    {
        GLint infoLen;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
		const int BUFFER_SIZE=4096;
		char buffer[BUFFER_SIZE];

		LOGE("Shader output log:");

        glGetShaderInfoLog(shaderID, BUFFER_SIZE, &infoLen, buffer);

        LOGE("\n%s",buffer);
    }

	void OutputProgramLog()
    {
        GLint infoLen;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLen);
		const int BUFFER_SIZE=4096;
		char buffer[BUFFER_SIZE];

		LOGE("Program output log: ");

        glGetProgramInfoLog(m_programID, BUFFER_SIZE, &infoLen, buffer);

        LOGE("\n%s",buffer);
    }

    GLSLShader m_vertexShader;
    GLSLShader m_fragmentShader;
    unsigned int m_programID;
	string m_header;

    map<string, GLuint> m_uniformMap;
    map<string, GLuint> m_attribMap;
};

#endif
