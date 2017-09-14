#version 450 core
out vec4 FragColor;  
in vec3 color;
  
void main()
{
  FragColor = vec4(color, 1.0);
  //FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}