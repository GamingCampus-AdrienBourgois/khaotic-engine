#include "shadermanagerclass.h"

ShaderManagerClass::ShaderManagerClass()
{
    m_TextureShader = 0;
    m_LightShader = 0;
    m_NormalMapShader = 0;
    m_MultitextureShader = 0;
    m_TranslateShader = 0;
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

    // Create and initialize the light shader object.
    m_LightShader = new LightShaderClass;

    result = m_LightShader->Initialize(device, hwnd);
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

    // Release the light shader object.
    if (m_LightShader)
    {
        m_LightShader->Shutdown();
        delete m_LightShader;
        m_LightShader = 0;
    }

    // Release the texture shader object.
    if (m_TextureShader)
    {
        m_TextureShader->Shutdown();
        delete m_TextureShader;
        m_TextureShader = 0;
    }

    // Release the multitexture shader object.
    if (m_TranslateShader)
    {
        m_TranslateShader->Shutdown();
        delete m_TranslateShader;
        m_TranslateShader = 0;
    }
    
    // Release the multitexture shader object.
    if (m_MultitextureShader)
    {
        m_MultitextureShader->Shutdown();
        delete m_MultitextureShader;
        m_MultitextureShader = 0;
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

bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
    bool result;

    // Allouer de la mémoire pour stocker XMFLOAT4 pour la direction de la lumière
    XMFLOAT4* lightDirection4Ptr = new XMFLOAT4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f);

    // Allouer de la mémoire pour stocker XMFLOAT4 pour la couleur diffuse
    XMFLOAT4* diffuseColorPtr = new XMFLOAT4(diffuseColor);

    result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection4Ptr, diffuseColorPtr);
    if (!result)
    {
        delete lightDirection4Ptr;
        delete diffuseColorPtr;
        return false;
    }

    delete lightDirection4Ptr;
    delete diffuseColorPtr;
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