#version 410 core

in VS_OUT
{
    vec4 color;
} fs_in;

out vec4 color;

void main(void)
{
    color = fs_in.color;
//    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,
//                 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,
//                 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),
//                 1.0);
}