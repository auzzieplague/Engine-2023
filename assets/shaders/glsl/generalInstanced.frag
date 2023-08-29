#version 330 core


in vec3 fragPos; // for lighting calcs
in vec2 fragUV;
in vec3 fragNormal;

struct Material {
    vec3 ambientColor;
    vec3 specularColor;
    float shininess;

    sampler2D diffuseTexture;
    sampler2D normalTexture;
};

uniform Material material;
uniform vec3 camera;
uniform vec3 highlight;

out vec4 fragColor;

void main()
{
    vec4 textureColour = texture(material.diffuseTexture, fragUV);
    vec3 normal = normalize(texture(material.normalTexture, fragUV).rgb * 2.0 - 1.0);
    vec3 diffuseColor = textureColour.rgb;


    // Light properties
    vec3 lightPosition = vec3(0, 5, -10.5);
    vec3 lightColor = vec3(1,1,1);
    float specularStrength =0.5;

    // Light attenuation
    float constant = 1.0;
    float linear = 0.009;
    float quadratic = 0.0032;

    // Calculate the light direction and distance
    vec3 lightDir = normalize(lightPosition - fragPos);
    float distance = length(lightPosition - fragPos);

    // Calculate the ambient light component
    vec3 ambient = material.ambientColor * diffuseColor;

    // Calculate the diffuse light component
    float diffuseFactor = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseColor * lightColor * diffuseFactor;

    // Calculate the specular light component
    vec3 viewDir = normalize(camera - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specularColor * lightColor * specularFactor * specularStrength;

    // Calculate the attenuation factor
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    // Calculate the final fragment color
    vec3 finalColor = (ambient + diffuse + specular) * attenuation;
    finalColor *= 1;

    // Apply the final color to the fragment
    fragColor = vec4(finalColor, 0.5);
//fragColor =  textureColour;
}
