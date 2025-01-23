#pragma once
#include "CDirectXTKPrimitive.h"

class CDirectXTKBox : public CDirectXTKPrimitive
{
private:
    XMFLOAT3 size_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
public:
    void Start() override;
    void CleanUp() override;
    void SetSize(XMFLOAT3 size) { size_ = size; }
};
