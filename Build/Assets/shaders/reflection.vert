#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out layout(location = 0) vec3 otexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

	vec3 position = vec3( model * vec4( vposition, 1 ) );
	vec3 normal = normalize( mat3(model) * vnormal );

	vec3 viewPosition = inverse(view)[3].xyz;
	vec3 viewDir = normalize(position - viewPosition);

	otexcoord = reflect(viewDir, normal);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);

}