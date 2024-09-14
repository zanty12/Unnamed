#pragma once
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#include <DirectXMath.h>
#include <string>
#include <dwrite.h>
#include <d2d1.h>
#include "dwrite_3.h"
#include <d2d1helper.h>

#include "Component.h"
#include "traits/drawable.h"

//2D Text using DirectWrite;
class CText2D : public Component, public Drawable
{
private:
    //directwrite
    static IDWriteFactory5* dwrite_factory_;
    static IDWriteFontSetBuilder1* fontset_builder_;
    static IDWriteFontCollection1* font_collection_;
    static IDWriteFontSet* font_set_;
    static IDWriteFontFile* font_file_;

    //D2D
    static ID2D1Factory* d2dfactory_;
    static ID2D1RenderTarget* render_target_;
    static IDXGISurface* back_buffer_;

    //text formats
    std::wstring font_ = L"Noto Sans JP";

public:


private:
    float font_size_ = 20.0f;
    DWRITE_FONT_WEIGHT font_weight_ = DWRITE_FONT_WEIGHT_NORMAL;
    DWRITE_FONT_STYLE font_style_ = DWRITE_FONT_STYLE_NORMAL;
    DirectX::XMFLOAT4 font_color_ = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    IDWriteTextFormat* text_format_ = nullptr;
    ID2D1SolidColorBrush* solid_brush_ = nullptr;
    DWRITE_TEXT_ALIGNMENT text_alignment_ = DWRITE_TEXT_ALIGNMENT_CENTER;

    //content
    std::wstring text_ = L"";

public:
    static HRESULT CreatePublicResources();
    static void DiscardPublicResources();
    static void TextStart();
    static void TextEnd();

    //左上原点
    //Separate WriteText for writing non-standard text, so we don't need to change the format every time
    static void WriteText(const WCHAR* text, IDWriteTextFormat* text_format, ID2D1SolidColorBrush* brush, float X,
                          float Y, float Width,
                          float Height);

    //スタイル変更
    static HRESULT SetTextFormat(IDWriteTextFormat* text_format, std::wstring font,
                                 float size , DWRITE_FONT_WEIGHT font_weight,
                                 DWRITE_FONT_STYLE style);
    static HRESULT SetFontColor(ID2D1SolidColorBrush* brush, DirectX::XMFLOAT4 color);

    //write factory getter for creating separate text format
    static IDWriteTextFormat* MakeTextFormat(std::wstring font, float size,
                                             DWRITE_FONT_WEIGHT font_weight,
                                             DWRITE_FONT_STYLE font_style);
    static ID2D1SolidColorBrush* MakeBrush(DirectX::XMFLOAT4 color);

    static HRESULT SetTextAlignment(IDWriteTextFormat* text_format, DWRITE_TEXT_ALIGNMENT text_alignment);

    //non-static functions
    CText2D();
    ~CText2D() override;
    void Start() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;

    std::wstring GetFont() const;
    void SetFont(const std::wstring& font);
    float GetFontSize() const;
    void SetFontSize(float font_size);
    DWRITE_FONT_WEIGHT GetFontWeight() const;
    void SetFontWeight(DWRITE_FONT_WEIGHT font_weight);
    DWRITE_FONT_STYLE GetFontStyle() const;
    void SetFontStyle(DWRITE_FONT_STYLE font_style);
    DirectX::XMFLOAT4 GetFontColor() const;
    void SetFontColor(const DirectX::XMFLOAT4& font_color);
    DWRITE_TEXT_ALIGNMENT GetAlignment() const;
    void SetAlignment(DWRITE_TEXT_ALIGNMENT text_alignment);
    std::wstring GetText() const;
    void SetText(const std::wstring& text);
};