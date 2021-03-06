#pragma once
#include "renderer/loaders/voxLoader.h"

class VoxSlapLoader : public VoxLoader
{
public:
	virtual bool load(const std::string& filePath,
					  std::vector<GLuint>& voxelMaterials, 
					  std::vector<float>& materialData,
					  Imath::V3i& voxelResolution);
};

