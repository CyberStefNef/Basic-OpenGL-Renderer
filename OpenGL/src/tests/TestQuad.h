#pragma once

#include "Test.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Transform.h"

#include <memory>
#include <CameraController.h>

namespace test {

	class TestQuad : public Test
	{
	public:
		TestQuad();
		~TestQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		CameraController m_camera;
		Transform m_transform;
		glm::vec3 m_rotation;
	};

}
