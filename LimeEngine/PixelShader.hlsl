struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 normal   : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 worldPos : WORLD_POSITION;
};
SamplerState objSamplerState : SAMPLER : register(s0);
Texture2D objTexture : TEXTURE : register(t0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 pixelColor = objTexture.Sample(objSamplerState, input.texCoord);
    return float4(pixelColor, 1.0f);
    
}