Texture2D ObjectTexture;
SamplerState ObjectSampler;

cbuffer ImageBuffer
{
	float4 Colour;
}

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

float4 ImagePixelShader(PixelInput input) : SV_TARGET
{
	float4 output = ObjectTexture.Sample(ObjectSampler, input.TexCoord);
    
	if(output.r == 0.0f)
	{
		output.a = 0.0f;
	}
	else
	{
		output.a = 1.0f;

		output *= Colour;
	}

	return output;
}