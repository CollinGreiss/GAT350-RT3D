#version 430

#define INVERT_MASK      ( 1 << 0 )
#define GERYSCALE_MASK   ( 1 << 1 )
#define COLORTINT_MASK   ( 1 << 2 )

in layout(location = 0) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D screenTexture;


uniform float blend = 1;
uniform vec3 tint = vec3(0);

uniform uint params = 0;

vec4 invert(in vec4 color) {

	return vec4( vec3(1) - color.rgb, color.a );

}

vec4 greyScale(in vec4 color) {

	return vec4( vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b) / 3, color.a);

}

vec4 colorTint(in vec4 color) {

	return vec4( color.rgb * tint, color.a);

}

void main() {
	
	vec4 basecolor = texture(screenTexture, ftexcoord);

	vec4 postprocess = basecolor;
		
	if (bool(params & COLORTINT_MASK))
		postprocess = colorTint(postprocess);

	if (bool(params & GERYSCALE_MASK))
		postprocess = greyScale(postprocess);
	
	if (bool(params & INVERT_MASK))
		postprocess = invert(postprocess);

	ocolor = mix(basecolor, postprocess, blend);

}