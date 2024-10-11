#include "GameObject.h"

#include <iostream>

#include "ConstantBuffer.h"

// void GameObject::draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow)
// {
// 	std::cout << "GameObject draw: " << vs << " " << gs << " " << ps << std::endl;
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, constantBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(gs, constantBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, constantBuffer);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
// }
