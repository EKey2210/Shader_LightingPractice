#version 150
#define PI 3.14159265359

uniform mat4 modelViewProjectionMatrix;
uniform mat4 invMatrix;
uniform vec3 lightDirection;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;

in vec4 position;
in vec4 color;
in vec3 normal;
in vec2 texcoord;

out vec4 vColor;

void main(){
  vec3 invLight = normalize(invMatrix * vec4(lightDirection, 0.0)).xyz;
  vec3 invEye = normalize(invMatrix * vec4(eyeDirection, 0.0)).xyz;
  vec3 halfVec = normalize(invLight+invEye);
  float diffuse  = clamp(dot(normal, invLight), 0.1, 1.0);
  float specular = pow(clamp(dot(normal, halfVec), 0.0, 1.0), 10.0);
  vec4 light = color * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0);
  vColor = light + ambientColor;
  gl_Position = modelViewProjectionMatrix * position;
}
