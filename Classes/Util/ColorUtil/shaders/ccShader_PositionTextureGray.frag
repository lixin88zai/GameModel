//
//  ccShader_PositionTextureGray.frag
//
//  Created by 曾琪 on 14-6-13.
//
//
const char* ccPositionTextureGray_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
    vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
    float gray = dot(v_orColor.rgb, vec3(0.300, 0.300, 0.330));
    gl_FragColor = vec4(gray, gray, gray, v_orColor.a);
}
);