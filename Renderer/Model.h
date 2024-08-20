#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.h"
#include "../MainIncludes.h"

namespace Engine
{
	class Model
	{
	public:
		Model(const std::string& path);
	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode *node, const aiScene *scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			std::string typeName);
	};
}

