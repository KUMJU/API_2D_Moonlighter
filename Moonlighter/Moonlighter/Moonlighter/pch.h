#pragma once

using namespace std;
#include <Windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include<vector>
#include<list>
#include<map>
#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
#include <tchar.h>

#include <vfw.h>
#pragma comment(lib, "vfw32.lib")


//#ifdef _DEBUG
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
//#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일

// - 코드 재사용을 위한 초창기 방법 중 하나, 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자에 의해 제공
// - 라이브러리의 대다수 함수들은 함수의 정의 및 선언들을 필요로 하기 때문에 링크되기 전 전처리기에 의해 해당 헤더파일을 원시 프로그램(현재 사용자가 작성한 프로그램)에 포함시켜야 한다.
// - 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 된다.

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>
#include <iostream>