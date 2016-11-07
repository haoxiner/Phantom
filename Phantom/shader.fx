float4 VS(float4 pos:POSITION):SV_POSITION
{
  return pos;
}

float4 PS(float4 pos:SV_POSITION):SV_Target
{
  return float4(0.2, 0.4, 0.6, 1.0);
}