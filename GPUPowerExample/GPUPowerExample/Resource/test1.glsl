#version 300 es
precision highp float;
layout(location = 0) out vec4 color;
uniform sampler2D tex;
in vec2 uv;
void main()
{
    color = texture(tex, uv);
}
);
