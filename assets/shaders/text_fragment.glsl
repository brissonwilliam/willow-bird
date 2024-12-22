#version 410 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D text; // monocolored bitmap image of the glyph
uniform vec3 textColor; // rgb text color

void main()
{    
    // We first sample the color value of the bitmap texture.
    // Because the texture's data is stored in just its red component, we sample the r component of the texture as the sampled alpha value.
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);

    // By varying the output color's alpha value (last apram of vec4)
    // the resulting pixel will be transparent for all the glyph's background colors and non-transparent for the actual character pixels.
    // We also multiply the RGB colors by the textColor uniform to vary the text color.
    color = vec4(textColor, 1.0) * sampled;

} 
