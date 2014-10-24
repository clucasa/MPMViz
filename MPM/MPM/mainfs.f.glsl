uniform vec3 Color;
varying vec4 fnormal;
varying vec4 fpos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 LightPosition;

void main() 
{
     
    // Phong shading
    vec4 l_ambient  = vec4(0.6, 0.6, 0.6, 1.0);
    vec4 l_diffuse  = vec4(15.0, 15.0, 15.0, 1.0);
    vec4 l_specular = vec4(1.0, 0.0, 0.0, 1.0);
    
    vec4 m_ambient  = vec4(Color, 1.0);
    vec4 m_diffuse  = vec4(Color, 1.0);
    vec4 m_specular = vec4(1.0, 1.0, 1.0, 1.0);
    float shine = 100.0;
    
    // vertex to eye coords
    vec3 pos = (Model * View * fpos).xyz;
    
    // L = light_eye_coords -> pos
    vec3 L = normalize( (Model * View * vec4(LightPosition,1.0)).xyz - pos );
    vec3 E = normalize( -pos ); // E = pos -> eye
    vec3 H = normalize( L + E ); // halfway vector
    
    vec3 N = normalize( transpose(inverse(Model * View))*fnormal ).xyz;
    
    vec4 ambient = l_ambient * m_ambient;
    
    float dr = max( dot(L,N), 0.0 );
    vec4 diffuse = dr * (l_diffuse * m_diffuse);
    
    float sr = pow( max(dot(N,H), 0.0), shine );
    vec4 specular = sr * (l_specular * m_specular);
    if( dot(L,N) < 0.0) // if light is behind surface
    {
        specular = vec4(0.0,0.0,0.0,1.0);
    }
    
    vec4 col = ambient + diffuse + specular;
    col.a = 1.0f;

    gl_FragColor = col;//vec4(Color,1.0f);
}