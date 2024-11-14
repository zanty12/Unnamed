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

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC; // D3D11_USAGE_DYNAMIC�͂��Ƃ��珑�������\
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;  // D3D11_CPU_ACCESS_WRITE�͂��Ƃ��珑�������\

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertex_buffer_);

	// �e�N�X�`���ǂݍ���
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
	Transform transform = parent_entity_->GetTransform();
	// �p�[�e�B�N������
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == false)
		{
			/*for (auto player : objectList)
			{
				m_Particle[i].pos = player->GetPosition();
			}*/
			m_Particle[i].Enable = true;
			m_Particle[i].Position.x = transform.position.x + (rand() % 1000 - 500) / 500.0f;
			m_Particle[i].Position.z = transform.position.y + (rand() % 1000 - 500) / 500.0f;
			m_Particle[i].Position.y = -0.1f;
			m_Particle[i].Scale = transform.scale;
			m_Particle[i].Life = 120;
			m_Particle[i].Velocity.x = 0.0f;
			m_Particle[i].Velocity.y = 0.0f;
			m_Particle[i].Velocity.z = 0.0f;

			m_Particle[i].Color = XMFLOAT4(255.0f, 240.0f, 0.0f, 255.0f);
			break;
		}
	}

	// �p�[�e�B�N���ړ�
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

			// ���C�t
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
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, NULL, 0);

	// �J�����̃r���[�}�g���N�X�擾
	XMFLOAT4X4 view = Manager::GetActiveCamera()->GetViewMatrix();

	// �r���[�̋t�s��
	XMMATRIX invView= XMLoadFloat4x4(&view);;
	invView = XMMatrixInverse(nullptr, invView); // �t�s��
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);

	//// �}�e���A���ݒ�
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	//material.TextureEnable = true;
	//Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Z�o�b�t�@����
	Renderer::SetDepthEnable(false);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			// �}�e���A���ݒ�
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = XMFLOAT4(m_Particle[i].Color.x / 255.0f, m_Particle[i].Color.y / 255.0f, m_Particle[i].Color.z / 255.0f, m_Particle[i].Color.w / 255.0f);
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			// ���[���h�}�g���N�X�ݒ�
			XMMATRIX world, scale, rot, trans;
			scale = XMMatrixScaling(m_Particle[i].Scale.x, m_Particle[i].Scale.y, m_Particle[i].Scale.z);
			trans = XMMatrixTranslation(m_Particle[i].Position.x, m_Particle[i].Position.y, m_Particle[i].Position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			// �|���S���`��
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	// Z�o�b�t�@�L��
	Renderer::SetDepthEnable(true);
}