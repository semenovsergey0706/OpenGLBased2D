#include "ITexStorage.hpp"

ITexStorage::ITexStorage() : m_texStorage(), m_allBinded(false)
{
}

ITexStorage::ITexStorage(ITexStorage&& store) noexcept : m_texStorage(std::move(store.m_texStorage)), m_allBinded(store.m_allBinded)
{
}

void ITexStorage::loadTexture(const char* path, int id)
{    
    m_texStorage.emplace_back();
    m_texStorage.back().setID(id);
    m_texStorage.back().loadFromFile(path);

    m_allBinded = false;
}

void ITexStorage::bindStorageTextures(std::shared_ptr<logl_shader> m_shader, const char *shaderField)
{
    assert(m_shader != nullptr && "shader nullptr");

    if (m_allBinded) return;

    m_shader->Use();
    std::vector<GLuint64EXT> textures;
    for (int i = 0; i < m_texStorage.size(); ++i)
    {
        textures.push_back(glGetTextureHandleNV(m_texStorage[i].get()));
        glMakeTextureHandleResidentNV(textures.back());
    }        
        
    GLuint handleSamplersLocation(glGetUniformLocation(m_shader->get(), shaderField));
    glUniform1ui64vNV(handleSamplersLocation, m_texStorage.size(), textures.data());

    m_allBinded = true;
}

const Texture& ITexStorage::getTextureByID(int id) const
{
    int t_id = std::find_if(m_texStorage.begin(), m_texStorage.end(), [=](const Texture &tempTexture) { return tempTexture.getID() == id; }) - m_texStorage.begin();
    assert(t_id < m_texStorage.size() && "texture with current id not found");
    return m_texStorage[t_id];
}

const Texture& ITexStorage::getTextureByStorageID(int id) const 
{
    return m_texStorage[id];
}

bool ITexStorage::isAllTexturesBinded()
{
    return m_allBinded;
}
