#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "CParticleEmitter.h"

const double PI = 3.14;

void CParticleEmitter::Start()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC; // D3D11_USAGE_DYNAMICはあとから書き換え可能
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;  // D3D11_CPU_ACCESS_WRITEはあとから書き換え可能

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertex_buffer_);

	// テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\particle.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, "asset\\shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&pixel_shader_, "asset\\shader\\unlitTexturePS.cso");
}

void CParticleEmitter::CleanUp()
{
	vertex_buffer_->Release();
	m_Texture->Release();

	vertex_layout_->Release();
	vertex_shader_->Release();
	pixel_shader_->Release();
}

void CParticleEmitter::Update()
{
	Transform* transform = Manager::FindEntityByID(parent_id_)->GetTransform();
	// パーティクル発射
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == false)
		{
			/*for (auto player : objectList)
			{
				m_Particle[i].pos = player->GetPosition();
			}*/
			m_Particle[i].Enable = true;
			m_Particle[i].Position.x = transform->position.x + (rand() % 1000 - 500) / 500.0f;
			m_Particle[i].Position.z = transform->position.y + (rand() % 1000 - 500) / 500.0f;
			m_Particle[i].Position.y = -0.1f;
			m_Particle[i].Scale = transform->scale;
			m_Particle[i].Life = 120;
			m_Particle[i].Velocity.x = 0.0f;
			m_Particle[i].Velocity.y = 0.0f;
			m_Particle[i].Velocity.z = 0.0f;

			m_Particle[i].Color = XMFLOAT4(255.0f, 240.0f, 0.0f, 255.0f);
			break;
		}
	}

	// パーティクル移動
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			m_Particle[i].Velocity.y += 0.001f;
			m_Particle[i].Position.x += m_Particle[i].Velocity.x;
			m_Particle[i].Position.y += m_Particle[i].Velocity.y;
			m_Particle[i].Position.z += m_Particle[i].Velocity.z;
			
			m_Particle[i].Scale.x -= m_Particle[i].Position.y * 0.003f;
			m_Particle[i].Scale.y -= m_Particle[i].Position.y * 0.003f;

			m_Particle[i].Color.y -= 1.0f;
			if (m_Particle[i].Color.y < 0)
			{
				m_Particle[i].Color.y = 0;
			}

			// ライフ
			m_Particle[i].Life--;

			if (m_Particle[i].Life <= 0)
			{
				m_Particle[i].Enable = false;
			}

			/*if (m_Particle[i].Scale.x <= 0.0f)
			{
				m_Particle[i].Enable = false;
			}*/

			//if (m_Particle[i].Position.y <= 0)
			//{
			//	if (m_Particle[i].aaa == true)
			//	{
			//		//m_Particle[i].Enable = false;
			//		m_Particle[i].Velocity.y *= -1.0f;
			//		m_Particle[i].aaa = false;
			//	}
			//	else if (m_Particle[i].aaa == false)
			//	{
			//		if (m_Particle[i].Position.y > 0)
			//		{
			//			m_Particle[i].aaa = true;
			//		}
			//	}
			//}
			//break;
		}
	}
}

void CParticleEmitter::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, NULL, 0);

	// カメラのビューマトリクス取得
	XMFLOAT4X4 view = Manager::GetActiveCamera()->GetViewMatrix();

	// ビューの逆行列
	XMMATRIX invView= XMLoadFloat4x4(&view);;
	invView = XMMatrixInverse(nullptr, invView); // 逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);

	//// マテリアル設定
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	//material.TextureEnable = true;
	//Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Zバッファ無効
	Renderer::SetDepthEnable(false);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			// マテリアル設定
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = XMFLOAT4(m_Particle[i].Color.x / 255.0f, m_Particle[i].Color.y / 255.0f, m_Particle[i].Color.z / 255.0f, m_Particle[i].Color.w / 255.0f);
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			// ワールドマトリクス設定
			XMMATRIX world, scale, rot, trans;
			scale = XMMatrixScaling(m_Particle[i].Scale.x, m_Particle[i].Scale.y, m_Particle[i].Scale.z);
			trans = XMMatrixTranslation(m_Particle[i].Position.x, m_Particle[i].Position.y, m_Particle[i].Position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			// ポリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	// Zバッファ有効
	Renderer::SetDepthEnable(true);
}