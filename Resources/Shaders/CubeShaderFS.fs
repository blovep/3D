precision mediump float;

uniform samplerCube u_cube;
varying vec3 v_pos;
void main()
{
	gl_FragColor = textureCube(u_cube, v_pos);
}
