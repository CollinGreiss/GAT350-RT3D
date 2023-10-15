#pragma once
#include "Renderer.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace nc {

	class VertexBuffer : public Resource {

	public:

		VertexBuffer();
		virtual ~VertexBuffer();

		bool Create( std::string name, ... ) override;
		void Draw( GLenum primitiveType = GL_TRIANGLES );
		void Bind() { glBindVertexArray( m_vao ); }

		void CreateVertexBuffer( GLsizei size, GLsizei vertexCount, GLvoid* data );
		void CreateIndexBuffer( GLenum indexType, GLsizei count, GLvoid* data );

		void SetAttribute( int index, GLint size, GLsizei stride, GLuint offset );

	protected:

		GLuint m_vao = 0;

		GLuint m_vbo = 0;
		GLuint m_vertexCount = 0;

		GLuint m_ibo = 0;
		GLuint m_indexCount = 0;
		GLenum m_indexType = 0;

	};

}