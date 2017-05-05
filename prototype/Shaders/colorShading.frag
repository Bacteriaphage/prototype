#version 130
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentNormal;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec4 fragmentPosLightSpace;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.

out vec4 color;

uniform vec3 u_reverseLightDirection;

//uniform float time;
uniform sampler2D mySampler;
uniform sampler2D shadowMap;

float shadowCalculate(vec4 fragmentPosLightSpace){

	// perform perspective divide
    vec3 projCoords = fragmentPosLightSpace.xyz / fragmentPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    
	// Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    
	// Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    
	// Check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.5;

    return shadow;
}

void main() {

    //cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1
    //you simply do (cos(x) + 1.0) * 0.5
	//vec4 textureColor = texture(mySampler, fragmentUV);
	//color = fragmentColor;
    //Make crazy colors using time and position!

	vec3 normal = normalize(fragmentNormal);
    color = fragmentColor;
	
	float light = dot(normal, normalize(u_reverseLightDirection));
	if(light < 0.3) light = 0.2;
	float shadow = shadowCalculate(fragmentPosLightSpace);
	color = texture(mySampler, fragmentUV);
	color.xyz *= light;
	//color = texture(shadowMap, fragmentUV) * color;
	//color.xyz = (1.0-shadow) * color.xyz;
	//color = fragmentColor;
}