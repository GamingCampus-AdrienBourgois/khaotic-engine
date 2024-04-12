#include "shadermanagerclass.h"

ShaderManagerClass::ShaderManagerClass()
{
    m_TextureShader = 0;
    m_NormalMapShader = 0;
    m_MultitextureShader = 0;
    m_TranslateShader = 0;
    m_AlphaMapShader = 0;
    m_SpecMapShader = 0;
    m_TransparentShader = 0;
    m_LightShader = 0;
    m_LightMapShader = 0;
    m_RefractionShader = 0;
    m_WaterShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
    bool result;

    // Create and initialize the texture shader object.
    m_TextureShader = new TextureShaderClass;

    result = m_TextureShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the normal map shader object.
    m_NormalMapShader = new NormalMapShaderClass;

    result = m_NormalMapShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the multitexture shader object.
    m_MultitextureShader = new MultiTextureShaderClass;

    result = m_MultitextureShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the translate shader object.
    m_TranslateShader = new TranslateShaderClass;

    result = m_TranslateShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the alpha map shader object.
    m_AlphaMapShader = new AlphaMapShaderClass;

    result = m_AlphaMapShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the specular map shader object.
    m_SpecMapShader = new SpecMapShaderClass;

    result = m_SpecMapShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the transparent shader object.
    m_TransparentShader = new TransparentShaderClass;

    result = m_TransparentShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the light shader object.
    m_LightShader = new LightShaderClass;

    result = m_LightShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the light map shader object.
    m_LightMapShader = new LightMapShaderClass;

    result = m_LightMapShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the refraction shader object.
    m_RefractionShader = new RefractionShaderClass;

    result = m_RefractionShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the water shader object.
    m_WaterShader = new WaterShaderClass;

    result = m_WaterShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    return true;
}

void ShaderManagerClass::Shutdown()
{
    // Release the normal map shader object.
    if (m_NormalMapShader)
    {
        m_NormalMapShader->Shutdown();
        delete m_NormalMapShader;
        m_NormalMapShader = 0;
    }

    // Release the texture shader object.
    if (m_TextureShader)
    {
        m_TextureShader->Shutdown();
        delete m_TextureShader;
        m_TextureShader = 0;
    }

    // Release the multitexture shader object.
    if (m_MultitextureShader)
    {
        m_MultitextureShader->Shutdown();
        delete m_MultitextureShader;
        m_MultitextureShader = 0;
    }

    // Release the multitexture shader object.
    if (m_TranslateShader)
    {
        m_TranslateShader->Shutdown();
        delete m_TranslateShader;
        m_TranslateShader = 0;
    }

    // Release the alpha map shader object.
    if (m_AlphaMapShader)
    {
        m_AlphaMapShader->Shutdown();
        delete m_AlphaMapShader;
        m_AlphaMapShader = 0;
    }

    // Release the specular map shader object.
    if (m_SpecMapShader)
    {
        m_SpecMapShader->Shutdown();
        delete m_SpecMapShader;
        m_SpecMapShader = 0;
    }

    // Release the transparent shader object.
    if (m_TransparentShader)
    {
        m_TransparentShader->Shutdown();
        delete m_TransparentShader;
        m_TransparentShader = 0;
    }

    // Release the light shader object.
    if (m_LightShader)
    {
        m_LightShader->Shutdown();
        delete m_LightShader;
        m_LightShader = 0;
    }

    // Release the light map shader object.
    if (m_LightMapShader)
    {
        m_LightMapShader->Shutdown();
        delete m_LightMapShader;
        m_LightMapShader = 0;
    }

    // Release the refraction shader object.
    if (m_RefractionShader)
    {
        m_RefractionShader->Shutdown();
        delete m_RefractionShader;
        m_RefractionShader = 0;
    }

    // Release the water shader object.
    if (m_WaterShader)
    {
        m_WaterShader->Shutdown();
        delete m_WaterShader;
        m_WaterShader = 0;
    }

    return;
      
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture)
{
    bool result;


    result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderNormalMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
    bool result;


    result = m_NormalMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderMultitextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2)
{
    bool result;


    result = m_MultitextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, texture2);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderTranslateShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture1, float valeur)
{
    bool result;


    result = m_TranslateShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, valeur);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderAlphaMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2, ID3D11ShaderResourceView* texture3)
{
    bool result;


    result = m_AlphaMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, texture2, texture3);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderSpecMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2, ID3D11ShaderResourceView* texture3,
    XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
    bool result;


    result = m_SpecMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, texture2, texture3, lightDirection, 
        diffuseColor, cameraPosition, specularColor, specularPower);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderTransparentShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture1, float blendAmount)
{
    bool result;


    result = m_TransparentShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, blendAmount);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderlightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture, XMFLOAT4 diffuseColor[], XMFLOAT4 lightPosition[])
{
    bool result;


    result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderlightMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2)
{
    bool result;


    result = m_LightMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture1, texture2);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderRefractionShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT4 clipPlane)
{
    bool result;


    result = m_RefractionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor, clipPlane);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderWaterShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    XMMATRIX reflectionMatrix, ID3D11ShaderResourceView* reflectionTexture, ID3D11ShaderResourceView* refractionTexture,
    ID3D11ShaderResourceView* normalTexture, float waterTranslation, float reflectRefractScale)
{
    bool result;


    result = m_WaterShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, reflectionTexture,
        refractionTexture, normalTexture, waterTranslation, reflectRefractScale);
    if (!result)
    {
        return false;
    }

    return true;
}