cbuffer cbPerObject : register( b0 )
{
  float4x4 modelToWorld;
  float4x4 view;
  float4x4 proj;
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
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

VS_OUT VS(
  VS_IN vin)
{
  VS_OUT vout = (VS_OUT)0;
  vout.position = mul(modelToWorld,float4(vin.position, 1.0f));
  vout.position = mul(view, vout.position);
  vout.position = mul(proj, vout.position);
  //vout.position = float4(vin.position, 1.0);
  vout.normal = vin.normal;
  vout.texCoord = vin.texCoord;
  return vout;
}

float4 PS(VS_OUT pin):SV_Target
{
  return float4(pin.texCoord, 0.0f, 1.0f);
}