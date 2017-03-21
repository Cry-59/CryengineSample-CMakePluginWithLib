# Project: CMakePluginWithLib
# Brief: Top level CMakeLists
# Project Type: Dynamic DLL
# 
# Adds the third-party include and lib folders to the project and linker settings on project generation
# This is a bare bones example demonstrating the a very simple integration of a third-party library

cmake_minimum_required (VERSION 3.6.0)

# Standard CMakeLists setup for a plugin project...

# Top-Level CMake project. (This string defines the output name - dll name)
project ("CMakePluginWithLib" VERSION 1.0 LANGUAGES CXX)

option(OPTION_PCH "Enable Precompiled headers" ON)

# Required Packages
find_package (CryCommon REQUIRED)

# Source files
set (SourceGroup_NoUber
	"StdAfx.cpp"
	"StdAfx.h"
)
source_group("" FILES ${SourceGroup_NoUber})

set (SourceGroup_Source
	"Plugin.cpp"
)
source_group("Source Files" FILES ${SourceGroup_Source})

set (SourceGroup_Header
	"Plugin.h"
)
source_group("Header Files" FILES ${SourceGroup_Header})

set (SOURCE
	${SourceGroup_Source}
	${SourceGroup_Header}
	${SourceGroup_NoUber}
)

if(OPTION_PCH AND MSVC)
	set (PRECOMPILED_SOURCE ${SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCE "StdAfx.cpp")

	set (PRECOMPILED_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pch)
	set_source_files_properties (${PRECOMPILED_SOURCE} PROPERTIES COMPILE_FLAGS "/Yu\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_DEPENDS "${PRECOMPILED_BINARY}")
	set_source_files_properties (StdAfx.cpp PROPERTIES COMPILE_FLAGS "/Yc\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_OUTPUTS "${PRECOMPILED_BINARY}")
endif (OPTION_PCH AND MSVC)

link_directories("../ThirdPartyLibs/ThirdPartyLib/lib")
add_library(${PROJECT_NAME} MODULE ${SOURCE})

# Add the third-party interface directory
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  "../ThirdPartyLibs/ThirdPartyLib/include"
)

# Add a Post-Build step to copy the third-party binary to the used engine dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/../ThirdPartyLibs/ThirdPartyLib/bin/ThirdPartyLib.dll" "${CryEngine_DIR}/bin/win_x64/"
)
target_link_libraries(${PROJECT_NAME} PRIVATE CryCommon)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE Ntdll)
endif(WIN32)

