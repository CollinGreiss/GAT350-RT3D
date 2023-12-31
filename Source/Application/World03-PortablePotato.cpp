#include "World03.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#define INTERLEAVE

namespace nc {


	bool World03::Initialize() {

		m_program = GET_RESOURCE( Program, "shaders/unlit_color.prog" );
		m_program->Use();

#ifdef INTERLEAVE

		float vertexData[] = {
		   -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
		   -0.8f,  0.8f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 1.0f
		};


		GLuint vbo;

		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );

		glGenVertexArrays( 1, &m_vao );
		glBindVertexArray( m_vao );
		glBindVertexBuffer( 0, vbo, 0, 6 * sizeof( GLfloat ) );

		glEnableVertexAttribArray( 0 );
		glVertexAttribFormat( 0, 3, GL_FLOAT, GL_FALSE, 0 );
		glVertexAttribBinding( 0, 0 );

		glEnableVertexAttribArray( 1 );
		glVertexAttribFormat( 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ) );
		glVertexAttribBinding( 1, 0 );



#else

		float positionData[] = {
		   -0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
		   -0.8f,  0.8f, 0.0f,
			0.8f,  0.8f, 0.0f
		};

		float colorData[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		};

		GLuint vbo[2];

		glGenBuffers( 1, vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( positionData ), positionData, GL_STATIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( colorData ), colorData, GL_STATIC_DRAW );

		glGenVertexArrays( 1, &m_vao );
		glBindVertexArray( m_vao );

		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glBindVertexBuffer( 0, vbo[0], 0, 3 * sizeof( GLfloat ) );

		glEnableVertexAttribArray( 1 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glBindVertexBuffer( 1, vbo[1], 0, 3 * sizeof( GLfloat ) );

#endif

		return true;

	}

	void World03::Shutdown() {

	}

	void World03::Update( float dt ) {

		m_angle -= dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_E ) ? m_speed * dt * 45 : 0;
		m_angle += dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_Q ) ? m_speed * dt * 45 : 0;

		m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_A ) ? m_speed * dt : 0;
		m_position.x -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_D ) ? m_speed * dt : 0;

		m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LSHIFT ) ? m_speed * dt : 0;
		m_position.y -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LCTRL ) ? m_speed * dt : 0;

		m_position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_W ) ? m_speed * dt : 0;
		m_position.z -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_S ) ? m_speed * dt : 0;

		m_time += dt;

		glm::mat4 position = glm::translate( glm::mat4 { 1 }, m_position );
		glm::mat4 rotation = glm::rotate( glm::mat4 { 1 }, glm::radians(m_angle ), glm::vec3( 1, 1, 1 ) );

		glm::mat4 model = position * rotation;
		GLint uniformModel = glGetUniformLocation( m_program->m_program, "model" );
		glUniformMatrix4fv( uniformModel, 1, GL_FALSE, glm::value_ptr( model ) );

		glm::mat4 view = glm::lookAt( glm::vec3( 0, 4, -5 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
		GLint uniformView = glGetUniformLocation( m_program->m_program, "view" );
		glUniformMatrix4fv( uniformView, 1, GL_FALSE, glm::value_ptr( view ) );

		glm::mat4 projection = glm::perspective( glm::radians( 70.0f ), (float) ENGINE.GetSystem<nc::Renderer>()->GetWidth() / ENGINE.GetSystem<nc::Renderer>()->GetHeight(), 0.01f, 100.0f);
		GLint uniformProjection = glGetUniformLocation( m_program->m_program, "projection" );
		glUniformMatrix4fv( uniformProjection, 1, GL_FALSE, glm::value_ptr( projection ) );

	}

	void World03::Draw( Renderer& renderer ) {

		// pre-render
		renderer.BeginFrame();

		// render
		glBindVertexArray( m_vao );
		glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

		// post-render
		renderer.EndFrame();

	}

}
