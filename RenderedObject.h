#pragma once
class RenderedObject
{
public:
	virtual void InitializeDeviceDependent(ID3D11Device1*) = 0;
	virtual void Render(DirectX::SpriteBatch*) = 0;
	virtual void Reset() = 0;
};

