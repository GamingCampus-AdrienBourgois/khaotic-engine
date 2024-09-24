#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureshaderclass.h"
#include "normalmapshaderclass.h"
#include "Multitextureshaderclass.h"
#include "translateshaderclass.h"
#include "alphamapshaderclass.h"
#include "specmapshaderclass.h"
#include "transparentshaderclass.h"
#include "lightshaderclass.h"
#include "lightmapshaderclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include "CelShadingShader.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
    ShaderManagerClass();
    ShaderManagerClass(const ShaderManagerClass&);
    ~ShaderManagerClass();

    bool Initialize(ID3D11Device*, HWND);
    void Shutdown();
    bool RenderTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
    bool RenderNormalMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
    bool RenderMultitextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
    bool RenderTranslateShader(ID3D11DeviceContext*,int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float);
    bool RenderAlphaMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
    bool RenderSpecMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
        XMFLOAT3, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);
    bool RenderTransparentShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float);
    bool RenderlightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4[], XMFLOAT4[], XMFLOAT4[]);
    bool RenderlightMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
    bool RenderRefractionShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
        XMFLOAT3, XMFLOAT4[], XMFLOAT4[], XMFLOAT4[], XMFLOAT4);
    bool RenderWaterShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
        ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, float);
	bool RenderCelShadingShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4[]);
private:
    TextureShaderClass* m_TextureShader;
    NormalMapShaderClass* m_NormalMapShader;
    MultiTextureShaderClass* m_MultitextureShader;
    TranslateShaderClass* m_TranslateShader;
    AlphaMapShaderClass* m_AlphaMapShader;
    SpecMapShaderClass* m_SpecMapShader;
    TransparentShaderClass* m_TransparentShader;

    LightShaderClass* m_LightShader;
    LightMapShaderClass* m_LightMapShader;
    RefractionShaderClass* m_RefractionShader;
    WaterShaderClass* m_WaterShader;
	CelShadingShader* m_CelShadingShader;
};

#endif