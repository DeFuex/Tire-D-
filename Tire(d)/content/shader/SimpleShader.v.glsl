#version 330

in vec3 position;

out vec3 _Position;


uniform mat4 matrixModel;
uniform mat4 matrixViewPerspective;
uniform float dTime;

void main(void)
{
   gl_Position = (matrixViewPerspective * matrixModel) * vec4((_Position = position)*(abs(sin(dTime))*0.3+0.85),1);
}