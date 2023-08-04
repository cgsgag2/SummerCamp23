/* */
layout(location = 0) in vec3 InPosition;

out vec4 in_color;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  // in_color = vec4(InPosition, 1);
  in_color = vec4(Ka, 1);
} 