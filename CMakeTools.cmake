# Copyright (C) Pavel Jakushik
# See file LICENSE for copyright and licensing details.
# https://github.com/RubyCircle/LimeEngine

function(CompileShaders)
    if(NOT RENDERER)
        message(FATAL_ERROR "Renderer is not set")
    elseif(RENDERER STREQUAL "DirectX")
        set(HLSL_SHADER_FILES ${HLSL_VERTEX_SHADER} ${HLSL_PIXEL_SHADERS})

        if(HLSL_SHADER_FILES)
            set_source_files_properties(${HLSL_VERTEX_SHADER} PROPERTIES ShaderType "vs")
            set_source_files_properties(${HLSL_PIXEL_SHADERS} PROPERTIES ShaderType "ps")
            set_source_files_properties(${HLSL_SHADER_FILES} PROPERTIES ShaderModel "5_0")

            file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

            foreach(FILE ${HLSL_SHADER_FILES})
                get_filename_component(FILE_WE ${FILE} NAME_WE)
                get_source_file_property(SHADER_TYPE ${FILE} ShaderType)
                get_source_file_property(SHADER_MODEL ${FILE} ShaderModel)

                if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
                    set(HLSL_BUILD_COMMAND fxc.exe /nologo /Emain /T${SHADER_TYPE}_${SHADER_MODEL} /Od /Zi /Fo ${SHADER_OUTPUT_DIR}/${FILE_WE}.cso /Fd ${SHADER_OUTPUT_DIR}/${FILE_WE}.pdb ${FILE})
                else()
                    set(HLSL_BUILD_COMMAND fxc.exe /nologo /Emain /T${SHADER_TYPE}_${SHADER_MODEL} /O1 /Zi /Fo ${SHADER_OUTPUT_DIR}/${FILE_WE}.cso ${FILE})
                endif()

                add_custom_command(TARGET ${PROJECT_NAME}
                    COMMAND ${HLSL_BUILD_COMMAND}
                    MAIN_DEPENDENCY ${FILE}
                    COMMENT "HLSL ${FILE}"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
                    VERBATIM
                )
            endforeach(FILE)
        endif()
    endif()
endfunction()

function(DisableRTTI)
    if(MSVC)
      string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
    else()
      string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
    endif()
endfunction()

function(InstallPDB)
    if(MSVC)
        set(pdb_file "")
        if(${TARGET_TYPE} MATCHES "^(SHARED_LIBRARY|EXECUTABLE)$")
            set(pdb_file $<TARGET_PDB_FILE:${PROJECT_NAME}>)
        else()
            set(pdb_file $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_PREFIX:${PROJECT_NAME}>$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.pdb)
        endif()
        install(FILES ${pdb_file} CONFIGURATIONS Debug RelWithDebInfo DESTINATION . OPTIONAL)
    endif()
endfunction()