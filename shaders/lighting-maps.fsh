

#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float time;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //vec3 inverseSpec = spec * (vec3(1.0) - vec3(texture(material.specular, TexCoords)));

    vec3 emission = vec3(0.0);
    //mask edge of crate
    if(texture(material.specular, TexCoords).r == 0.0) {
        emission = texture(material.emission, TexCoords).rgb;

        //movingf
        emission = texture(material.emission, TexCoords + vec2(0.0, time)).rgb;
        //fading
        emission = emission * ( (sin(time) * 0.5) + 0.5) * 2.0;
    }

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
}
