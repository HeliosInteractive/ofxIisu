#pragma once

#ifndef OVERRIDE_NEW_API
#ifdef OVERRIDE_NEW_EXPORTS
#define OVERRIDE_NEW_API __declspec(dllexport)
#define OVERRIDE_NEW_CAPI extern "C" __declspec(dllexport)
#else
#define OVERRIDE_NEW_API __declspec(dllimport)
#define OVERRIDE_NEW_CAPI extern "C" __declspec(dllexport)
#endif
#endif

