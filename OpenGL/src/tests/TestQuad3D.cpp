#include "TestQuad3D.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "InputController.h"

#include <array>

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "CameraController.h"

struct Vec2
{
	float x, y;
};

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
	Vec2 TexCoords;
	float TexID;
};

namespace test {

	TestQuad3D::TestQuad3D()
		:	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
			m_Proj(glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 1.0f)),
			m_trans_model(0, 0, 0), m_test(0, 0, 0), m_perspective(45, 1.3, -2, 2)
	{

		const size_t MaxQuadCount = 1000;
		const size_t MaxVertexCount = MaxQuadCount * 18;
		const size_t MaxIndexCount = MaxQuadCount * 18;

		uint32_t indices[MaxIndexCount];
		uint32_t indexCount = 0;

		for (size_t i = 0; i < 18; i += 1)
		{
			indices[i] = i;

			indexCount += 1;
		}


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 18 * sizeof(Vertex));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 18);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicBatch.shader");

		m_ChernoTex = std::make_unique<Texture>("res/textures/chernologo.png");
		m_HazelTex = std::make_unique<Texture>("res/textures/hazellogo.png");

		m_Shader->Bind();
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
	}

	TestQuad3D::~TestQuad3D()
	{
	}

	void TestQuad3D::OnUpdate(float deltaTime)
	{
	}

	static Vertex* CreateQuad(Vertex* target, float x, float y, float textureID)
	{
		
		float size = 1.0f;

		//target->Position = { x, y, zQuad.x };
		//target->Color = { 1.0f - textureID, 1.0f - textureID, 1.0f - textureID, 1.0f };
		//target->TexCoords = {0.0f, 0.0 };
		//target->TexID = textureID;
		//target++;

		//target->Position = { x + size, y, zQuad.y };
		//target->Color = { 1.0f - textureID, 1.0f - textureID, 1.0f - textureID, 1.0f };
		//target->TexCoords = {1.0f, 0.0 };
		//target->TexID = textureID;
		//target++;

		//target->Position = { x + size, y + size, zQuad.z };
		//target->Color = { 1.0f - textureID, 1.0f - textureID, 1.0f - textureID, 1.0f };
		//target->TexCoords = {1.0f, 1.0 };
		//target->TexID = textureID;
		//target++;

		//target->Position = { x , y + size, zQuad.w };
		//target->Color = { 1.0f - textureID, 1.0f - textureID, 1.0f - textureID, 1.0f };
		//target->TexCoords = {0.0f, 1.0 };
		//target->TexID = textureID;
		//target++;

		target->Position = { -0.5,  -0.5,  -0.5 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target->TexCoords = {0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.5,  -0.5, -0.5 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target->TexCoords = {1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0.5, 0.5, 0.5, 1.0f };
		target->TexCoords = {1.0f, 1.0 };
		target->TexID = textureID;
		target++;


		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  0.5 };
		target->Color = { 1, 0, 0, 1.0f };
		target->TexCoords = { 0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 1, 0, 0, 1.0f };
		target->TexCoords = { 1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 1, 0, 0, 1.0f };
		target->TexCoords = { 1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  -0.5 };
		target->Color = { 0, 0, 1, 1.0f };
		target->TexCoords = { 0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { -0.5,  -0.5, 0.5 };
		target->Color = { 0, 0, 1, 1.0f };
		target->TexCoords = { 1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0, 0, 1, 1.0f };
		target->TexCoords = { 1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		///////////////////////////////////////////////////

		target->Position = { 0.5,  -0.5,  -0.5 };
		target->Color = { 0, 1, 0, 1.0f };
		target->TexCoords = { 0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 0, 1, 0, 1.0f };
		target->TexCoords = { 1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0, 1, 0, 1.0f };
		target->TexCoords = { 1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		///////////////////////////////////////////////////

		target->Position = { 0.5,  -0.5,  -0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target->TexCoords = { 0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.5,  -0.5, 0.5 };
		target->Color = { 1, 1, 1, 1.0f };
		target->TexCoords = { 1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 1, 1, 1, 1.0f };
		target->TexCoords = { 1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		///////////////////////////////////////////////////

		target->Position = { -0.5,  -0.5,  0.5 };
		target->Color = { 0, 0, 0, 1.0f };
		target->TexCoords = { 0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { -0.5,  -0.5, -0.5 };
		target->Color = { 0, 0, 0, 1.0f };
		target->TexCoords = { 1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { 0.0, 0.5, 0.0 };
		target->Color = { 0, 0, 0, 1.0f };
		target->TexCoords = { 1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		return target;
	}


	void TestQuad3D::OnRender()
	{

		std::array<Vertex, 18> vertices;
		Vertex* buffer = vertices.data();

		buffer = CreateQuad(buffer, m_test.x, m_test.y, m_test.z);


		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());


		Renderer renderer;

		m_Proj = glm::perspective(m_perspective.x, m_perspective.y, m_perspective.z, m_perspective.w);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(m_view.x, m_view.y, m_view.z));

		m_ChernoTex->Bind();
		m_HazelTex->Bind(1);
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trans_model);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestQuad3D::OnImGuiRender()
	{
		ImGui::DragFloat3("Test", &m_test.x, 0.1f, -2.0f, 2.0f, "%.3f");
		ImGui::DragFloat("FOV", &m_perspective.x);
		ImGui::DragFloat("Aspect", &m_perspective.y, 0.1f);
		ImGui::DragFloat("Znear", &m_perspective.z, 0.1f);
		ImGui::DragFloat("Zfar", &m_perspective.w, 0.1f);
		ImGui::DragFloat3("View", &m_view.x, 0.1f);
		ImGui::SliderFloat3("Translation Model", &m_trans_model.x, -2.0f, 2.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}