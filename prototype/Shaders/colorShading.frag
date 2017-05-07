#version 130
//The fragment shader operates on each pixel in a given polygon
in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec4 fragmentPosLightSpace;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.

out vec4 color;
uniform float u_scene;
uniform vec3 u_reverseLightDirection;

//uniform float time;
uniform sampler2D mySampler;
uniform sampler2D shadowMap;

float shadowCalculate(vec4 fragmentPosLightSpace){
	//float bias = 0.05;
	float bias = max(0.3 * (1.0 - dot(fragmentNormal, normalize(u_reverseLightDirection))), 0.05);
	// perform perspective divide
    vec3 projCoords = fragmentPosLightSpace.xyz / fragmentPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    
	// Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	vec4 shadowData = texture(shadowMap, projCoords.xy);
    float closestDepth = shadowData.x / 100.0 + shadowData.y /10.0 + shadowData.z + shadowData.w * 10.0; 
	//closestDepth /= 10.0;
	closestDepth = (closestDepth<0.01) ? 100.0 : closestDepth;
	// Get depth of current fragment from light's perspective
	float currentDepth = fragmentPosLightSpace.z;
	//currentDepth /= 10.0;
    //currentDepth = (currentDepth<0.01) ? 1.0 : currentDepth;
	// Check whether current frag pos is in shadow
    float shadow = currentDepth < closestDepth + bias ? 0.0 : 1.0;
	
    return shadow;
}

void main() {

	vec3 normal = normalize(fragmentNormal);
    
	
	float light = dot(normal, normalize(u_reverseLightDirection));
	if(light < 0.1) light = 0.1;
	float shadow = shadowCalculate(fragmentPosLightSpace);
	color = texture(mySampler, fragmentUV);
	if(u_scene < 1.0)
		color.xyz = color.xyz * ((1.0 - shadow)+0.3) * light;
	//color.xyz = vec3(1.0, 1.0, 1.0) * shadow;
}