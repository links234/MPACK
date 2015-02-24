#ifndef MPACK_SHADERTYPES_HPP
#define MPACK_SHADERTYPES_HPP

#include "GLSLShader.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace MPACK
{
	namespace Graphics
	{
		class AbstractShaderType: public GLSLProgram
		{
		public:
			AbstractShaderType(const char* vertexShader, const char* fragmentShader, const char* header=NULL): GLSLProgram(vertexShader, fragmentShader, header){};

			virtual ~AbstractShaderType(){};

			virtual void BindAttributeLocations() = 0;
			virtual void UpdateUniforms() = 0;
			virtual void UpdateFrameUniforms() = 0;
			virtual void InitUniforms() = 0;
			virtual void SendVertexBuffer() = 0;
			virtual void EnableVertexAttributes() = 0;
			virtual void SendVertexBuffer(GLfloat *VA){}
			virtual void DisableVertexAttributes() = 0;
		};

		extern AbstractShaderType* Sprite_Shader;
		extern AbstractShaderType* FXAAII_Shader;
		extern AbstractShaderType* FXAAI_Shader;

		class ShaderType_Tex0Pass: public AbstractShaderType
		{
		public:
			ShaderType_Tex0Pass(const char* vertexShader, const char* fragmentShader, const char* header=NULL);
			~ShaderType_Tex0Pass();

			void BindAttributeLocations();
			void UpdateUniforms();
			void UpdateFrameUniforms();
			void InitUniforms();
			void SendVertexBuffer();
			void SendVertexBuffer(GLfloat *VAO);
			void EnableVertexAttributes();
			void DisableVertexAttributes();
		};

		class ShaderType_Sprite: public AbstractShaderType
		{
		public:
			ShaderType_Sprite(const char* vertexShader, const char* fragmentShader, const char* header=NULL);
			~ShaderType_Sprite();

			void BindAttributeLocations();
			void UpdateUniforms();
			void UpdateFrameUniforms();
			void InitUniforms();
			void SendVertexBuffer();
			void SendVertexBuffer(GLfloat *VA);
			void EnableVertexAttributes();
			void DisableVertexAttributes();
		};

		bool LoadShaders();
		void DeleteShaders();
	}
}

#endif

