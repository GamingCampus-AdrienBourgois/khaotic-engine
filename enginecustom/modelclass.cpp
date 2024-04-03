#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Textures = 0;
	m_model = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* modelFilename, char* textureFilename1, char* textureFilename2)
{
	bool result;

	// Load in the model data.
	result = LoadModel(modelFilename);
	if (!result)
	{
		MessageBox(NULL, L"Could not load model data.", L"Error", MB_OK);
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		MessageBox(NULL, L"Could not initialize the buffers.", L"Error", MB_OK);
		return false;
	}
	// Load the textures for this model.
	result = LoadTextures(device, deviceContext, textureFilename1, textureFilename2);
	if (!result)
	{
		MessageBox(NULL, L"Could not load the textures.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Release the model textures.
	ReleaseTextures();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture(int index)
{
	return m_Textures[index].GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];

	// Create the index array.
	indices = new unsigned long[m_indexCount];

	// Load the vertex array and index array with data.
	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename1, char* filename2)
{
	bool result;


	// Create and initialize the texture object array.
	m_Textures = new TextureClass[2];

	result = m_Textures[0].Initialize(device, deviceContext, filename1);
	if (!result)
	{
		return false;
	}

	result = m_Textures[1].Initialize(device, deviceContext, filename2);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTextures()
{
	// Release the texture object array.
	if (m_Textures)
	{
		m_Textures[0].Shutdown();
		m_Textures[1].Shutdown();

		delete[] m_Textures;
		m_Textures = 0;
	}

	return;
}

bool ModelClass::LoadModel(char* filename)
{
	std::ifstream fin;
	std::string line;
	std::vector<XMFLOAT3> vertices;
	std::vector<XMFLOAT2> textures;
	std::vector<XMFLOAT3> normals;
	std::vector<ModelType> modelData;

	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read the file line by line.
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v")
		{
			XMFLOAT3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (type == "vt")
		{
			XMFLOAT2 texture;
			iss >> texture.x >> texture.y;
			textures.push_back(texture);
		}
		else if (type == "vn")
		{
			XMFLOAT3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (type == "f")
		{
			std::string vertexInfo;
			std::vector<ModelType> faceData;

			// Parse each vertex of the face.
			while (iss >> vertexInfo)
			{
				ModelType model;
				int v, vt, vn;

				sscanf_s(vertexInfo.c_str(), "%d/%d/%d", &v, &vt, &vn);
				model.x = vertices[v - 1].x;
				model.y = vertices[v - 1].y;
				model.z = vertices[v - 1].z;
				model.tu = textures[vt - 1].x;
				model.tv = textures[vt - 1].y;
				model.nx = normals[vn - 1].x;
				model.ny = normals[vn - 1].y;
				model.nz = normals[vn - 1].z;
				faceData.push_back(model);
			}

			// Triangulate the face.
			modelData.push_back(faceData[0]);
			modelData.push_back(faceData[1]);
			modelData.push_back(faceData[2]);

			if (faceData.size() > 3) // If the face is not a triangle
			{
				modelData.push_back(faceData[0]);
				modelData.push_back(faceData[2]);
				modelData.push_back(faceData[3]);
			}

		}
	}

	// Close the model file.
	fin.close();

	// Set the vertex and index counts.
	m_vertexCount = modelData.size();
	m_indexCount = modelData.size();

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];

	// Copy the model data into the class's model data.
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_model[i] = modelData[i];
	}

	return true;
}


void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}