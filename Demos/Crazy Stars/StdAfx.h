#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

#include <GUI.h>
#include <ParticleSystem.h>
#include <SceneManager.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <time.h>
#include <math.h>

#define SCENE_MENU	1
#define SCENE_STARS	2