#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
in layout(location = 3) vec4 vcolor;

out layout(location = 0) vec3 oposition;
out layout(location = 1) vec3 onormal;
out layout(location = 2) vec2 otexcoord;
out layout(location = 3) vec4 ocolor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

	oposition = vposition;
	onormal = vnormal;
	otexcoord = otexcoord;
	ocolor = vcolor;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);

}