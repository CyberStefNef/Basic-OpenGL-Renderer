#include "TestQuad.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <array>

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vertex
{
	Vec3 Position;
	Vec4 Color;
};

namespace test {

	TestQuad::TestQuad()
		:	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
			m_Proj(glm::perspective(45.0f, 4.0f/3.0f, 0.5f, 5.0f)), 
			m_trans_model(0, 0, 0)
	{

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(Vertex));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicBatch.shader");

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
	}

	static Vertex* CreateQuad(Vertex* target, float x, float y)
	{
		target->Position = { -0.5f, -0.5f, 0.0f };
		target->Color = { 0.5f, 0.5f, 0.5f, 1.0f };
		target++;

		target->Position = { 0.5f,	-0.5f, 0.0f };
		target->Color = { 0.5f, 0.5f, 0.5f, 1.0f };
		target++;

		target->Position = { 0.5f, 0.5f, 0.0f };
		target->Color = { 0.5f, 0.5f, 0.5f, 1.0f };
		target++;

		target->Position = { -0.5f, 0.5f, 0.0f };
		target->Color = { 0.5f, 0.5f, 0.5f, 1.0f };
		target++;

		return target;
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

		std::array<Vertex, 4> vertices;
		Vertex* buffer = vertices.data();

		buffer = CreateQuad(buffer,0, 0);

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		Renderer renderer;

		m_Proj = glm::perspective(glm::radians(45.0f * 2.0f), 4.0f / 3.0f, 0.5f, 5.0f);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trans_model);
		glm::mat4 mvp = m_Proj;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform1f("u_Timer", glfwGetTime());
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestQuad::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation Models", &m_trans_model.x, -2.0f, 2.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}