#version 120

varying vec2 texCoord;
uniform sampler2DRect baseTexture;
uniform float bloom;

void main() {
    vec4 sum, dry;
    
    for( int i = -3; i <= 3; i++ ) {
        for( int j = -3; j <= 3; j++ ) {
            sum += texture2DRect(baseTexture, texCoord + vec2(j, i) * 2.0) * 0.25;
        }
    }
    
    sum = sum * sum * 0.012;
    dry = texture2DRect(baseTexture, texCoord);
    
    gl_FragColor = bloom * (1.0 - ((1.0 - sum) * (1.0 - dry))) + ((1.0 - bloom) * dry);
}
