#include "CWater.h"
#include "manager.h"
#include "system/timesystem.h"

void CWater::Start()
{
	//VERTEX_3D vertex_[21][21];
	for (int x = 0; x < 21; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			Transform world_transform = GetWorldTransform();
			//set vertex
			vertex_[x][z].Position = DirectX::XMFLOAT3(
				(static_cast<float>(x) - 10) * world_transform.scale.x / 20.0f,
				0.0f,
				(static_cast<float>(z) - 10) * -world_transform.scale.z / 20.0f);
			physX_vertex_.push_back(physx::PxVec3(vertex_[x][z].Position.x, vertex_[x][z].Position.y, vertex_[x][z].Position.z));
			//vertex[0].Position = DirectX::XMFLOAT3(-50.0f, 0.0f, 50.0f);
			vertex_[x][z].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex_[x][z].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex_[x][z].TexCoord = DirectX::XMFLOAT2(x, z);
		}
	}

	//vertex buffer
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subresource_data;
	ZeroMemory(&subresource_data, sizeof(subresource_data));
	subresource_data.pSysMem = vertex_;

	Renderer::GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_);

	int i = 0;
	for (int x = 0; x < 20; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			index_[i] = x * 21 + z;
			i++;

			index_[i] = (x + 1) * 21 + z;
			i++;
		}
		if (x == 19)
			break;
		index_[i] = (x + 1) * 21 + 20;
		i++;
		index_[i] = (x + 1) * 21;
		i++;
	}

	for (int x = 0; x < 20; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			physX_index_.push_back(x * 21 + z);
			physX_index_.push_back((x + 1) * 21 + z);
			physX_index_.push_back(x * 21 + z + 1);

			physX_index_.push_back((x + 1) * 21 + z);
			physX_index_.push_back((x + 1) * 21 + z + 1);
			physX_index_.push_back(x * 21 + z + 1);
		}
	}


	//index buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = index_;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &index_buffer_);

	Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, vertex_shader_path_.c_str());
	Renderer::CreatePixelShader(&pixel_shader_, pixel_shader_path_.c_str());

	// Create triangle mesh description
	physx::PxTriangleMeshDesc meshDesc;
	meshDesc.points.count = static_cast<physx::PxU32>(physX_vertex_.size());
	meshDesc.points.stride = sizeof(physx::PxVec3);
	meshDesc.points.data = physX_vertex_.data();

	meshDesc.triangles.count = static_cast<physx::PxU32>(physX_index_.size() / 3);
	meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
	meshDesc.triangles.data = physX_index_.data();

	assert(meshDesc.isValid());


	// Cooking parameters
	physx::PxCookingParams cookingParams(PhysX_Impl::GetPhysics()->getTolerancesScale());
	cookingParams.buildGPUData = true;
	// disable mesh cleaning - perform mesh validation on development configurations
	//cookingParams.meshPreprocessParams |= physx::PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
	// disable edge precompute, edges are set for each triangle, slows contact generation
	//cookingParams.meshPreprocessParams |= physx::PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
	//cookingParams.meshWeldTolerance = 0.001f;

#ifdef _DEBUG
// mesh should be validated before cooked without the mesh cleaning
	bool res = PxValidateTriangleMesh(cookingParams, meshDesc);
	PX_ASSERT(res);
#endif

	// Cook the triangle mesh
	physx::PxDefaultMemoryOutputStream writeBuffer{};
	physx::PxTriangleMeshCookingResult::Enum result;
	bool status = PxCookTriangleMesh(cookingParams, meshDesc, writeBuffer, &result);

	if (!status)
	{
		throw std::runtime_error("Failed to cook triangle mesh");
	}

	physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	physx::PxTriangleMesh* triangleMesh = PhysX_Impl::GetPhysics()->createTriangleMesh(readBuffer);
	assert(triangleMesh);

	// Create a triangle mesh geometry
	physx::PxTriangleMeshGeometry meshGeometry{};
	meshGeometry.triangleMesh = triangleMesh;
	//validate meshGeometry
	assert(meshGeometry.isValid());

	// Create a rigid static actor with the triangle mesh geometry
	//identity transform
	actor_ = PhysX_Impl::GetPhysics()->createRigidStatic(physx::PxTransform(physx::PxIdentity));
	shape_ = PhysX_Impl::GetPhysics()->createShape(meshGeometry, *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f));
	shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	actor_->attachShape(*shape_);

	// Add the actor to the PhysX scene
	physx::PxScene* scene = PhysX_Impl::GetScene();
	scene->addActor(*actor_);
}

