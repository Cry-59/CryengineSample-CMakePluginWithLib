#pragma once

struct IPublicInterface
{
	virtual const char * GetName() = 0;
	virtual const char * GetVersion() = 0;
};

// Exported functions
extern "C"
{
	__declspec(dllexport) void CreatePublicInterface();

	__declspec(dllexport) IPublicInterface * GetPublicInterface();

	__declspec(dllexport) void DestroyPublicInterface();
}