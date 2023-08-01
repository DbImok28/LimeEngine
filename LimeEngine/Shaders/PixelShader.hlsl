// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 worldPos : WORLD_POSITION;
};
SamplerState objSamplerState : SAMPLER : register(s0);
Texture2D objTexture : TEXTURE : register(t0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 pixelColor = objTexture.Sample(objSamplerState, input.texCoord).xyz;
    return float4(pixelColor, 1.0f);
    
}