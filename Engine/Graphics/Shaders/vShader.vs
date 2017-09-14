#version 450 core
layout (location = 0) in vec3 position;   // the position variable has attribute position 0
//layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
  
out vec3 color; // output a color to the fragment shader

//uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{

	//gl_Position = transform * vec4(position, 1.0);
    
	gl_Position = projection * view * model * vec4(position, 1.0);
	
	//gl_Position = vec4(position, 1.0);
	color = vec3(position.x * sin(time) + 0.2, 0.3, position.y * cos(time) + 0.2);
	//color = vec3(position.x + 0.5, 0.3, position.y + 0.2);
    //ourColor = aColor; // set ourColor to the input color we got from the vertex data
} 