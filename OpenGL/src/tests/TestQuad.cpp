#include "TestQuad.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {

	TestQuad::TestQuad()
		:	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
			m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
			m_trans_model(0, 0, 0)
	{
		float positions[] = {
			100.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			200.0f,	100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			200.0f, 200.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			100.0f, 200.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

			300.0f,	300.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f,
			400.0f, 300.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f,
			400.0f, 400.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f,
			300.0f, 400.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 7 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicBatch.shader");

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
	}

	TestQuad::~TestQuad()
	{
	}

	void TestQuad::OnUpdate(float deltaTime)
	{
	}

	void TestQuad::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trans_model);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestQuad::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation Models", &m_trans_model.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}