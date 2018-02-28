Texture2D ObjectTexture[3];
SamplerState ObjectSampler;

cbuffer LightBuffer
{
	float4 LightPosition[3];
	float4 AmbientColour[3];
	float4 DiffuseColour[3];
	float4 SpecularColour[3];
	float4 ObjectColour;
	float ObjectReflectivity;
	float3 LightBufferPadding;
}

cbuffer BlendBuffer
{
	float BlendAmount;
	float3 BlendBufferPadding;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD0;
	float3 WorldPosition : TEXCOORD1;
	float3 ViewPosition : TEXCOORD2;
	float RenderState : TEXCOORD3;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};

float4 ModelPixelShader(PixelInput input) : SV_TARGET
{
	float4 textureColour = float4(0.0f, 0.0f, 0.0f, 0.0f);

	if (input.RenderState > 1.0f)
	{
		textureColour = ObjectTexture[0].Sample(ObjectSampler, input.TexCoord);
	}
	else
	{
		textureColour = ObjectColour;
	}

	float3 normal = float3(0.0f, 0.0f, 0.0f);
	float4 specularMap = float4(0.0f, 0.0f, 0.0f, 0.0f);

	if(input.RenderState > 2.0f)
	{
		float4 bumpMap = (ObjectTexture[1].Sample(ObjectSampler, input.TexCoord) * 2.0f) - 1.0f;
		normal = normalize((bumpMap.x * input.Tangent) + (bumpMap.y * input.Binormal) + (bumpMap.z * input.Normal));

		specularMap = ObjectTexture[2].Sample(ObjectSampler, input.TexCoord);
	}
	else
	{
		normal = input.Normal;

		specularMap = float4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	float4 output[3];

	for (int i = 0; i < 3; i++)
	{
		float3 lightPosition = normalize(LightPosition[i].xyz - input.WorldPosition);

		float lightBrightness = saturate(dot(lightPosition, normal));
		float4 lightColour = saturate(AmbientColour[i] + (DiffuseColour[i] * lightBrightness));

		float4 objectColour = textureColour * lightColour;

		float3 lightReflection = normalize(reflect(-lightPosition, normal));
		float4 specularLight = pow(saturate(dot(input.ViewPosition, lightReflection)), ObjectReflectivity) * specularMap;

		float4 objectReflection = SpecularColour[i] * specularLight;

		output[i] = saturate(objectColour + objectReflection);
	}

	return float4(saturate(output[0] + output[1] + output[2]).xyz, BlendAmount);
}