#version 120

varying vec2 texCoord;

void main() {
    texCoord = vec2(gl_MultiTexCoord0);
    gl_Position = ftransform();
}
