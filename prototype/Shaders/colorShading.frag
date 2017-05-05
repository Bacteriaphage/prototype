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

uniform vec3 u_reverseLightDirection;

//uniform float time;
uniform sampler2D mySampler;
uniform sampler2D shadowMap;

float shadowCalculate(vec4 fragmentPosLightSpace){
	float bias = max(0.01 * (1.0 - dot(fragmentNormal, normalize(u_reverseLightDirection))), 0.001);
	// perform perspective divide
    vec3 projCoords = fragmentPosLightSpace.xyz / fragmentPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    
	// Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).x; 
    
	// Get depth of current fragment from light's perspective
    float currentDepth = 10.0 / fragmentPosLightSpace.z;
    
	// Check whether current frag pos is in shadow
    float shadow = currentDepth + bias > closestDepth ? 0.0 : 1.0;

    return shadow;
}

void main() {

	vec3 normal = normalize(fragmentNormal);
    
	
	float light = dot(normal, normalize(u_reverseLightDirection));
	if(light < 0.3) light = 0.2;
	float shadow = shadowCalculate(fragmentPosLightSpace);
	
	color = fragmentColor;
	//float shadow = shadow2DProj(shadowMap, fragmentPosLightSpace).r;
	//color.xyz = shadow * color.xyz;
	//color = fragmentColor;
	
	//float depth = texture(shadowMap, fragmentUV).r;
	//color = vec4(vec3(1.0-depth), 1.0);
	color = texture(mySampler, fragmentUV);
	//color = texture(shadowMap, fragmentUV);
	//float distance = 1.0 / fragmentPosLightSpace.z;
	//color = vec4(shadow, shadow, shadow, 1.0);
	color.xyz = color.xyz * ((1.0 - shadow)+0.3) * light;
}