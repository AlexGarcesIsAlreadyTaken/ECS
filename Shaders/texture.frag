
#version 330 core

uniform sampler2D texture0;

out vec4 FragColor;

in vec2 TexCoord;
uniform vec3 tint;

void main() {
  //FragColor = vec4(TexCoord, sqrt(TexCoord.x*TexCoord.x + TexCoord.y*TexCoord.y), 1.0);
  vec4 color = texture(texture0, TexCoord);
  if (color.a < 0.5) discard;
  FragColor = color * vec4(tint, 1.0);
}
