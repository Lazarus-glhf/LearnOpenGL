#version 330 core
layout (location = 0) in vec3 aPos;   // set position attribute value to 0 
layout (location = 1) in vec3 aColor; // set color attribute value to  1

out vec3 ourColor; // output a color to fragment shader
out vec3 outPosition;
uniform vec3 pOffset;

void main()
{
	gl_Position = vec4(-aPos + pOffset / 2, 1.0);
	// outPosition = gl_Position.xyz;
	ourColor = aColor; // set ourColor as what we got from vertex data
}