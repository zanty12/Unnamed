#include "CTerrain.h"
#include "manager.h"

void CTerrain::Start()
{
	//VERTEX_3D vertex_[21][21];
	//Get World Transform
	Transform world_transform = GetWorldTransform();
	for (int x = 0; x < 21; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			//generate random float for height
			float height = static_cast<float>(rand() % 10) * 0.1f;
			//set vertex
			vertex_[x][z].Position = DirectX::XMFLOAT3(
				(static_cast<float>(x) - 10) * 0.05f,
				height,
				(static_cast<float>(z) - 10) * -0.05f);
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

	unsigned int index[((21 + 1) * 2) * 20 - 2];
	int i = 0;
	for (int x = 0; x < 20; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			index[i] = x * 21 + z;
			i++;

			index[i] = (x + 1) * 21 + z;
			i++;
		}
		if (x == 19)
			break;
		index[i] = (x + 1) * 21 + 20;
		i++;
		index[i] = (x + 1) * 21;
		i++;
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
	sd.pSysMem = index;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &index_buffer_);

	Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, vertex_shader_path_.c_str());
	Renderer::CreatePixelShader(&pixel_shader_, pixel_shader_path_.c_str());
}

void CTerrain::Update()
{
	////find parent
	//Entity* parent = Manager::FindEntityByID(parent_id_);

	//if (parent_id_ < 0 || parent == nullptr)
	//{
	//    //do nothing
	//}
	//else
	//{
	//}
}

void CTerrain::Draw()
{
	//input layout
	Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

	//shader
	Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, nullptr, 0);

	//world matrix
	DirectX::XMMATRIX world, scale, rot, trans;
	Transform world_transform = GetWorldTransform();
	scale = DirectX::XMMatrixScaling(world_transform.scale.x, world_transform.scale.y, world_transform.scale.z);
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

void CTerrain::CleanUp()
{
	vertex_buffer_->Release();
	vertex_shader_->Release();
	pixel_shader_->Release();
	vertex_layout_->Release();
}
