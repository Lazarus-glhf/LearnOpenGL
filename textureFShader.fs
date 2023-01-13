#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D  ourTexture2;

void main()
{
    FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, vec2((TexCoord.x + 0.5) * 0.1, (TexCoord.y + 0.1) * 0.5)), 0.5);
    // FragColor = texture(ourTexture, TexCoord);
}