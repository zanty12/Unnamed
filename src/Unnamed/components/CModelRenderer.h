#pragma once
#include "main.h"
#include "renderer.h"
#include "transform.h"
#include "traits/drawable.h"


// マテリアル構造体
struct MODEL_MATERIAL
{
    char Name[256];
    MATERIAL Material;
    char TextureName[256];
    ID3D11ShaderResourceView* Texture;
};


// 描画サブセット構造体
struct SUBSET
{
    unsigned int StartIndex;
    unsigned int IndexNum;
    MODEL_MATERIAL Material;
};


// モデル構造体
struct MODEL_OBJ
{
    VERTEX_3D* VertexArray;
    unsigned int VertexNum;

    unsigned int* IndexArray;
    unsigned int IndexNum;

    SUBSET* SubsetArray;
    unsigned int SubsetNum;
};

struct MODEL
{
    ID3D11Buffer* VertexBuffer;
    ID3D11Buffer* IndexBuffer;

    SUBSET* SubsetArray;
    unsigned int SubsetNum;
};


#include <string>
#include <unordered_map>
#include "components/Component.h"


class CModelRenderer : public Component, public Drawable
{
private:
    static std::unordered_map<std::string, MODEL*> m_ModelPool;

    static void LoadModel(const char* FileName, MODEL* Model);
    static void LoadObj(const char* FileName, MODEL_OBJ* ModelObj);
    static void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);

    MODEL* m_Model{};

    ID3D11VertexShader* vertex_shader_ = nullptr;
    ID3D11PixelShader* pixel_shader_ = nullptr;
    ID3D11InputLayout* vertex_layout_ = nullptr;

public:
    static void Preload(const char* FileName);
    static void UnloadAll();


    using Component::Component;

    CModelRenderer() : Component("ModelRenderer"),Drawable(2)
    {
    }

    void Load(const char* FileName);

    void Start() override;
    void Draw();

    void Update() override;

    void CleanUp() override;
};
