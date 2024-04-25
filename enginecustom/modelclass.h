#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "Logger.h"
#include <d3d11.h>
#include <directxmath.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <vector>
#include <string>

using namespace DirectX;
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
protected:
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
        XMFLOAT3 normal;
        XMFLOAT3 tangent;
        XMFLOAT3 binormal;
    };

    struct Face
    {
        int v1, v2, v3;
        int t1, t2, t3;
        int n1, n2, n3;
    };

    // Define TempVertexType struct
    struct TempVertexType
    {
        float x, y, z;
        float tu, tv;
        float nx, ny, nz;
    };

    // Define VectorType struct
    struct VectorType
    {
        float x, y, z;
    };


public:
    ModelClass();
    ModelClass(const ModelClass&);
    ~ModelClass();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
    void Shutdown();
    void Render(ID3D11DeviceContext*);

    int GetIndexCount();
    ID3D11ShaderResourceView* GetTexture(int);

private:
    bool InitializeBuffers(ID3D11Device*);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext*);
    bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, const char*, const char*, const char*, const char*);
    void ReleaseTextures();

    bool LoadModel(const char*);
    void ReleaseModel();

    void CalculateModelVectors();
    void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

private:
    ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
    int m_vertexCount, m_indexCount;
    TextureClass* m_Textures;

    Logger logger;
};

#endif // _MODELCLASS_H_