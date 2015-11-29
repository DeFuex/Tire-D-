#version 330

out vec3 color;

in vec3 _Position;

void main(void)
{
    color = _Position;
}