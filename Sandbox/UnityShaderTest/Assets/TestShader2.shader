Shader "Test Shader 2"
{
	Properties
	{
		OutlineColor("Outline Color", Color) = (0, 0, 0, 1)
	}
	SubShader
	{
		Pass
		{
			CGPROGRAM

			#pragma vertex VertexShaderName  
			#pragma fragment PixelShaderName 

			struct VertexInput {
				float4 Vertex : POSITION;
				float3 Normal : NORMAL;
			};

			struct VertexOutput {
				float4 Pos : SV_POSITION;
				float4 PosWorld : TEXCOORD0;
				float3 NormalDir : TEXCOORD1;
			};

			float4 OutlineColor;

			VertexOutput VertexShaderName(VertexInput input)
			{
#if UNITY_VERSION > 0
				float4x4 modelMatrix = unity_ObjectToWorld;
				float4x4 modelMatrixInverse = unity_WorldToObject;
				float time = _Time;
#else
				// TODO: find UE4 equivalents
#endif
				float4 newRelativePosition = input.Vertex;
				newRelativePosition.x += cos((time + newRelativePosition.z) * 100) * 0.01; // add some waviness

				VertexOutput output;
				output.PosWorld = mul(modelMatrix, input.Vertex);
				output.NormalDir = normalize(mul(float4(input.Normal, 0.0), modelMatrixInverse).xyz);

#if UNITY_VERSION > 0
				output.Pos = UnityObjectToClipPos(newRelativePosition);
#else
				// TODO: output.Pos = ModelViewProjectionMatrix * newRelativePosition ;
#endif

				return output;
			}

			float4 PixelShaderName(VertexOutput input) : COLOR
			{
#if UNITY_VERSION > 0
				float3 camerPosition = _WorldSpaceCameraPos;
#else
				// TODO: find UE4 equivalents
#endif
				float3 normalDirection = normalize(input.NormalDir);
				float3 viewDirection = normalize(camerPosition - input.PosWorld.xyz);
				
				const float outlineThreshold = 0.2;
				if (dot(viewDirection, normalDirection) < outlineThreshold)
				{
					return OutlineColor;
				}

				return float4(1, 1, 1, 1);
			}
		ENDCG
		}
	}
}