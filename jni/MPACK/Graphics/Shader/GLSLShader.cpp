#include "GLSLShader.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		GLSLProgram* GLSLProgram::lastBindedShader=NULL;

		GLSLProgram::GLSLProgram(const char* vertexShader, const char* fragmentShader, const char* header)
			: m_programID(0)
		{
			if(header==NULL)
			{
				m_header="";
			}
			InputResource *pVertexShaderInputResource=GetInputResource(vertexShader);
			pVertexShaderInputResource->Open();
			m_vertexShader.path = vertexShader;
			m_vertexShader.source=string((const char*)(pVertexShaderInputResource->Bufferize()));
			delete pVertexShaderInputResource;

			InputResource *pFragmentShaderResource=GetInputResource(fragmentShader);
			pFragmentShaderResource->Open();
			m_fragmentShader.path = fragmentShader;
			m_fragmentShader.source=string((const char*)(pFragmentShaderResource->Bufferize()));
			delete pFragmentShaderResource;
		}

		GLSLProgram::~GLSLProgram()
		{
		}

		void GLSLProgram::Unload()
		{
			GL_CHECK( glDetachShader(m_programID, m_vertexShader.id) );
			GL_CHECK( glDetachShader(m_programID, m_fragmentShader.id) );
			GL_CHECK( glDeleteShader(m_vertexShader.id) );
			GL_CHECK( glDeleteShader(m_fragmentShader.id) );
			GL_CHECK( glDeleteShader(m_programID) );
		}

		bool GLSLProgram::Initialize()
		{
			GL_CHECK( m_programID = glCreateProgram() );
			GL_CHECK( m_vertexShader.id = glCreateShader(GL_VERTEX_SHADER) );
			GL_CHECK( m_fragmentShader.id = glCreateShader(GL_FRAGMENT_SHADER) );

			if (m_vertexShader.source.empty() || m_fragmentShader.source.empty())
			{
				return false;
			}

			const GLchar* tmp = static_cast<const GLchar*>(m_vertexShader.source.c_str());
			GL_CHECK( glShaderSource(m_vertexShader.id, 1, (const GLchar**)&tmp, NULL) );

			tmp = static_cast<const GLchar*>(m_fragmentShader.source.c_str());
			GL_CHECK( glShaderSource(m_fragmentShader.id, 1, (const GLchar**)&tmp, NULL) );

			if (!CompileShader(m_vertexShader) || !CompileShader(m_fragmentShader))
			{
				LOGE("Failed to compile shader");
				return false;
			}

			GL_CHECK( glAttachShader(m_programID, m_vertexShader.id) );
			GL_CHECK( glAttachShader(m_programID, m_fragmentShader.id) );

			GL_CHECK( glLinkProgram(m_programID) );
			return true;
		}

		bool GLSLProgram::LinkProgram()
		{
			GLint result=0xDEADBEAF;
			GL_CHECK( glLinkProgram(m_programID) );
			GL_CHECK( glGetProgramiv(m_programID,GL_LINK_STATUS,&result) );
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
				GLuint location;
				GL_CHECK( location = glGetUniformLocation(m_programID, name.c_str()) );
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
				GLuint location;
				GL_CHECK( location = glGetAttribLocation(m_programID, name.c_str()) );
				m_attribMap.insert(std::make_pair(name, location));
				return location;
			}

			return (*i).second;
		}

		void GLSLProgram::SendUniform(const string& name, const int id)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniform1i(location, id) );
		}

		void GLSLProgram::SendUniform4x4(const string& name, const float* matrix, bool transpose)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniformMatrix4fv(location, 1, transpose, matrix) );
		}

		void GLSLProgram::SendUniform3x3(const string& name, const float* matrix, bool transpose)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniformMatrix3fv(location, 1, transpose, matrix) );
		}

		void GLSLProgram::SendUniform(const string& name, const float red, const float green,
						 const float blue, const float alpha)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniform4f(location, red, green, blue, alpha) );
		}

		void GLSLProgram::SendUniform(const string& name, const float x, const float y,
						 const float z)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniform3f(location, x, y, z) );
		}

		void GLSLProgram::SendUniform(const string& name, const float scalar)
		{
			GLuint location = GetUniformLocation(name);
			GL_CHECK( glUniform1f(location, scalar) );
		}

		void GLSLProgram::BindAttrib(unsigned int index, const string& attribName)
		{
			GL_CHECK( glBindAttribLocation(m_programID, index, attribName.c_str()) );
		}

		void GLSLProgram::BindShader()
		{
			if(lastBindedShader!=this)
			{
				lastBindedShader=this;
				GL_CHECK( glUseProgram(m_programID) );
			}
		}

		bool GLSLProgram::CompileShader(const GLSLShader& shader)
		{
			GL_CHECK( glCompileShader(shader.id) );
			GLint result = 0xDEADBEEF;
			GL_CHECK( glGetShaderiv(shader.id, GL_COMPILE_STATUS, &result) );

			if (!result)
			{
				LOGE("Failed to compile shader from \"%s\":\n %s",shader.path.c_str(),shader.source.c_str());
				OutputShaderLog(shader.id);
				return false;
			}
			return true;
		}

		void GLSLProgram::OutputShaderLog(unsigned int shaderID)
		{
			GLint infoLen;
			GL_CHECK( glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen) );
			const int BUFFER_SIZE=64*1024;
			char buffer[BUFFER_SIZE];

			LOGE("Shader output log:");

			GL_CHECK( glGetShaderInfoLog(shaderID, BUFFER_SIZE, &infoLen, buffer) );

			LOGE("\n%s",buffer);
		}

		void GLSLProgram::OutputProgramLog()
		{
			GLint infoLen;
			GL_CHECK( glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLen) );
			const int BUFFER_SIZE=64*1024;
			char buffer[BUFFER_SIZE];

			LOGE("Program output log: ");

			GL_CHECK( glGetProgramInfoLog(m_programID, BUFFER_SIZE, &infoLen, buffer) );

			LOGE("\n%s",buffer);
		}
	}
}
