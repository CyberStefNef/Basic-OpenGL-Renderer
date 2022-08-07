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

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
};

namespace test {

	TestQuad::TestQuad()
		:m_transform()
	{

		unsigned int indices[] = {
			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/*glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);*/

		glEnable(GL_DEPTH_TEST);



		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 18 * sizeof(Vertex));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 18);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicBatch.shader");

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
	}

	static Vertex* CreateQuad(Vertex* target, float x, float y)
	{
		target->Position = { -0.5,  -0.5,  -0.5 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target++;

		target->Position = { 0.5,  -0.5, -0.5 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target++;


		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  0.5 };
		target->Color = { 1, 0, 0, 1.0f };
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 1, 0, 0, 1.0f };
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 1, 0, 0, 1.0f };
		target++;

		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  -0.5 };
		target->Color = { 0, 0, 1, 1.0f };
		target++;

		target->Position = { -0.5,  -0.5, 0.5 };
		target->Color = { 0, 0, 1, 1.0f };
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0, 0, 1, 1.0f };
		target++;

		///////////////////////////////////////////////////

		target->Position = { 0.5,  -0.5,  -0.5 };
		target->Color = { 0, 1, 0, 1.0f };
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 0, 1, 0, 1.0f };
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0, 1, 0, 1.0f };
		target++;

		///////////////////////////////////////////////////

		target->Position = { 0.5,  -0.5,  -0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target++;

		target->Position = { -0.5, -0.5, -0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target++;

		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target++;

		target->Position = { -0.5,  -0.5, -0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target++;

		target->Position = { 0.5, -0.5, 0.5 };
		target->Color = { 1, 1, 1, 1.0f };
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
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		std::array<Vertex, 18> vertices;
		Vertex* buffer = vertices.data();

		buffer = CreateQuad(buffer,0, 0);

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		Renderer renderer;

		float time = glfwGetTime();

		glm::vec3 cosCounter = glm::vec3(cos(time), cos(time), cos(time));

		//m_transform.GetRot()->y = time;
		m_transform.GetRot()->x = m_rotation.x;
		m_transform.GetRot()->y = m_rotation.y;
		m_transform.GetRot()->z = m_rotation.z;
		//m_transform.SetScale(cosCounter);

		glm::mat4 mvp = m_camera.getPersCamera().GetViewProjection() * m_transform.GetModel();
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		//m_Shader->SetUniform1f("u_Timer", glfwGetTime());
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestQuad::OnImGuiRender()
	{
		ImGui::DragFloat3("Rotation", &m_rotation.x, 0.01f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}