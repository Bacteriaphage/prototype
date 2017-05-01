#version 130
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentNormal;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform vec3 u_reverseLightDirection;
//uniform float time;
//uniform sampler2D mySampler;

void main() {

    //cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1
    //you simply do (cos(x) + 1.0) * 0.5
	//vec4 textureColor = texture(mySampler, fragmentUV);
	//color = fragmentColor;
    //Make crazy colors using time and position!

	vec3 normal = normalize(fragmentNormal);
    color = fragmentColor;
	float light = dot(normal, u_reverseLightDirection);
	if(light < 0.0) light = 0.0;
	color.xyz *= light;
}