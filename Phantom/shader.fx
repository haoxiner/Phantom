
cbuffer cbChangeOnResize
{
  float4x4 projection;
};

cbuffer cbChangeEveryFrame
{
  float4x4 modelToWorld;
  float4x4 view;
};

struct VS_IN
{
  float3 position:POSITION0;
  float3 normal:NORMAL0;
  float2 texCoord:TEXCOORD0;
};
struct VS_OUT
{
  float4 position:SV_POSITION;
  float4 posInCameraSpace:POSITION0;
  float4 normal:NORMAL0;
  float2 texCoord:TEXCOORD0;
};

#define LN2DIV8               0.08664
#define Log2Of1OnLn2_Plus1    1.528766
float SphericalGaussianApprox(float CosX, float ModifiedSpecularPower)
{
    return exp2(ModifiedSpecularPower* CosX - ModifiedSpecularPower);
}

VS_OUT VS(
  VS_IN vin)
{
  VS_OUT vout = (VS_OUT)0;
  vout.position = mul(modelToWorld,float4(vin.position, 1.0f));
  vout.position = mul(view, vout.position);
  vout.posInCameraSpace = vout.position;
  
  vout.position = mul(projection, vout.position);
  vout.normal = mul(modelToWorld,float4(vin.normal, 0.0f));
  vout.normal = mul(view, vout.normal);
  vout.texCoord = vin.texCoord;
  return vout;
}
struct PS_IN
{
  float4 position:SV_POSITION;
  float4 posInCameraSpace:POSITION0;
  float4 normal:NORMAL0;
  float2 texCoord:TEXCOORD0;
};
float4 PS(PS_IN pin):SV_Target
{
  float4 n = normalize(pin.normal);
  float4 lightDir = normalize(float4(1.0f,1.0f,-1.0f,0.0f));
  float diff = dot(n, lightDir);
  float4 h = normalize(n + normalize(reflect(normalize(pin.posInCameraSpace - float4(1.0f,1.0f,-1.0f,0.0f)), n)));

  float DotNH = max(0.0f, dot(h,n));
  float K = 100.0f;
  float SpecularLighting = exp(-K*(1-DotNH));
  //SpecularLighting = pow(DotNH, K);
  float intensity = SpecularLighting * 0.5 + diff * 0.5;
  float4 color = pow(float4(intensity,intensity,intensity, 1.0f), 1.0/2.2);
  return color;
}