#include "Model.h"
#include <glm/glm.hpp>

namespace Engine
{
    void Model::LoadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            ENGINE_CORE_WARN(std::format("ERROR::ASSIMP::{}",importer.GetErrorString()));
            return;
        }

        m_Directory = path.substr(0, path.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }
    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        for (int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture> textures;

        Vertex vertex;

        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            
            vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.Normal= glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            vertex.Color = glm::vec4(mesh->mColors[i]->r, mesh->mColors[i]->g, mesh->mColors[i]->b, mesh->mColors[i]->a);

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                vertex.Texture.x = mesh->mTextureCoords[0][i].x;
                vertex.Texture.y = mesh->mTextureCoords[0][i].y;
            }
            else
            {
                vertex.Texture = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        VertexBuffer VBO(vertices.data(), vertices.size());
        IndexBuffer EBO(indices.data(), sizeof(indices) / sizeof(uint32_t));
        VertexArray VAO;
        VAO.AddVertexBuffer(std::make_shared<VertexBuffer>(VBO));
        VAO.SetIndexBuffer(std::make_shared<IndexBuffer>(EBO));

        return Mesh(VBO, EBO, VAO);
    }
    std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture(m_Directory.c_str());
            textures.push_back(texture);
        }
    }
}