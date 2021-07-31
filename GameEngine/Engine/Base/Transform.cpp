#include "Transform.hpp"

XMMATRIX Transform::getTransformMatrix()
{
    return XMMatrixScaling(scale.x, scale.y, scale.z)
         * XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
         * XMMatrixTranslation(location.x, location.y, location.z);   
}