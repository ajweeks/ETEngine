#include "stdafx.hpp"

#include "ShadingTestScene.hpp"

#include "../../SceneGraph/Entity.hpp"

#include "../Materials/TexPBRMaterial.hpp"
#include "../Materials/EmissiveMaterial.hpp"

#include "../../Graphics\FrameBuffer.hpp"
#include "../../Framebuffers\Gbuffer.hpp"

#include "../../Components/ModelComponent.hpp"
#include "../../Components/LightComponent.hpp"

#include "../../Prefabs/Skybox.hpp"

#include <random>
#include "../Materials/ParamPBRMaterial.hpp"
#include "../../Graphics/SpriteFont.h"
#include "../../GraphicsHelper/TextRenderer.h"

ShadingTestScene::ShadingTestScene() : AbstractScene("SkyboxTestScene")
{
}
ShadingTestScene::~ShadingTestScene()
{
	SafeDelete(m_pMat);
	SafeDelete(m_pStandMat);
	SafeDelete(m_pEnvMat); 
}

void ShadingTestScene::Initialize()
{
	//Fonts
	//***************************
	m_pDebugFont = ContentManager::Load<SpriteFont>("Resources/Fonts/Consolas_32.fnt");

	//Camera
	//**************************
	//auto cam = new OrbitCamera();
	//AddEntity(cam);

	//Materials
	//**************************
	m_pMat = new TexPBRMaterial(
		"Resources/Textures/BaseColor.png",
		"Resources/Textures/Roughness.png",
		"Resources/Textures/Metalness.png",
		"Resources/Textures/AOMap.png",
		"Resources/Textures/NormalMap.png");
	m_pMat->SetSpecular(0.5f);

	m_pStandMat = new ParamPBRMaterial(glm::vec3(0.95, 0.95f, 0.5f), 0.2f, 0);
	m_pEnvMat = new ParamPBRMaterial(glm::vec3(0.8f), 0.8f, 0);

	//Skybox
	//**************************
	SetSkybox("Resources/Textures/Ice_Lake_Ref.hdr");

	//Models
	//*************************
	{
		auto pModelComp = new ModelComponent("Resources/Models/HelmetSettled.dae");
		pModelComp->SetMaterial(m_pMat);
		auto pHelmet = new Entity();
		pHelmet->AddComponent(pModelComp);
		pHelmet->GetTransform()->Translate(vec3(0, 0, 0));
		AddEntity(pHelmet);
	}
	{
		auto pModelComp = new ModelComponent("Resources/Models/HelmetStand.dae");
		pModelComp->SetMaterial(m_pStandMat);
		auto pHelmet = new Entity();
		pHelmet->AddComponent(pModelComp);
		pHelmet->GetTransform()->Translate(vec3(0, 0, 0));
		AddEntity(pHelmet);
	}
	{
		auto pModelComp = new ModelComponent("Resources/Models/Env.dae");
		pModelComp->SetMaterial(m_pEnvMat);
		auto pHelmet = new Entity();
		pHelmet->AddComponent(pModelComp);
		pHelmet->GetTransform()->Translate(vec3(0, 0, 0));
		AddEntity(pHelmet);
	}

	//Lights
	//**************************
	m_pLigEntity = new Entity();
	m_pLight = new DirectionalLight(vec3(1, 1, 1), 0.99f);
	m_pLight->SetShadowEnabled(true);
	m_pLigEntity->AddComponent(new LightComponent( m_pLight));
	//m_pLigEntity->GetTransform()->SetRotation(glm::lookAtLH())
	AddEntity(m_pLigEntity);

	SETTINGS->Window.VSync(false);
}

void ShadingTestScene::Update()
{
	//LOGGER::Log("FPS: " + to_string(TIME->FPS()));
	//cout << "FPS: " + to_string(TIME->FPS()) << endl;

	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_2))
	{
		m_pLigEntity->GetTransform()->RotateEuler(TIME->DeltaTime(), 0, 0);
	}
	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_8))
	{
		m_pLigEntity->GetTransform()->RotateEuler(-TIME->DeltaTime(), 0, 0);
	}
	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_4))
	{
		m_pLigEntity->GetTransform()->RotateEuler(0, -TIME->DeltaTime(), 0);
	}
	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_6))
	{
		m_pLigEntity->GetTransform()->RotateEuler(0, TIME->DeltaTime(), 0);
	}

	//Change light settings
	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_3))
	{
		float b = m_pLight->GetBrightness();
		float nB = b * 4;
		m_pLight->SetBrightness(b - (nB - b)*TIME->DeltaTime());
		LOGGER::Log("Linear: " + to_string(m_pLight->GetBrightness()));
	}
	if (INPUT->IsKeyboardKeyDown(SDL_SCANCODE_KP_9))
	{
		float b = m_pLight->GetBrightness();
		float nB = b * 4;
		m_pLight->SetBrightness(b + (nB - b)*TIME->DeltaTime());
		LOGGER::Log("Linear: " + to_string(m_pLight->GetBrightness()));
	}
}

void ShadingTestScene::Draw()
{
	TextRenderer::GetInstance()->SetFont(m_pDebugFont);
	TextRenderer::GetInstance()->SetColor(glm::vec4(1, 0.3f, 0.3f, 1));
	TextRenderer::GetInstance()->DrawText("FPS: " + std::to_string((int)TIME->FPS()), glm::vec2(20, 20));
}

void ShadingTestScene::DrawForward()
{
}

void ShadingTestScene::PostDraw()
{
}