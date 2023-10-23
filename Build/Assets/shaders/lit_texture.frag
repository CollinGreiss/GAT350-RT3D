#version 430

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;
in layout(location = 3) vec4 fcolor;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform struct Material {
	
	vec3 diffuse;
	vec3 specular;
	float shininess;

	vec2 offset;
	vec2 tiling;

} material;

uniform struct Light {
	
	vec3 position;
	vec3 color;

} light;

uniform vec3 ambientLight = vec3( 0.2, 0.2, 0.2 );

vec3 ads ( in vec3 position, in vec3 normal) {
	
	vec3 ambient = ambientLight;

	vec3 lightDir = normalize(light.position - position);
	float intensity = max( dot(lightDir, normal), 0 );
	vec3 diffuse = material.diffuse * light.color * intensity;

	vec3 specular = vec3(0);

	if (intensity > 0) {

		vec3 reflection = reflect(-lightDir, normal);
		vec3 viewDir = normalize(-position);
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity;

	}

	return ambient + diffuse + specular;

}

void main() {

	mat4 modelView = view * model;

	vec3 normal = normalize( mat3( modelView ) * fnormal );;
	vec3 position = vec3 ( modelView * vec4(fposition, 1) );

	ocolor = texture(tex, ftexcoord) * vec4( ads(position, normal), 1 );

}