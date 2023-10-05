#include "World02.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

namespace nc {


	bool World02::Initialize() {

		const char* vertexShader =
			"#version 430\n"
			"layout (location=0) in vec3 position;"
			"layout (location=1) in vec3 color;"
			"layout (location=0) out vec3 ocolor;"
			"void main() {"
			"  ocolor = color;"
			"  gl_Position = vec4(position, 1.0);"
			"}";



		const char* fragmentShader =
			"#version 430\n"
			"layout (location=0) in vec3 color;"
			"out vec4 ocolor;"
			"void main() {"
			"  ocolor = vec4(color, 1);"
			"}";

		GLuint vs = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vs, 1, &vertexShader, NULL );
		glCompileShader( vs );

		GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fs, 1, &fragmentShader, NULL );
		glCompileShader( fs );

		GLuint program = glCreateProgram();
		glAttachShader( program, vs );
		glAttachShader( program, fs );
		glLinkProgram( program );
		glUseProgram( program );

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

		glGenBuffers( 1, vbo);
		glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( positionData ), positionData, GL_STATIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( colorData ), colorData, GL_STATIC_DRAW );

		glGenVertexArrays( 1, &m_vao );
		glBindVertexArray( m_vao );

		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glBindVertexBuffer( 0, vbo[0], 0, 3 * sizeof( GLfloat ));

		glEnableVertexAttribArray( 1 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glBindVertexBuffer( 1, vbo[1], 0, 3 * sizeof( GLfloat ) );

		return true;

	}

	void World02::Shutdown() {

	}

	void World02::Update( float dt ) {

		m_angle -= dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_E ) ? dt * 180 : 0;
		m_angle += dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_Q ) ? dt * 180 : 0;

		m_position.x -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_A ) ? dt * 5 : 0;
		m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_D ) ? dt * 5 : 0;

		m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_W ) ? dt * 5 : 0;
		m_position.y -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_S ) ? dt * 5 : 0;

		m_time += dt;

	}

	void World02::Draw( Renderer& renderer ) {

		// pre-render
		renderer.BeginFrame();

		// render
		glBindVertexArray( m_vao );
		glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

		// post-render
		renderer.EndFrame();

	}

}
