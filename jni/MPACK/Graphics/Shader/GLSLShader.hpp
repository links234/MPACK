#ifndef MPACK_GLSLSHADER_HPP
#define MPACK_GLSLSHADER_HPP

#include "Types.hpp"
#include "Resources.hpp"
#include "Log.hpp"

#include <map>
#include <string>
#include <vector>

namespace MPACK
{
	namespace Graphics
	{
		class GLSLProgram
		{
		public:
			struct GLSLShader
			{
				unsigned int id;
				std::string path;
				std::string source;
			};

			GLSLProgram(const char* vertexShader, const char* fragmentShader, const char* header=NULL);

			virtual ~GLSLProgram();

			bool Initialize();
			bool LinkProgram();

			void Unload();

			GLuint GetUniformLocation(const std::string& name);
			GLuint GetAttribLocation(const std::string& name);

			void SendUniform(const std::string& name, const int id);
			void SendUniform4x4(const std::string& name, const float* matrix, bool transpose=false);
			void SendUniform3x3(const std::string& name, const float* matrix, bool transpose=false);
			void SendUniform(const std::string& name, const float red, const float green,
							 const float blue, const float alpha);
			void SendUniform(const std::string& name, const float x, const float y,
							 const float z);
			void SendUniform(const std::string& name, const float scalar);

			void BindAttrib(unsigned int index, const std::string& attribName);

			void BindShader();

		private:
			static GLSLProgram* lastBindedShader;

			bool CompileShader(const GLSLShader& shader);
			void OutputShaderLog(unsigned int shaderID);
			void OutputProgramLog();

			GLSLShader m_vertexShader;
			GLSLShader m_fragmentShader;
			unsigned int m_programID;
			std::string m_header;

			std::map<std::string, GLuint> m_uniformMap;
			std::map<std::string, GLuint> m_attribMap;
		};
	}
}

#endif
