#version 330

out vec3 color;

in vec3 _Position;
in vec2 _UV;


uniform sampler2D textureSimple;

void main(void)
{
    color = texture2D( textureSimple, _UV ).xyz;
}