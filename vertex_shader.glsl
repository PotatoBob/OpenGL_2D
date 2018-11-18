attribute vec2 position;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main(){
    gl_Position = projectionMatrix * modelMatrix * vec4(position, 0, 1);
}