#include "CText2D.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

IDWriteFactory5* CText2D::dwrite_factory_;
IDWriteFontSetBuilder1* CText2D::fontset_builder_;
IDWriteFontCollection1* CText2D::font_collection_;
IDWriteFontSet* CText2D::font_set_;
IDWriteFontFile* CText2D::font_file_;
//D2D
ID2D1Factory* CText2D::d2dfactory_;
ID2D1RenderTarget* CText2D::render_target_;
IDXGISurface* CText2D::back_buffer_;

HRESULT CText2D::CreatePublicResources()
{
    HRESULT hr = S_OK;
    IDXGISwapChain* swapChain = Renderer::GetSwapChain();

    // Direct2D,DirectWriteの初期化
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dfactory_);
    if (FAILED(hr))
        return hr;

    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&back_buffer_));
    if (FAILED(hr))
        return hr;

    HWND hWnd = GetWindow();

    FLOAT dpi = static_cast<FLOAT>(GetDpiForWindow(hWnd));

    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                                       D2D1::PixelFormat(
                                                                           DXGI_FORMAT_UNKNOWN,
                                                                           D2D1_ALPHA_MODE_PREMULTIPLIED), dpi, dpi);

    hr = d2dfactory_->CreateDxgiSurfaceRenderTarget(back_buffer_, &props, &render_target_);
    if (FAILED(hr))
        return hr;

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5),
                             reinterpret_cast<IUnknown**>(&dwrite_factory_));
    if (FAILED(hr))
        return hr;

    //Load all fonts in asset
    dwrite_factory_->CreateFontSetBuilder(&fontset_builder_);
    dwrite_factory_->CreateFontFileReference(L"/asset/fonts/NotoSansJP-Bold.ttf", NULL, &font_file_);
    fontset_builder_->AddFontFile(font_file_);
    dwrite_factory_->CreateFontFileReference(L"/asset/fonts/wapuro-mincho.otf", NULL, &font_file_);
    fontset_builder_->AddFontFile(font_file_);
    fontset_builder_->CreateFontSet(&font_set_);
    dwrite_factory_->CreateFontCollectionFromFontSet(font_set_, &font_collection_);

    return S_OK;
}

void CText2D::DiscardPublicResources()
{
    if (back_buffer_) back_buffer_->Release();
    if (render_target_) render_target_->Release();
    if (dwrite_factory_) dwrite_factory_->Release();
    if (d2dfactory_) d2dfactory_->Release();
}

void CText2D::TextStart()
{
    render_target_->BeginDraw();
}

void CText2D::TextEnd()
{
    render_target_->EndDraw();
}

void CText2D::WriteText(const WCHAR* text, IDWriteTextFormat* text_format, ID2D1SolidColorBrush* brush, float X,
                        float Y,
                        float Width, float Height)
{
    render_target_->DrawText(text, wcslen(text), text_format, D2D1::RectF(X, Y, X + Width, Y + Height), brush);
}

HRESULT CText2D::SetTextFormat(IDWriteTextFormat* text_format, std::wstring font, float size, DWRITE_FONT_WEIGHT weight,
                               DWRITE_FONT_STYLE style)
{
    //release CText2DFormat
    if (text_format) text_format->Release();
    //create new CText2DFormat
    HRESULT hr = dwrite_factory_->CreateTextFormat(font.c_str(), font_collection_, weight, style,
                                                   DWRITE_FONT_STRETCH_NORMAL, size, L"ja-jp", &text_format);

    return hr;
}

HRESULT CText2D::SetFontColor(ID2D1SolidColorBrush* brush, DirectX::XMFLOAT4 color)
{
    //release brush
    if (brush) brush->Release();
    //create new brush
    HRESULT hr = render_target_->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush);
    return hr;
}

IDWriteTextFormat* CText2D::MakeTextFormat(std::wstring font, float size, DWRITE_FONT_WEIGHT font_weight_,
                                           DWRITE_FONT_STYLE font_style_)
{
    IDWriteTextFormat* text_format;
    //関数CreateTextFormat()
    //第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
    //第2引数：フォントコレクション（nullptr）
    //第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
    //第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
    //第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
    //第6引数：フォントサイズ（20, 30等）
    //第7引数：ロケール名（L""）
    //第8引数：テキストフォーマット（&pTextFormat_）
    HRESULT hr = dwrite_factory_->CreateTextFormat(font.c_str(), font_collection_, font_weight_, font_style_,
                                                   DWRITE_FONT_STRETCH_NORMAL, size, L"ja-jp", &text_format);
    if (FAILED(hr))
        return nullptr;
    return text_format;
}

ID2D1SolidColorBrush* CText2D::MakeBrush(XMFLOAT4 color)
{
    ID2D1SolidColorBrush* brush;
    //関数CreateSolidColorBrush()
    //第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
    HRESULT hr = render_target_->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush);
    if (FAILED(hr))
        return nullptr;
    return brush;
}

HRESULT CText2D::SetTextAlignment(IDWriteTextFormat* text_format, DWRITE_TEXT_ALIGNMENT text_alignment)
{
    HRESULT hr = text_format->SetTextAlignment(text_alignment);
    return hr;
}

//non-static function
CText2D::CText2D() : Component("Text2D",DrawCallers), Drawable(10)
{
};

CText2D::~CText2D() = default;

void CText2D::Start(){
    //フォントの設定
    text_format_ = MakeTextFormat(font_, font_size_, font_weight_, font_style_);
    text_format_->SetTextAlignment(text_alignment_);
    //フォント色の設定
    solid_brush_ = MakeBrush(font_color_);
}

void CText2D::CleanUp()
{
    if (text_format_) text_format_->Release();
    if (solid_brush_) solid_brush_->Release();
}


void CText2D::Update(){}

void CText2D::Draw()
{
    Transform transform = Manager::FindEntityByID(parent_id_)->GetTransform();
    WriteText(text_.c_str(), text_format_, solid_brush_, transform.position.x, transform.position.y, transform.scale.x, transform.scale.y);
}

std::wstring CText2D::GetFont() const
{
    return font_;
}

void CText2D::SetFont(const std::wstring& font)
{
    font_ = font;
}

float CText2D::GetFontSize() const
{
    return font_size_;
}

void CText2D::SetFontSize(float font_size)
{
    font_size_ = font_size;
}

DWRITE_FONT_WEIGHT CText2D::GetFontWeight() const
{
    return font_weight_;
}

void CText2D::SetFontWeight(DWRITE_FONT_WEIGHT font_weight)
{
    font_weight_ = font_weight;
}

DWRITE_FONT_STYLE CText2D::GetFontStyle() const
{
    return font_style_;
}

void CText2D::SetFontStyle(DWRITE_FONT_STYLE font_style)
{
    font_style_ = font_style;
}

DirectX::XMFLOAT4 CText2D::GetFontColor() const
{
    return font_color_;
}

void CText2D::SetFontColor(const DirectX::XMFLOAT4& font_color)
{
    font_color_ = font_color;
}

DWRITE_TEXT_ALIGNMENT CText2D::GetAlignment() const
{
    return text_alignment_;
}

void CText2D::SetAlignment(DWRITE_TEXT_ALIGNMENT text_alignment)
{
    text_alignment_ = text_alignment;
}

std::wstring CText2D::GetText() const
{
    return text_;
}

void CText2D::SetText(const std::wstring& text)
{
    text_ = text;
}
