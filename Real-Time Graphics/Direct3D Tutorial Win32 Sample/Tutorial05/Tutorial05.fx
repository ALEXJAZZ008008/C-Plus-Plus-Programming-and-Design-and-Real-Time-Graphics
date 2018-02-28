//--------------------------------------------------------------------------------------
// File: Tutorial05.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

static const int m_NumberOfLights = 1;

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 Eye;
	float4 MaterialAmbiant;
	float4 MaterialDiffuse;
	float4 MaterialSpecular;
	float4 MaterialSpecularPower;
	float4 LightPosition[m_NumberOfLights];
	float4 LightColour[m_NumberOfLights];
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float3 WorldPosition : TEXCOORD0;
    float3 Normal : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

	output.WorldPosition = input.Position.xyz;

	output.Normal = mul(float4(input.Normal, 1.0), World).xyz;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float4 colour = 0;

	float3 view = normalize(float3(Eye.xyz - input.WorldPosition.xyz));
	float3 normal = normalize(input.Normal);

	for (int i = 0; i < m_NumberOfLights; i++)
	{
		float3 lightPosition = normalize(LightPosition[i].xyz - input.WorldPosition.xyz);

		float diffuse = saturate(dot(lightPosition[i], normal));

		float3 reflection = normalize(reflect(lightPosition[i], normal));
		float specular = pow(saturate(dot(view, reflection)), MaterialSpecularPower.x);

		colour += (MaterialAmbiant + (diffuse * MaterialDiffuse) + (specular * MaterialSpecular)) * LightColour[i];
	}

	colour = float4(colour.xyz, 1.0f);

    return colour;
}
