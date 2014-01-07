#version 330

uniform sampler2D sampler;
uniform bool Mirror;
uniform float LensOffset = 0.0;
uniform float ViewportAspectRatio = 1.0;

in vec2 vTexCoord;
in vec2 vPosition;
out vec4 FragColor;

void main() {
  vec2 warpedTexCoord = vTexCoord;
  float len = length(warpedTexCoord) * 3.14159 / 2.0;
  float warp = cos(len);
  warpedTexCoord /= warp;

  // now correct for the lens offset
  float eyeLensOffset = LensOffset;
  eyeLensOffset *= (Mirror ? -1 : 1);

  warpedTexCoord.y *= ViewportAspectRatio;
  warpedTexCoord.x += eyeLensOffset;

  warpedTexCoord += 1.0;
  warpedTexCoord /= 2.0;

  if (!all(equal(clamp(warpedTexCoord, 0.0, 1.0), warpedTexCoord))) {
    FragColor = vec4(Mirror ? 0.4 : 0.0, 0.4, Mirror ? 0.0 : 0.4, 1.0);
  } else {
    FragColor = texture(sampler, warpedTexCoord);
  }
//  FragColor = vec4(abs(vTexCoord.x), abs(vTexCoord.y), len, 1);
}

