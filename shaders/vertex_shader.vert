#version 430 core

layout(location=0) in vec2 pos;

out vec2 uv;

void main()
{
	uv = 0.5 * (pos + 1.0);
	uv.y = -uv.y;
	gl_Position = vec4(pos, 0.0, 1.0);
}
