//
// The exemplar for this technique comes from the default Xcode Swift Metal Game Template
//
// Seems trivial until someone updating the code revises a struct in Swift but forgets to update the shader,
// or adds a field to Swift that changes the alignment or the in-memory-layout of the Swift struct.
//
#ifndef Shaders_struct_BridgingHeader_h
#define Shaders_struct_BridgingHeader_h

#ifdef __METAL_VERSION__
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
typedef metal::int32_t EnumBackingType;
#else
#import <Foundation/Foundation.h>
typedef NSInteger EnumBackingType;
#endif

#include <simd/simd.h>

#ifdef __cplusplus
#define CXX_ATTRIBUTE_N(__n__) [[attribute(__n__)]]
#pragma message("C++ compiler semantics")
#else
#define CXX_ATTRIBUTE_N(__n__)
#pragma message("ANSI-C compiler semantics")
#endif

typedef struct tagVertexIn {
    simd_float3 position  CXX_ATTRIBUTE_N(0);
    simd_float3 normal    CXX_ATTRIBUTE_N(1);
    simd_float2 texCoords CXX_ATTRIBUTE_N(2);
} VertexIn;

typedef struct tagVertexUniforms {
    simd_float4x4 viewProjectionMatrix;
    simd_float4x4 modelMatrix;
    simd_float3x3 normalMatrix;
} VertexUniforms;

#define LightCount 3

typedef struct tagLight {
    simd_float3 worldPosition;
    simd_float3 color;
} Light;

typedef struct tagFragmentUniforms {
    simd_float3 cameraWorldPosition;
    simd_float3 ambientLightColor;
    simd_float3 specularColor;
    float specularPower;
    Light lights[LightCount];
} FragmentUniforms;

typedef NS_ENUM(EnumBackingType, FragmentTexture)
{
    FragmentTextureIndex0 = 0,
    FragmentTextureIndex1 = 1,
};

typedef NS_ENUM(EnumBackingType, ShaderBuffer)
{
    ShaderBufferIndex0 = 0,
    ShaderBufferIndex1 = 1,
};

typedef NS_ENUM(EnumBackingType, Sampler)
{
    SamplerIndex0 = 0,
    SamplerIndex1 = 1,
};

#endif /* Shaders_struct_BridgingHeader_h */

