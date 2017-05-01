#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 vertexNormal;

uniform mat4 u_matrix;
uniform mat4 u_model;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec4 fragmentColor;
out vec2 fragmentUV;

//uniform float time;

void main() {
    //Set the x,y position on the screen
    gl_Position = u_matrix * vec4(vertexPosition, 1.0);
    
    fragmentColor = vertexColor;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);

	
	fragmentNormal = mat3(u_model) * vertexNormal;

}