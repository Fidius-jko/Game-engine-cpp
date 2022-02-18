#include "CORE/log.hpp"
#include "shaderProgram.hpp"

#include <glad/glad.h>

namespace Engine {
	bool createShader(const char* source, const GLenum type, GLuint& shaderID) {
		shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);

		GLint succes;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (!succes) {
			char infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			LOG_CRITICAL("Shader compilation error:\n{}", infoLog);
			return false;
		}
		return true;
	}

	ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource){
		GLuint vertexShader;
		if (!createShader(vertexSource, GL_VERTEX_SHADER, vertexShader)) {
			LOG_CRITICAL("VERTEX SHADER: compilation time error!");
			glDeleteShader(vertexShader);
			return;
		}

		GLuint fragmentShader;
		if (!createShader(fragmentSource, GL_FRAGMENT_SHADER, fragmentShader)) {
			LOG_CRITICAL("FRAGMENT SHADER: compilation time error!");
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			return;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLchar info_log[1024];
			glGetProgramInfoLog(ID, 1024, nullptr, info_log);
			LOG_CRITICAL("SHADER PROGRAM: Link-time error:\n{0}", info_log);
			glDeleteProgram(ID);
			ID = 0;
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}
		else {
			mIsCompiled = true;
		}
		
		glDetachShader(ID, vertexShader);
		glDetachShader(ID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(ID);
	}

	void ShaderProgram::Bind() const {
		glUseProgram(ID);
	}

	void ShaderProgram::Unbind() {
		glUseProgram(0);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) {
		glDeleteProgram(ID);
		ID = shaderProgram.ID;
		mIsCompiled = shaderProgram.mIsCompiled;

		shaderProgram.ID = 0;
		shaderProgram.mIsCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) {
		ID = shaderProgram.ID;
		mIsCompiled = shaderProgram.mIsCompiled;

		shaderProgram.ID = 0;
		shaderProgram.mIsCompiled = false;
	}

}