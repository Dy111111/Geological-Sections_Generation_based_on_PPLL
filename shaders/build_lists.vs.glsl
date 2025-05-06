#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 map1;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform Mat{
	vec4 aAmbient;
	vec4 aDiffuse;
	vec4 aSpecular;
};
out vec4 Ambient;
out vec4 Diffuse;
out vec4 Specular;

out gl_PerVertex
{
    vec4 gl_Position;
};
out vec3 frag_position;
out vec3 frag_normal;

void main(void)
{
    
    frag_position = vec3( model * vec4(position, 1.0));
    //Normal =vec3(projection * vec4(mat3(transpose(inverse(view * model))) * aNormal,0.0));  
	frag_normal = mat3(transpose(inverse(model))) * normal;  
	Ambient = aAmbient;
	Diffuse = aDiffuse;
	Specular = aSpecular;
 
	
    gl_Position = projection * view * vec4(frag_position, 1.0);
}
