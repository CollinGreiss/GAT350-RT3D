#version 430

#define INVERT_MASK      ( 1 << 0 )
#define GERYSCALE_MASK   ( 1 << 1 )
#define COLORTINT_MASK   ( 1 << 2 )
#define GRAIN_MASK		 ( 1 << 3 )
#define SCANLINE_MASK	 ( 1 << 4 )
#define GAMER_MASK		 ( 1 << 5 )

in layout(location = 0) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D screenTexture;


uniform float blend = 1;
uniform uint params = 0;

uniform vec3 tint = vec3(0);
uniform int lineSpace = 2;

uniform float time = 0;

vec4 invert(in vec4 color) {

	return vec4( vec3(1) - color.rgb, color.a );

}

vec4 greyScale(in vec4 color) {

	return vec4( vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b) / 3, color.a);

}

vec4 colorTint(in vec4 color) {

	return vec4( color.rgb * tint, color.a);

}

float random(vec2 st) {

	return fract( sin( dot( st.xy, vec2(12.9898, 78.233) ) ) * 43758.5453 );

}

vec4 grain(in vec4 color) {

	return vec4(color.xyz * random(gl_FragCoord.xy + time), color.a);

}

vec4 scanline(in vec4 color) {

	return vec4(color.xyz * ( (int( mod(gl_FragCoord.y, lineSpace) ) == 0) ? 1 : 0 ), color.a);

}

vec4 gamer(in vec4 color) {

	return color * vec4(sin(time), sin(time - 2.09439510239), sin(time - 4.18879020479), 1);

}

void main() {
	
	vec4 basecolor = texture(screenTexture, ftexcoord);

	vec4 postprocess = basecolor;
		
	if (bool(params & COLORTINT_MASK))
		postprocess = colorTint(postprocess);
		
	if (bool(params & GAMER_MASK))
		postprocess = gamer(postprocess);

	if (bool(params & GERYSCALE_MASK))
		postprocess = greyScale(postprocess);
	
	if (bool(params & INVERT_MASK))
		postprocess = invert(postprocess);
	
	if (bool(params & GRAIN_MASK))
		postprocess = grain(postprocess);
	
	if (bool(params & SCANLINE_MASK))
		postprocess = scanline(postprocess);

	ocolor = mix(basecolor, postprocess, blend);

}