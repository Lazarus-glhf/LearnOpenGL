#version 330 core
out vec4 FragColor;  

in vec3 ourColor;
in vec3 outPosition;

uniform vec3 pOffset;

void main()
{
	//FragColor = vec4(outPosition, 1.0f);
	 FragColor = vec4(ourColor + pOffset, 1.0);
}