void CWater::Update()
{
    //calculate the height of the water
    float time = Time::GetCurrentTime();
    Transform world_transform = GetWorldTransform();

    //set position of all vertices
    for (int x = 0; x < 21; x++)
    {
        for (int z = 0; z < 21; z++)
        {
            vertex_[x][z].Position.y = sinf((x + z) * 0.1f + time) * 1.0f;
        }
    }

    //release the old vertex buffer
    vertex_buffer_->Release();
    //set vertex buffer
    //vertex buffer
    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc, sizeof(buffer_desc));
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA subresource_data;
    ZeroMemory(&subresource_data, sizeof(subresource_data));
    subresource_data.pSysMem = vertex_;

    Renderer::GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_);

}

void CWater::Draw()
{
	//input layout
	Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

	//shader
	Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, nullptr, 0);

	//world matrix
	DirectX::XMMATRIX world, scale, rot, trans;
	Transform world_transform = GetWorldTransform();
	scale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//rot = DirectX::XMMatrixRotationRollPitchYaw(world_transform.rotation.x, world_transform.rotation.y,world_transform.rotation.z);
	rot = DirectX::XMMatrixRotationQuaternion(XMLoadFloat4(&world_transform.quaternion));
	trans = DirectX::XMMatrixTranslation(world_transform.position.x, world_transform.position.y,
		world_transform.position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//vertex buffer
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);

	//material
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//texture
	ID3D11ShaderResourceView* render_resource = texture_->GetView();
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &render_resource);

	//primitive topology
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}

void CWater::CleanUp()
{
	vertex_buffer_->Release();
	vertex_shader_->Release();
	pixel_shader_->Release();
	vertex_layout_->Release();
	shape_->release();
	actor_->release();

}

float CWater::GetHeight(XMFLOAT3 position)
{
	int x,z;
	Transform world_transform = GetWorldTransform();
	x= static_cast<int>(position.x / 0.05f /world_transform.scale.x  + 10);
	z = static_cast<int>(position.z / -0.05f / world_transform.scale.z + 10);
	XMFLOAT3 pos0, pos1, pos2, pos3;
	pos0 = vertex_[x][z].Position;
	pos1 = vertex_[x + 1][z].Position;
	pos2 = vertex_[x][z + 1].Position;
	pos3 = vertex_[x + 1][z + 1].Position;

	XMFLOAT3 v12,v1p;
	v12.x = pos1.x - pos0.x;
	v12.y = pos1.y - pos0.y;
	v12.z = pos1.z - pos0.z;

	v1p.x = position.x / world_transform.scale.x - pos1.x;
	v1p.y = position.y / world_transform.scale.y - pos1.y;
	v1p.z = position.z / world_transform.scale.z - pos1.z;

	float cy = v12.z * v1p.x - v12.x * v1p.z;
	float py;
	XMFLOAT3 n;
	if(cy > 0.0f)
	{
		XMFLOAT3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;

		n.x = v10.y * v12.z - v10.z * v12.y;
		n.y = v10.z * v12.x - v10.x * v12.z;
		n.z = v10.x * v12.y - v10.y * v12.x;
	}
	else
	{
		XMFLOAT3 v13;
		v13.x = pos3.x - pos1.x;
		v13.y = pos3.y - pos1.y;
		v13.z = pos3.z - pos1.z;

		n.x = v12.y * v13.z - v12.z * v13.y;
		n.y = v12.z * v13.x - v12.x * v13.z;
		n.z = v12.x * v13.y - v12.y * v13.x;
	}
	py = -((position.x / world_transform.scale.x - pos1.x) * n.x  + (position.z / world_transform.scale.z - pos1.z) * n.z) / n.y + pos1.y;
	return py * world_transform.scale.y;
}
