#version 120

void main() {
    float xVal = gl_FragCoord.x;
    float yVal = gl_FragCoord.y;
    
    if( mod(xVal, 2.0) == 0.5 && mod(yVal, 4.0) == 0.5 ) {
        gl_FragColor = gl_Color;
    } else {
        gl_FragColor.a = 0.0;
    }
}
