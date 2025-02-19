struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

// Texture.
texture2D diffuseMap : register(t0);
SamplerState diffuseSmapler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSmapler, input.texCoord);
    
    return texColor;
} 