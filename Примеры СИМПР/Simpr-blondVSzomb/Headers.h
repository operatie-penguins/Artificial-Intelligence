#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <conio.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9math.h>

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
