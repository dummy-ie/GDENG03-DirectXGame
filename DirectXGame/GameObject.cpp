#include "GameObject.h"

#include <iostream>

#include "ConstantBuffer.h"

// void GameObject::draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow)
// {
// 	std::cout << "GameObject draw: " << vs << " " << gs << " " << ps << std::endl;
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(gs, cb);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);
// }
