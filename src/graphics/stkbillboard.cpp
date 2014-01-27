#include "graphics/stkbillboard.hpp"
#include "graphics/glwrap.hpp"
#include "graphics/shaders.hpp"
#include "graphics/irr_driver.hpp"

using namespace irr;

static GLuint billboardvbo;
static GLuint billboardvao = 0;

static void createbillboardvao()
{
	float quad[] = {
		-.5, -.5, 0., 1.,
		-.5, .5, 0., 0.,
		.5, -.5, 1., 1.,
		.5, .5, 1., 0.,
	};
	
	glGenBuffers(1, &billboardvbo);
	glGenVertexArrays(1, &billboardvao);
	glBindVertexArray(billboardvao);
	glBindBuffer(GL_ARRAY_BUFFER, billboardvbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), quad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(MeshShader::BillboardShader::attrib_corner);
	glEnableVertexAttribArray(MeshShader::BillboardShader::attrib_texcoord);
	glVertexAttribPointer(MeshShader::BillboardShader::attrib_corner, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glVertexAttribPointer(MeshShader::BillboardShader::attrib_texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*) (2 * sizeof(float)));
	glBindVertexArray(0);
}

STKBillboard::STKBillboard(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id,
	const irr::core::vector3df& position, const irr::core::dimension2d<irr::f32>& size,
	irr::video::SColor colorTop,	irr::video::SColor colorBottom) :
	CBillboardSceneNode(parent, mgr, id, position, size, colorTop, colorBottom), IBillboardSceneNode(parent, mgr, id, position)
{
	if (!billboardvao)
		createbillboardvao();
}

void STKBillboard::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDepthMask(GL_FALSE);
	core::vector3df pos = getAbsolutePosition();
	glBindVertexArray(billboardvao);
	GLuint texid = static_cast<irr::video::COpenGLTexture*>(Material.getTexture(0))->getOpenGLTextureName();
	setTexture(0, texid, GL_LINEAR, GL_LINEAR);
	glUseProgram(MeshShader::BillboardShader::Program);
	MeshShader::BillboardShader::setUniforms(irr_driver->getViewMatrix(), irr_driver->getProjMatrix(), pos, Size, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	return;
}
