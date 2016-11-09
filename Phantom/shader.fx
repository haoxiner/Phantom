struct VSIN
{
  float3 position:POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
struct VSOUT
{
  float4 position:SV_POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
cbuffer cbPerObject
{
  float4x4 view;
  float4x4 projection;
};

VSOUT VS(
  VSIN vin)
{
  VSOUT vout;
  vout.position = mul(float4(vin.position, 1.0), view);
  vout.position = mul(vout.position, projection);
  //vout.position = float4(vin.position, 1.0);
  vout.normal = vin.normal;
  vout.texCoord = vin.texCoord;
  return vout;
}

float4 PS(VSOUT pin):SV_Target
{
  return float4(pin.texCoord, 0.0, 1.0);
}