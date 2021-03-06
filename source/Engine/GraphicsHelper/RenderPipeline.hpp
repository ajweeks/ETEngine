#pragma once
#include "../StaticDependancies/glad/glad.h"

class AbstractScene;
class RenderState;

class RenderPipeline : public Singleton<RenderPipeline>
{
public:
	RenderPipeline();
	virtual ~RenderPipeline();

	void Initialize();

	Gbuffer* GetGBuffer() { return m_pGBuffer; }
	PostProcessingRenderer* GetPostProcessor() { return m_pPostProcessing; }	

	void DrawShadow();
	void Draw(std::vector<AbstractScene*> pScenes);

	RenderState* GetState() { return m_pState; }

private:
	std::vector<AbstractScene*> m_pRenderScenes;

	RenderState* m_pState;

	Gbuffer* m_pGBuffer = nullptr;
	PostProcessingRenderer* m_pPostProcessing = nullptr;
	glm::vec3 m_ClearColor;
};