#ifndef SHADERTYPES_HPP
#define SHADERTYPES_HPP

#include "GLSLShader.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class AbstractProgramType: public GLSLProgram
{
public:
	AbstractProgramType(const char* vertexShader, const char* fragmentShader, const char* header=NULL): GLSLProgram(vertexShader, fragmentShader, header){};
	virtual ~AbstractProgramType(){};

	virtual void BindAttributeLocations() = 0;
	virtual void UpdateUniforms() = 0;
	virtual void UpdateFrameUniforms() = 0;
	virtual void InitUniforms() = 0;
	virtual void SendVertexBuffer() = 0;
	virtual void EnableVertexAttributes() = 0;
	virtual void SendVertexBuffer(GLfloat *VA){}
	virtual void DisableVertexAttributes() = 0;
};

class ProgramType_Vertex3fPos4fColor: public AbstractProgramType
{
public:
	ProgramType_Vertex3fPos4fColor(const char* vertexShader, const char* fragmentShader, const char* header=NULL);
	~ProgramType_Vertex3fPos4fColor();

	void BindAttributeLocations();
	void UpdateUniforms();
	void UpdateFrameUniforms();
	void InitUniforms();
	void SendVertexBuffer();
	void SendVertexBuffer(GLfloat *VA);
	void EnableVertexAttributes();
	void DisableVertexAttributes();
};

class ProgramType_Sprite: public AbstractProgramType
{
public:
	ProgramType_Sprite(const char* vertexShader, const char* fragmentShader, const char* header=NULL);
	~ProgramType_Sprite();

	void BindAttributeLocations();
	void UpdateUniforms();
	void UpdateFrameUniforms();
	void InitUniforms();
	void SendVertexBuffer();
	void SendVertexBuffer(GLfloat *VA);
	void EnableVertexAttributes();
	void DisableVertexAttributes();
};

class ProgramType_Basic2: public AbstractProgramType
{
public:
	ProgramType_Basic2(const char* vertexShader, const char* fragmentShader, const char* header=NULL);
	~ProgramType_Basic2();

	void BindAttributeLocations();
	void UpdateUniforms();
	void UpdateFrameUniforms();
	void InitUniforms();
	void SendVertexBuffer();
	void SendVertexBuffer(GLfloat *VA);
	void EnableVertexAttributes();
	void DisableVertexAttributes();
};

#endif

