#version 330 core
out vec4 FragColor; //OUTPUT COLORS IN RGBA
in vec3 color; // INPUT COLOR FROM VERTEX SHADER

in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	//FragColor = vec4(color, 1.0f);

	FragColor = texture(tex0, texCoord);
}