cbuffer mycBuffer : register(b0)
{
    float xOffset;
    float yOffset;
};
struct VS_INPUT
{
    float3 pos : POSITION;
    float2 texCoord : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 outPos : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    input.pos.x += xOffset;
    input.pos.y += yOffset;
    output.outPos = float4(input.pos, 1.0f);
    output.outTexCoord = input.texCoord;
    return output;
}