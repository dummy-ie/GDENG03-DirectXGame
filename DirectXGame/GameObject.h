#pragma once

#include <vector>
#include <corecrt_math_defines.h>
#include <reactphysics3d/reactphysics3d.h>

#include "Quaternion.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "ConstantBuffer.h"
#include "LogUtils.h"
#include "Material.h"
#include "Component.h"
#include "EditorAction.h"

namespace mrlol
{
	class GameObject
	{
	public:
		typedef std::vector<Component*> ComponentList;

		explicit GameObject(const std::string& name);

		virtual ~GameObject() = default;
		GameObject(GameObject const&) = default;
		GameObject& operator=(GameObject const&) = default;
		GameObject(GameObject&& other) noexcept = default;
		GameObject& operator=(GameObject&& other) noexcept = default;

		virtual void awake() {}
		virtual void update(float deltaTime) {}

		void setLocalPosition(const Vector3D& position);
		void translate(const Vector3D& translation);
		Vector3D getLocalPosition();

		void setLocalScale(const Vector3D& scale);
		void scale(const Vector3D& scale);
		Vector3D getLocalScale();

		void setLocalRotation(const Vector3D& rotation);
		void rotate(const Vector3D& rotation);
		Vector3D getLocalRotation();

		void setOrientation(const Vector4D& orientation);
		Vector4D getOrientation();

		void setEnabled(const bool enabled);
		bool getEnabled() const;

		void setDisplayName(const std::string& displayName);
		std::string getUniqueName();
		std::string getDisplayName();

		void updateLocalMatrix();
		Matrix4x4 getLocalMatrix() const;
		void setLocalMatrix(float matrix[16]);
		float* getPhysicsLocalMatrix();

		void attachComponent(Component* component);
		void detachComponent(const Component* component);

		Component* findComponentByName(const std::string& name);
		Component* findComponentOfType(ComponentType type, const std::string& name);
		ComponentList getComponentsOfType(ComponentType type) const;
		ComponentList getComponentsOfTypeRecursive(ComponentType type) const;

		void saveEditState();
		void restoreEditState();

		//reactphysics3d::Transform transform;

	protected:
		void setUniqueName(const std::string& uniqueName);

		float elapsedTime = 0.f;

		std::string displayName;
		std::string name;
		bool isEnabled = true;

		Vector3D localScale = 1.f;
		Vector3D localPosition = 0.f;
		Vector3D localRotation = 0.f;
		Matrix4x4 localMatrix;
		Vector4D orientation;

		EditorAction* lastEditState = nullptr;

		ComponentList componentList;

		friend class GameObjectManager;
	};
}
