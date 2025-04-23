#pragma once

#ifdef DSH_INPUT_EXPORTS
#define DSH_INPUT_API __declspec(dllexport)
#else
#define DSH_INPUT_API __declspec(dllimport)
#endif