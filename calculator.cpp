#include <windows.h>
#include <cstring>
#include <string>

HWND input1;
HWND input2;

char inputSave1[20];
char inputSave2[20];
char result[50];

double resultValue;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{

	/* Upon destruction, tell the main thread to stop */
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_COMMAND:
		GetWindowTextA(input1, &inputSave1[0], 20);
		GetWindowTextA(input2, &inputSave2[0], 50);
		switch (LOWORD(wParam))
		{
		case 1:
			resultValue = atof(inputSave1) + atof(inputSave2);
			sprintf(result, "%f", resultValue);
			MessageBoxA(hwnd, result, "Result", MB_OK);
			break;
		case 2:
			resultValue = atof(inputSave1) - atof(inputSave2);
			sprintf(result, "%f", resultValue);
			MessageBoxA(hwnd, result, "Result", MB_OK);
			break;
		case 3:
			resultValue = atof(inputSave1) * atof(inputSave2);
			sprintf(result, "%f", resultValue);
			MessageBoxA(hwnd, result, "Result", MB_OK);
			break;
		case 4:
			resultValue = atof(inputSave1) / atof(inputSave2);
			sprintf(result, "%f", resultValue);
			MessageBoxA(hwnd, result, "Result", MB_OK);
			break;
		}
		break;

	/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 7);
	wc.lpszClassName = TEXT("WindowClass");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	  /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	wc.hbrBackground = CreateSolidBrush(RGB(50, 150, 200));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("WindowClass"), TEXT("My Calculator"), WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  250,			 /* width */
						  200,			 /* height */
						  NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	CreateWindowW(L"static", L"Please input two numbers", WS_VISIBLE | WS_CHILD, 20 ,20 ,200 ,25, hwnd, NULL, NULL, NULL);
	input1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD, 20 ,55 ,200 ,25, hwnd, NULL, NULL, NULL);
	input2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD, 20 ,85 ,200 ,25, hwnd, NULL, NULL, NULL);

	// 200 - 20 * 3 = 140 / 4 = 35
	// width 35 เว้น 20
	CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD, 30 ,123 ,40 ,25 ,hwnd ,(HMENU) 1 ,NULL ,NULL);
	CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD, 75 ,123 ,40 ,25 ,hwnd ,(HMENU) 2 ,NULL ,NULL);
	CreateWindowW(L"Button", L"*", WS_VISIBLE | WS_CHILD, 120 ,123 ,40 ,25 ,hwnd ,(HMENU) 3 ,NULL ,NULL);
	CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD, 165 ,123 ,40 ,25 ,hwnd ,(HMENU) 4 ,NULL ,NULL);

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}