#version 330

in vec3 position;
in vec2 texture0;


out vec3 _Position;
out vec2 _UV;

uniform mat4 matrixModel;
uniform mat4 matrixViewPerspective;
uniform float dTime;

void main(void)
{
   _UV = texture0;
   gl_Position = (matrixViewPerspective * matrixModel) * vec4(_Position = position,1);
}