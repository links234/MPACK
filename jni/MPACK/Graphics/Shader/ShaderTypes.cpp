#include "ShaderTypes.hpp"
#include "ShaderUniform.hpp"
#include "Vertex.hpp"

namespace MPACK
{
	namespace Graphics
	{
		ShaderType_Sprite::ShaderType_Sprite(const char* vertexShader, const char* fragmentShader, const char* header)
			: AbstractShaderType(vertexShader, fragmentShader, header)
		{
		}
		ShaderType_Sprite::~ShaderType_Sprite()
		{
		}
		void ShaderType_Sprite::BindAttributeLocations()
		{
			BindAttrib(0, "a_Vertex");
			BindAttrib(1, "a_TexCoord");
			BindAttrib(2, "a_Color");
			BindAttrib(3, "a_ShadeType");
		}
		void ShaderType_Sprite::UpdateUniforms()
		{
			SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
		}
		void ShaderType_Sprite::UpdateFrameUniforms()
		{
		}
		void ShaderType_Sprite::InitUniforms()
		{
			SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
			SendUniform("texture0",0);
		}
		void ShaderType_Sprite::SendVertexBuffer()
		{
			GL_CHECK( glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(0)) );
			GL_CHECK( glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*2)) );
			GL_CHECK( glVertexAttribPointer((GLint)2,4,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*4)) );
			GL_CHECK( glVertexAttribPointer((GLint)3,1,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),BUFFER_OFFSET(sizeof(GLfloat)*8)) );
		}
		void ShaderType_Sprite::SendVertexBuffer(GLfloat *VA)
		{
			GL_CHECK( glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),VA) );
			GL_CHECK( glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*2))) );
			GL_CHECK( glVertexAttribPointer((GLint)2,4,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*4))) );
			GL_CHECK( glVertexAttribPointer((GLint)3,1,GL_FLOAT,GL_FALSE,sizeof(SpriteVertex),(GLvoid*)((intptr_t)(VA)+(intptr_t)(sizeof(GLfloat)*8))) );
		}
		void ShaderType_Sprite::EnableVertexAttributes()
		{
			GL_CHECK( glEnableVertexAttribArray(0) );
			GL_CHECK( glEnableVertexAttribArray(1) );
			GL_CHECK( glEnableVertexAttribArray(2) );
			GL_CHECK( glEnableVertexAttribArray(3) );
		}
		void ShaderType_Sprite::DisableVertexAttributes()
		{
			GL_CHECK( glEnableVertexAttribArray(0) );
			GL_CHECK( glEnableVertexAttribArray(1) );
			GL_CHECK( glEnableVertexAttribArray(2) );
			GL_CHECK( glEnableVertexAttribArray(3) );
		}

		ShaderType_Tex0Pass::ShaderType_Tex0Pass(const char* vertexShader, const char* fragmentShader, const char* header)
			: AbstractShaderType(vertexShader, fragmentShader, header)
		{
		}
		ShaderType_Tex0Pass::~ShaderType_Tex0Pass()
		{
		}
		void ShaderType_Tex0Pass::BindAttributeLocations()
		{
			BindAttrib(0, "a_Vertex");
			BindAttrib(1, "a_TexCoord0");
		}
		void ShaderType_Tex0Pass::UpdateUniforms()
		{
		}
		void ShaderType_Tex0Pass::UpdateFrameUniforms()
		{
			SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
			SendUniform("texture0",0);
		}
		void ShaderType_Tex0Pass::InitUniforms()
		{
			SendUniform4x4("projection_matrix",(GLfloat*)(&ShaderUniform::projectionMatrix));
			SendUniform("texture0",0);
		}
		void ShaderType_Tex0Pass::SendVertexBuffer()
		{
			GL_CHECK( glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*4,BUFFER_OFFSET(0)) );
			GL_CHECK( glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*4,BUFFER_OFFSET(sizeof(GLfloat)*2)) );
		}
		void ShaderType_Tex0Pass::SendVertexBuffer(GLfloat *VAO)
		{
			GL_CHECK( glVertexAttribPointer((GLint)0,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*4,VAO) );
			GL_CHECK( glVertexAttribPointer((GLint)1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*4,(GLvoid*)((intptr_t)VAO+(intptr_t)sizeof(GLfloat)*2)) );
		}
		void ShaderType_Tex0Pass::EnableVertexAttributes()
		{
			GL_CHECK( glEnableVertexAttribArray(0) );
			GL_CHECK( glEnableVertexAttribArray(1) );
		}
		void ShaderType_Tex0Pass::DisableVertexAttributes()
		{
			GL_CHECK( glDisableVertexAttribArray(0) );
			GL_CHECK( glDisableVertexAttribArray(1) );
		}

		AbstractShaderType* Sprite_Shader;
		AbstractShaderType* FXAAII_Shader;
		AbstractShaderType* FXAAI_Shader;

		#ifdef ANDROID_PLATFORM
		#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGLES2/Sprite.vert"
		#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGLES2/Sprite.frag"
		#define		VERTEXSHADER_FXAAI		"@Shaders/OpenGLES2/PostFX/FXAAI.vert"
		#define		FRAGMENTSHADER_FXAAI	"@Shaders/OpenGLES2/PostFX/FXAAI.frag"
		#define		VERTEXSHADER_FXAAII		"@Shaders/OpenGLES2/PostFX/FXAAII.vert"
		#define		FRAGMENTSHADER_FXAAII	"@Shaders/OpenGLES2/PostFX/FXAAII.frag"
		#elif	defined(WINDOWS_PLATFORM)
		#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGL2/Sprite.vert"
		#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGL2/Sprite.frag"
		#define		VERTEXSHADER_FXAAI		"@Shaders/OpenGL2/PostFX/FXAAI.vert"
		#define		FRAGMENTSHADER_FXAAI	"@Shaders/OpenGL2/PostFX/FXAAI.frag"
		#define		VERTEXSHADER_FXAAII		"@Shaders/OpenGL2/PostFX/FXAAII.vert"
		#define		FRAGMENTSHADER_FXAAII	"@Shaders/OpenGL2/PostFX/FXAAII.frag"
		#elif	defined(LINUX_PLATFORM)
		#define		VERTEXSHADER_SPRITE		"@Shaders/OpenGL2/Sprite.vert"
		#define		FRAGMENTSHADER_SPRITE	"@Shaders/OpenGL2/Sprite.frag"
		#define		VERTEXSHADER_FXAAI		"@Shaders/OpenGL2/PostFX/FXAAI.vert"
		#define		FRAGMENTSHADER_FXAAI	"@Shaders/OpenGL2/PostFX/FXAAI.frag"
		#define		VERTEXSHADER_FXAAII		"@Shaders/OpenGL2/PostFX/FXAAII.vert"
		#define		FRAGMENTSHADER_FXAAII	"@Shaders/OpenGL2/PostFX/FXAAII.frag"
		#endif

		bool LoadShaders()
		{
			Sprite_Shader = (AbstractShaderType*)(new ShaderType_Sprite(VERTEXSHADER_SPRITE,FRAGMENTSHADER_SPRITE));
			if(!Sprite_Shader->Initialize())
			{
				return false;
			}
			Sprite_Shader->BindAttributeLocations();
			if(!Sprite_Shader->LinkProgram())
			{
				return false;
			}

			FXAAII_Shader = (AbstractShaderType*)(new ShaderType_Tex0Pass(VERTEXSHADER_FXAAII,FRAGMENTSHADER_FXAAII));
			if(!FXAAII_Shader->Initialize())
			{
				return false;
			}
			FXAAII_Shader->BindAttributeLocations();
			if(!FXAAII_Shader->LinkProgram())
			{
				return false;
			}

			FXAAI_Shader = (AbstractShaderType*)(new ShaderType_Tex0Pass(VERTEXSHADER_FXAAI,FRAGMENTSHADER_FXAAI));
			if(!FXAAI_Shader->Initialize())
			{
				return false;
			}
			FXAAI_Shader->BindAttributeLocations();
			if(!FXAAI_Shader->LinkProgram())
			{
				return false;
			}

			return true;
		}

		void DeleteShaders()
		{
			if(Sprite_Shader)
			{
				delete Sprite_Shader;
			}
			if(FXAAII_Shader)
			{
				delete FXAAII_Shader;
			}
			if(FXAAI_Shader)
			{
				delete FXAAI_Shader;
			}
		}
	}
}
