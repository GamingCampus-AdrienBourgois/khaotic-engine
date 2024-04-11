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
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
    logger.Log("Initializing ShaderManagerClass", __FILE__, __LINE__);

    bool result;

    // Create and initialize the texture shader object.
    m_TextureShader = new TextureShaderClass;

    result = m_TextureShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing TextureShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the normal map shader object.
    m_NormalMapShader = new NormalMapShaderClass;

    result = m_NormalMapShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing NormalMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the multitexture shader object.
    m_MultitextureShader = new MultiTextureShaderClass;

    result = m_MultitextureShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing MultiTextureShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the translate shader object.
    m_TranslateShader = new TranslateShaderClass;

    result = m_TranslateShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing TranslateShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the alpha map shader object.
    m_AlphaMapShader = new AlphaMapShaderClass;

    result = m_AlphaMapShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing AlphaMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the specular map shader object.
    m_SpecMapShader = new SpecMapShaderClass;

    result = m_SpecMapShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing SpecMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Create and initialize the specular map shader object.
    m_TransparentShader = new TransparentShaderClass;

    result = m_TransparentShader->Initialize(device, hwnd);
    if (!result)
    {
        logger.Log("Error initializing TransparentShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    logger.Log("ShaderManagerClass initialized", __FILE__, __LINE__);

    return true;
}

void ShaderManagerClass::Shutdown()
{
    logger.Log("Shutting down ShaderManagerClass", __FILE__, __LINE__);

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

    logger.Log("ShaderManagerClass shut down", __FILE__, __LINE__);

    return;
      
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture)
{
    bool result;


    result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
    if (!result)
    {
        logger.Log("Error rendering TextureShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering NormalMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering MultiTextureShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering TranslateShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering AlphaMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering SpecMapShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
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
        logger.Log("Error rendering TransparentShaderClass", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    return true;
}