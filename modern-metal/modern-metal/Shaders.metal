#include <metal_stdlib>
#include <simd/simd.h>

// Including header shared between this Metal shader code and Swift/C code executing Metal API commands
#include "Shaders_StructBridgingHeader.h"

using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float3 worldNormal;
    float3 worldPosition;
    float2 texCoords;
};

vertex VertexOut vertex_main(VertexIn vertexIn [[stage_in]],
                             constant const VertexUniforms &uniforms [[buffer(ShaderBufferIndex1)]])
{
    VertexOut vertexOut;
    float4 worldPosition = uniforms.modelMatrix * float4(vertexIn.position, 1);
    vertexOut.position = uniforms.viewProjectionMatrix * worldPosition;
    vertexOut.worldPosition = worldPosition.xyz;
    vertexOut.worldNormal = uniforms.normalMatrix * vertexIn.normal;
    vertexOut.texCoords = vertexIn.texCoords;
    return vertexOut;
}

fragment float4 fragment_main(VertexOut fragmentIn [[stage_in]],
                              constant const FragmentUniforms &uniforms [[buffer(ShaderBufferIndex0)]],
                              texture2d<float, access::sample> baseColorTexture [[texture(FragmentTextureIndex0)]],
                              sampler baseColorSampler [[sampler(0)]])
{
    float3 baseColor = baseColorTexture.sample(baseColorSampler, fragmentIn.texCoords).rgb;
    float3 specularColor = uniforms.specularColor;
    
    float3 N = normalize(fragmentIn.worldNormal);
    float3 V = normalize(uniforms.cameraWorldPosition - fragmentIn.worldPosition);

    float3 finalColor(0, 0, 0);
    for (int i = 0; i < LightCount; ++i) {
        float3 L = normalize(uniforms.lights[i].worldPosition - fragmentIn.worldPosition.xyz);
        float3 diffuseIntensity = saturate(dot(N, L));
        float3 H = normalize(L + V);
        float specularBase = saturate(dot(N, H));
        float specularIntensity = powr(specularBase, uniforms.specularPower);
        float3 lightColor = uniforms.lights[i].color;
        finalColor += uniforms.ambientLightColor * baseColor +
                      diffuseIntensity * lightColor * baseColor +
                      specularIntensity * lightColor * specularColor;
    }
    return float4(finalColor, 1);
}
