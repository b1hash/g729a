cmake_minimum_required(VERSION 3.10)
project(G729a VERSION 1.0 LANGUAGES C CXX)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Source files for the library
set(G729A_SOURCES
    src/acelp_ca.c
    src/basic_op.c
    src/bits.c
    src/cod_ld8a.c
    src/cor_func.c
    src/de_acelp.c
    src/dec_gain.c
    src/dec_lag3.c
    src/dec_ld8a.c
    src/dspfunc.c
    src/filter.c
    src/g729a_interface.c
    src/gainpred.c
    src/lpc.c
    src/lpcfunc.c
    src/lspdec.c
    src/lspgetq.c
    src/oper_32b.c
    src/p_parity.c
    src/pitch_a.c
    src/post_pro.c
    src/postfilt.c
    src/pre_proc.c
    src/pred_lt3.c
    src/qua_gain.c
    src/qua_lsp.c
    src/tab_ld8a.c
    src/taming.c
    src/util.c
    src/interface/va_g729a_interface.c
)

# Header files
set(G729A_HEADERS
    src/basic_op.h
    src/g729a_decoder.h
    src/g729a_defines.h
    src/g729a_encoder.h
    src/get_bits.h
    src/interface/g729a_errors.h
    src/interface/g729a_interface.h
    src/interface/g729a_typedef.h
    src/interface/va_g729a_interface.h
    src/ld8a.h
    src/oper_32b.h
    src/put_bits.h
    src/tab_ld8a.h
)

# Create static library
add_library(g729a STATIC ${G729A_SOURCES} ${G729A_HEADERS})

# Include directories
target_include_directories(g729a PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interface
)

# Set library output name based on configuration
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64-bit build
        set_target_properties(g729a PROPERTIES
            OUTPUT_NAME_DEBUG "G729a_ud_x64"
            OUTPUT_NAME_RELEASE "G729a_u_x64"
            OUTPUT_NAME_RELWITHDEBINFO "G729a_u_x64"
            OUTPUT_NAME_MINSIZEREL "G729a_u_x64"
        )
    else()
        # 32-bit build
        set_target_properties(g729a PROPERTIES
            OUTPUT_NAME_DEBUG "G729a_ud"
            OUTPUT_NAME_RELEASE "G729a_u"
            OUTPUT_NAME_RELWITHDEBINFO "G729a_u"
            OUTPUT_NAME_MINSIZEREL "G729a_u"
        )
    endif()
else()
    # For non-Windows platforms, use a simple name
    set_target_properties(g729a PROPERTIES
        OUTPUT_NAME "g729a"
    )
endif()

# Set output directories
set_target_properties(g729a PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Export header files for installation
set_target_properties(g729a PROPERTIES PUBLIC_HEADER "${G729A_HEADERS}")

# Installation rules
install(TARGETS g729a
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/g729a
)

# Optionally build the original test programs
option(BUILD_TESTS "Build test programs (coder and decoder)" OFF)

if(BUILD_TESTS)
    add_executable(coder src/coder.c)
    target_link_libraries(coder g729a)
    target_include_directories(coder PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interface
    )

    add_executable(decoder src/decoder.c)
    target_link_libraries(decoder g729a)
    target_include_directories(decoder PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interface
    )
endif()
