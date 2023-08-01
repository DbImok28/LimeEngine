// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine

cbuffer perObjectBuffer : register(b0)
{
    float4x4 wvpMatrix; // WorldViewProjectionMatrix
    float4x4 worldMatrix; // WorldMatrix
};
struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 worldPos : WORLD_POSITION;
};
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.0f), wvpMatrix);
    output.normal = normalize(mul(float4(input.normal, 0.0f), worldMatrix));
    output.texCoord = input.texCoord;
    output.worldPos = mul(float4(input.position, 1.0f), worldMatrix);
    return output;
}