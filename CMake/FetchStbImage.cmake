#
# Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

if(TARGET Stb::Image)
    return()
endif()

include(FetchContent)

FetchContent_Declare(stb_image 
  URL https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
  DOWNLOAD_NO_EXTRACT TRUE
  )
FetchContent_MakeAvailable(stb_image)

FetchContent_Declare(stb_image_write
  URL https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
  DOWNLOAD_NO_EXTRACT TRUE
  )
FetchContent_MakeAvailable(stb_image_write)

# stb image library
add_library(StbImage STATIC
    ${CMAKE_CURRENT_LIST_DIR}/stb.cpp
    ${stb_image_SOURCE_DIR}/stb_image.h
    ${stb_image_write_SOURCE_DIR}/stb_image_write.h
)
target_include_directories(StbImage
    PUBLIC
        ${stb_image_SOURCE_DIR}
        ${stb_image_write_SOURCE_DIR}
)
if(NOT MSVC)
  target_compile_options(StbImage PRIVATE -Wno-missing-field-initializers)
endif()
set_target_properties(StbImage PROPERTIES FOLDER ThirdParty)

add_library(Stb::Image ALIAS StbImage)
