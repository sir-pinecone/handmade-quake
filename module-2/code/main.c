#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#define internal static
#define global_variable static

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


struct win32_window_dimension {
  int width;
  int height;
};

// ===============================
// Game Globals
// ===============================
// TODO: global for now
global_variable bool32 GlobalRunning;


internal LRESULT CALLBACK Win32MainWindowCallback(HWND window, UINT Message, WPARAM WParam, LPARAM LParam) {
  LRESULT Result = 0;
  switch (Message) {
    case WM_SIZE: {
    } break;
    case WM_ACTIVATEAPP: {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
    case WM_CLOSE: {
      // TODO: handle this with a message to the user?
      GlobalRunning = 0;
    } break;
    case WM_DESTROY: {
      // TODO handle this as an error then recreate window?
      GlobalRunning = 0;
    } break;
      // syskey will include things like alt-f4
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP: {
      uint32 VKCode = WParam;
      bool32 wasDown = ((LParam & (1 << 30)) != 0);
      bool32 isDown = ((LParam & (1 << 31)) == 0);

      // stop key repeats
      if (wasDown != isDown) {
        if (VKCode == 'W') {
        }
        else if (VKCode == 'A') {
        }
        else if (VKCode == 'S') {
        }
        else if (VKCode == 'D') {
        }
        else if (VKCode == 'Q') {
        }
        else if (VKCode == 'E') {
        }
        else if (VKCode == VK_UP) {
        }
        else if (VKCode == VK_LEFT) {
        }
        else if (VKCode == VK_DOWN) {
        }
        else if (VKCode == VK_RIGHT) {
        }
        else if (VKCode == VK_ESCAPE) {
          GlobalRunning = 0;
        }
        else if (VKCode == VK_SPACE) {
        }

        bool32 altKeyIsDown = (LParam & (1 << 29));
        if ((VKCode == VK_F4) && altKeyIsDown) {
          GlobalRunning = 0;
        }
      }
    } break;
    case WM_PAINT: {
        PAINTSTRUCT paint;
        HDC deviceContext = BeginPaint(window, &paint);
        //   win32_window_dimension dimension = Win32GetWindowDimension(window);
        //   Win32RenderBuffer(&GlobalBackbuffer, deviceContext, dimension.width, dimension.height);
        RECT clientRect;
        GetClientRect(window, &clientRect);
        int32 width = clientRect.right - clientRect.left;
        int32 height = clientRect.bottom - clientRect.top;

        PatBlt(deviceContext, 0, 0, width, height, BLACKNESS);
        EndPaint(window, &paint);
    } break;
    default: {
      Result = DefWindowProc(window, Message, WParam, LParam);
    } break;
  }
  return Result;
}


int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode) {
  WNDCLASSA windowClass = {0}; // reset block to 0

  windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowClass.lpfnWndProc = Win32MainWindowCallback;
  windowClass.hInstance = Instance; // or get the instance of GlobalRunning window with GetModulehandle(0)
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  // WindowClass.hIcon = ;
  windowClass.lpszClassName = "handmadeQuakeModule2WindowClass";

  int32 defaultWidth = 800;
  int32 defaultHeight = 600;

  if (RegisterClass(&windowClass)) {
    DWORD windowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    // Get an adjusted rendering rect to take full advantage of the window area for drawing.
    // (MC) Not sure why Philip added this...
    RECT r;
    r.top = r.left = 0;
    r.right = defaultWidth;
    r.bottom = defaultHeight;
    AdjustWindowRect(&r, windowStyle, FALSE);

    HWND window = CreateWindowEx(
      0,
      windowClass.lpszClassName,
      "Handmade Quake Module 2",
      windowStyle,
      CW_USEDEFAULT, // x
      CW_USEDEFAULT, // y
      r.right - r.left, // w
      r.bottom - r.top, // h
      0,
      0,
      Instance,
      0 // provides a callback message called WM_CREATE
    );

    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);
    
    double SecondsPerTick = 1.0 / (double)Frequency.QuadPart;

    LARGE_INTEGER Tick, Tock;
    QueryPerformanceCounter(&Tick);

    if (window) {
      GlobalRunning = 1;

      while (GlobalRunning) {
        MSG Message;
        // Don't use the blocking GetMessageA since we want to use the idle time
        while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
          // Flush the queue before rendering
          if (Message.message == WM_QUIT) {
              GlobalRunning = 1;
          }
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        }
        // TODO: update game if it's time
        // TODO: render game if it's time

        // Calculate game loop timing
        QueryPerformanceCounter(&Tock);
        __int64 Interval = Tock.QuadPart - Tick.QuadPart;
        double SecondsGoneBy = (double)Interval * SecondsPerTick;

        //char buf[64];
        //sprintf_s(buf, 64, "Total time: %3.7f \n", SecondsGoneBy);
        //OutputDebugStringA(buf);

        Tick = Tock;
      }
    }
  }
  return 0;
}
