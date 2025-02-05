attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;

attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_WVP;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
v_color = a_color;
v_uv = a_uv;
gl_Position = u_WVP * posL;
}
   