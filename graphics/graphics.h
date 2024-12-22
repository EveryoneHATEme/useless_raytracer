#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>


#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	bool hasError = false;
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		hasError = true;
	}
	return !hasError;
}

class Shader
{
private:
	GLuint ID;

private:
	void readShader(const char* path, std::string& destination) const;
	GLuint initializeShader(const char* path, GLenum shaderType) const;
	GLint getUniformLocation(const std::string& name) const;

public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath, const char* computePath);
	~Shader();

	GLuint getID() const;
	void use() const;

	void setInt(const std::string& name, int source) const;
	void setVec3(const std::string& name, const glm::vec3& source) const;
	void setMat4(const std::string& name, const glm::mat4& source) const;
};


class ShaderStorageBuffer
{
private:
	GLuint ID;

public:
	ShaderStorageBuffer() = default;
	ShaderStorageBuffer(size_t size);
	ShaderStorageBuffer(const void* data, size_t size);
	~ShaderStorageBuffer();

	void setBindingPoint(unsigned int bindingPoint) const;

	void bind() const;
	void unbind() const;
};


class Texture
{
private:
	GLuint ID;

public:
	Texture() = default;
	Texture(unsigned int width, unsigned int height);
	~Texture();

	void bind(unsigned int index) const;
	void unbind() const;

	GLuint getID() const { return this->ID; }
};


class UniformBuffer
{
private:
	GLuint ID;
	unsigned int binding;

public:
	UniformBuffer() = default;
	UniformBuffer(unsigned int size, unsigned int bindingPoint);
	UniformBuffer(const void* data, unsigned int size, unsigned int bindingPoint);
	~UniformBuffer();

	void setShaderBinding(GLuint shader, const std::string& name) const;
	void setShaderBinding(const Shader& shader, const std::string& name) const;

	void bind() const;
	void unbind() const;
};


class VertexBuffer
{
private:
	GLuint ID;

public:
	VertexBuffer() = default;
	VertexBuffer(size_t size, const void* data);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}

		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout()
		: stride(0)
	{}

	template<typename T>
	void push(unsigned int count)
	{
		return;
	}

	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
	inline unsigned int getStride() const { return stride; }
};

class VertexArray
{
private:
	unsigned int ID;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addBuffer(VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
};
