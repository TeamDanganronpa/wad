#ifndef WAD_API_H
#define WAD_API_H

#ifdef _WIN32
	#ifdef WAD_DLL
		#ifdef WAD_COMPILATION
			#define WAD_API __declspec(dllexport)
		#else
			#define WAD_API __declspec(dllimport)
		#endif
	#else
		#define WAD_API
	#endif
#else
	#define WAD_API
#endif

#endif // WAD_API_H
