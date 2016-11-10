cbuffer cbPerObject : register(b0)
{
  float4x4 modelToWorld;
  float4x4 view;
  float4x4 proj;
};
cbuffer cbChangeOnResize :register(b1)
{
  float4x4 projection;
};

struct VS_IN
{
  float3 position:POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
struct VS_OUT
{
  float4 position:SV_POSITION;
  float4 posInCameraSpace:POSITION;
  float4 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

VS_OUT VS(
  VS_IN vin)
{
  VS_OUT vout = (VS_OUT)0;
  vout.position = mul(modelToWorld,float4(vin.position, 1.0f));
  vout.position = mul(view, vout.position);
  vout.posInCameraSpace = vout.position;
  vout.position = mul(proj, vout.position);
  vout.normal = mul(modelToWorld,float4(vin.normal, 0.0f));
  vout.texCoord = vin.texCoord;
  return vout;
}

float4 PS(VS_OUT pin):SV_Target
{
  float4 lightDir = normalize(float4(1.0f,1.0f,-1.0f,0.0f));
  float diff = dot(normalize(pin.normal), lightDir);
  float4 color = pow(float4(diff,diff,diff, 1.0f), 1.0/1.0);
  return color;
}