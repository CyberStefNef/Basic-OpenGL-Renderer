#include "TestBatchTexture2D.h"

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

	TestBatchTexture2D::TestBatchTexture2D()
		:	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
			m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), 
			m_trans_model(0, 0, 0), m_test(0, 0, 0), m_mouse(1, 1)
	{

		const size_t MaxQuadCount = 1000;
		const size_t MaxVertexCount = MaxQuadCount * 4;
		const size_t MaxIndexCount = MaxQuadCount * 6;

		uint32_t indices[MaxIndexCount];
		uint32_t offset = 0;
		uint32_t indexCount = 0;

		for (size_t i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
			indexCount += 6;
		}


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MaxVertexCount * sizeof(Vertex));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, indexCount);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicBatch.shader");

		m_ChernoTex = std::make_unique<Texture>("res/textures/chernologo.png");
		m_HazelTex = std::make_unique<Texture>("res/textures/hazellogo.png");

		m_Shader->Bind();
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
	}

	TestBatchTexture2D::~TestBatchTexture2D()
	{
	}

	void TestBatchTexture2D::OnUpdate(float deltaTime)
	{
	}

	static Vertex* CreateQuad(Vertex* target, float x, float y, float textureID)
	{
		
		float size = 1.0f;

		target->Position = { x, y, 0.0f };
		target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		target->TexCoords = {0.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { x + size, y, 0.0f };
		target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		target->TexCoords = {1.0f, 0.0 };
		target->TexID = textureID;
		target++;

		target->Position = { x + size, y + size, 0.0f };
		target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		target->TexCoords = {1.0f, 1.0 };
		target->TexID = textureID;
		target++;

		target->Position = { x , y + size, 0.0f };
		target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		target->TexCoords = {0.0f, 1.0 };
		target->TexID = textureID;
		target++;

		return target;
	}


	void TestBatchTexture2D::OnRender()
	{

		std::array<Vertex, 1000> vertices;
		Vertex* buffer = vertices.data();
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				buffer = CreateQuad(buffer, x, y , (x + y) % 2);
			}

		}

		buffer = CreateQuad(buffer, m_test.x, m_test.y, m_test.z);


		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());


		Renderer renderer;


		m_ChernoTex->Bind();
		m_HazelTex->Bind(1);
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trans_model);
			glm::mat4 mvp =  model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestBatchTexture2D::OnImGuiRender()
	{
		ImGui::DragFloat3("Test", &m_test.x, 0.1f, -2.0f, 2.0f, "%.3f");
		ImGui::DragFloat2("Mouse", &m_mouse.x, 0.1f, 0.0f, 920.0f, "%.3f");
		ImGui::SliderFloat3("Translation Model", &m_trans_model.x, -2.0f, 2.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}