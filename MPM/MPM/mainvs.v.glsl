attribute  vec4 vPosition;
attribute  vec4 vNormal;
varying vec4 fnormal;
varying vec4 fpos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    fnormal = vNormal;
    fpos = vPosition;
    gl_Position = Projection * View * Model * vPosition;
}