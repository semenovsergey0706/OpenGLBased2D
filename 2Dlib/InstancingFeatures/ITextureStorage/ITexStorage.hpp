#pragma once
#include <vector>
#include "../../Texture/Texture.hpp"
#include "../../../InterfaceClasses/NonCopyable.hpp"
#include "../../../External/logl_shader.hpp"

class ITexStorage : public NonCopyable
{
private:
	bool m_allBinded;
	std::vector<Texture> m_texStorage;

public:
	ITexStorage();
	ITexStorage(ITexStorage&& store) noexcept;
	void loadTexture(const char* path, int id);
	void bindStorageTextures(std::shared_ptr<logl_shader> m_shader, const char* shaderField);
	const Texture& getTextureByID(int id) const;
	const Texture& getTextureByStorageID(int id) const;
	bool isAllTexturesBinded();

};