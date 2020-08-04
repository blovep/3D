attribute vec3 a_posL;

varying vec3 v_pos;
uniform mat4 u_WVP;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_WVP * posL;
v_pos = a_posL;
}
   