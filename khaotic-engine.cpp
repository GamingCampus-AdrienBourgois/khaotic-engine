//Include and link appropriate libraries and headers//
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3d10.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <DirectXPackedVector.h>

//Global Declarations//
IDXGISwapChain* SwapChain; //SwapChain c'est le buffer qui contient les frames
ID3D11Device* d3d11Device; //Device c'est le GPU
ID3D11DeviceContext* d3d11DevCon; //DeviceContext c'est le CPU
ID3D11RenderTargetView* renderTargetView; //RenderTargetView c'est la surface sur laquelle on dessine

float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
int colormodr = 1;
int colormodg = 1;
int colormodb = 1;

LPCTSTR WndClassName = L"firstwindow"; //Nom de la fenêtre
HWND hwnd = NULL; //Handle de la fenêtre

const int Width = 300;
const int Height = 300;

//Function Prototypes//
bool InitializeDirect3d11App(HINSTANCE hInstance); //Initialisation de Direct3D
void ReleaseObjects(); //Fonction pour libérer les objets
bool InitScene();
void UpdateScene();
void DrawScene();

bool InitializeWindow(HINSTANCE hInstance,
    int ShowWnd,
    int width, int height,
    bool windowed);
int messageloop();

LRESULT CALLBACK WndProc(HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam);


int WINAPI WinMain(_In_ HINSTANCE hInstance,    //Main windows function
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{

    if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
    {
        MessageBox(0, L"Window Initialization - Failed",
            L"Error", MB_OK);
        return 0;
    }


    if (!InitializeDirect3d11App(hInstance))    //Initialize Direct3D
    {
        MessageBox(0, L"Direct3D Initialization - Failed",
            L"Error", MB_OK);
        return 0;
    }

    if (!InitScene())    //Initialize our scene
    {
        MessageBox(0, L"Scene Initialization - Failed",
            L"Error", MB_OK);
        return 0;
    }

    messageloop();

    ReleaseObjects();

    return 0;
}

bool InitializeWindow(HINSTANCE hInstance,
    int ShowWnd,
    int width, int height,
    bool windowed)
{
    typedef struct _WNDCLASS {
        UINT cbSize;
        UINT style;
        WNDPROC lpfnWndProc;
        int cbClsExtra;
        int cbWndExtra;
        HANDLE hInstance;
        HICON hIcon;
        HCURSOR hCursor;
        HBRUSH hbrBackground;
        LPCTSTR lpszMenuName;
        LPCTSTR lpszClassName;
    } WNDCLASS;

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX); // taille de la structure
    wc.style = CS_HREDRAW | CS_VREDRAW; // style de la fenêtre
    wc.lpfnWndProc = WndProc; // pointeur vers la fonction de la fenêtre
    wc.cbClsExtra = NULL; // taille de mémoire supplémentaire pour la classe
    wc.cbWndExtra = NULL; // taille de mémoire supplémentaire pour la fenêtre
    wc.hInstance = hInstance; // handle de l'instance
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // handle de l'icone
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // handle du curseur
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2); // handle du fond de la fenêtre
    wc.lpszMenuName = NULL; 
    wc.lpszClassName = WndClassName; // nom de la classe
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // handle de l'icone de la fenêtre

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Error registering class",
            L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    hwnd = CreateWindowEx( // création de la fenêtre
        NULL,
        WndClassName,
        L"Khaotic Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
    {
        MessageBox(NULL, L"Error creating window",
            L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, ShowWnd);
    UpdateWindow(hwnd);

    return true;
}

bool InitializeDirect3d11App(HINSTANCE hInstance)
{
    //Describe our Buffer
    DXGI_MODE_DESC bufferDesc; // description du buffer

    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC)); // vide la mémoire

    bufferDesc.Width = Width;
    bufferDesc.Height = Height;
    bufferDesc.RefreshRate.Numerator = 60; // taux de rafraichissement
    bufferDesc.RefreshRate.Denominator = 1; // taux de rafraichissement
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // format des pixels (32 bits)
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ordre des lignes
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // mise à l'échelle
    
    //Describe our SwapChain
    DXGI_SWAP_CHAIN_DESC swapChainDesc; // description du swapchain

    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC)); // vide la mémoire

    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SampleDesc.Count = 4; //multisampling standard
    swapChainDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // utilisation du buffer pour le rendu
    swapChainDesc.BufferCount = 2; // triple buffering
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 


    //Create our SwapChain
    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

    //Create our BackBuffer
    ID3D11Texture2D* BackBuffer;
    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

    //Create our Render Target
    d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView); // associe le buffer à la surface de rendu
    BackBuffer->Release();

    //Set our Render Target
    d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, NULL); // associe la surface de rendu au device context

    return true;
}

void ReleaseObjects() // Fonction pour libérer les objets
{
    //Release the COM Objects we created
    SwapChain->Release();
    d3d11Device->Release();
    d3d11DevCon->Release();
}

bool InitScene()
{

    return true;
}

void UpdateScene()
{
    //Update the colors of our scene
    red += colormodr * 0.00005f;
    green += colormodg * 0.00002f;
    blue += colormodb * 0.00001f;

    if (red >= 1.0f || red <= 0.0f)
        colormodr *= -1;
    if (green >= 1.0f || green <= 0.0f)
        colormodg *= -1;
    if (blue >= 1.0f || blue <= 0.0f)
        colormodb *= -1;
}

void DrawScene()
{
    //Clear our backbuffer to the updated color
    DirectX::XMFLOAT4 bgColor(red, green, blue, 1.0f);
    float color[4] = { bgColor.x, bgColor.y, bgColor.z, bgColor.w };
    d3d11DevCon->ClearRenderTargetView(renderTargetView, color);

    //Present the backbuffer to the screen
    SwapChain->Present(0, 0);
}

int messageloop() {
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG)); // vide la mémoire
    while (true)
    {
        BOOL PeekMessageL(
            LPMSG lpMsg,
            HWND hWnd,
            UINT wMsgFilterMin,
            UINT wMsgFilterMax,
            UINT wRemoveMsg
        );

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            UpdateScene();
            DrawScene();
        }
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd,
        msg,
        wParam,
        lParam);
}
