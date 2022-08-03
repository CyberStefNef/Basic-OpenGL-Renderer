#pragma once

#include "Test.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>
#include "CameraController.h"

namespace test {

	class TestBatchTexture2D : public Test
	{
	public:
		TestBatchTexture2D();
		~TestBatchTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_ChernoTex;
		std::unique_ptr<Texture> m_HazelTex;

		glm::vec3 m_test;
		glm::vec2 m_mouse;
		glm::vec2 m_offset;
		glm::vec3 m_trans_model;
		glm::mat4 m_Proj, m_View;

		CameraController m_cameraController;
	};

}
