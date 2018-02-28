Texture2D ObjectTexture;
SamplerState ObjectSampler;

cbuffer ParticleBuffer
{
	float4 RenderState;
}

struct PixelInput
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD0;
};

float4 ParticlePixelShader(PixelInput input) : SV_TARGET
{
	float4 output = ObjectTexture.Sample(ObjectSampler, input.TexCoord);

	if (output.r == 0.0f)
	{
		output.a = 0.0f;
	}
	else
	{
		output.a = 1.0f;

		output *= float4(0.7, 0.5, 0.3, 1.0);
		output.xyz += float3(0.2, 0.2, 0.2);
	}

	return output;
}