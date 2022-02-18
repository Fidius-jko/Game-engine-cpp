#pragma once

namespace Engine {
	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexSource, const char* fragmentSource);
		ShaderProgram(ShaderProgram&&);
		ShaderProgram& operator=(ShaderProgram&&);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		void Bind() const;
		static void Unbind();

		bool isCompiled() const { return mIsCompiled; };
	private:
		bool mIsCompiled = false;
		unsigned int ID = 0;
	};
}