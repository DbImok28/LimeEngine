cbuffer perObjectBuffer : register(b0)
{
    float4x4 wvpMatrix; // WorldViewProjectionMatrix
};
struct VS_INPUT
{
    float3 Position : POSITION;
    float2 texCoord : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPosition = mul(float4(input.Position, 1.0f), wvpMatrix);
    output.outTexCoord = input.texCoord;
    return output;
}