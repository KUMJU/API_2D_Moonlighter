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

// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��Ƴ��� ����

// - �ڵ� ������ ���� ��â�� ��� �� �ϳ�, �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڿ� ���� ����
// - ���̺귯���� ��ټ� �Լ����� �Լ��� ���� �� ������� �ʿ�� �ϱ� ������ ��ũ�Ǳ� �� ��ó���⿡ ���� �ش� ��������� ���� ���α׷�(���� ����ڰ� �ۼ��� ���α׷�)�� ���Խ��Ѿ� �Ѵ�.
// - ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� �ȴ�.

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>
#include <iostream>