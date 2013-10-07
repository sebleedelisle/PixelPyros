#version 120

varying vec2 texCoord;
uniform sampler2DRect baseTexture;
uniform float blackPoint;
uniform float gamma;
uniform float whitePoint;
uniform float bloom;

vec4 adjustLevels(vec4 texel) {
    vec3 col = texel.rgb;
    
    vec3 diff = vec3(whitePoint) - vec3(blackPoint);
    if( diff == vec3(0.0) ) {
        diff += vec3(0.00001);
    }
    
    float g = gamma;
    if( g == 0.0f ) {
        g += 0.00001;
    }
    
    vec3 adjusted = min(max(col - vec3(blackPoint), vec3(0.0)) / (diff), vec3(1.0));
    
    return vec4(pow(adjusted, vec3(1.0 / gamma)), 1.0);
}

vec4 bloomFilter() {
    vec4 sum = vec4(0.0);
    vec4 dry = adjustLevels( texture2DRect(baseTexture, texCoord.xy) );
    vec4 raw;

    for( int i = -3; i <= 3; i++ ) {
        for( int j = -3; j <= 3; j++ ) {
            raw = texture2DRect(baseTexture, texCoord + vec2(j, i) ) * 0.25;
            sum += adjustLevels( raw );
        }
    }
    
    sum = sum / 49.0;
    
    return bloom * (1.0 - ((1.0 - sum) * (1.0 - dry))) + ((1.0 - bloom) * dry);
}

void main() {
    
    vec4 col = bloomFilter();
    
    gl_FragColor = col;
}