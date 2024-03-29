//
// Copyright (c) 2023, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <OptiXToolkit/ImageSource/ImageSource.h>
#include <OptiXToolkit/ImageSources/DeviceConstantImage.h>
#include <OptiXToolkit/ImageSources/DeviceMandelbrotImage.h>
#include <OptiXToolkit/ImageSources/ImageSources.h>
#include <OptiXToolkit/ImageSources/MultiCheckerImage.h>

#include <memory>

namespace imageSources {

std::shared_ptr<imageSource::ImageSource> createImageSource( const std::string& filename, const std::string& directory )
{
    if( filename == "mandelbrot" )
    {
        std::vector<float4> colors = { { 1.0f, 1.0f, 1.0f, 0.0f },
                                       { 0.0f, 0.0f, 1.0f, 0.0f },
                                       { 0.0f, 0.5f, 0.0f, 0.0f },
                                       { 1.0f, 0.0f, .0f, 0.0f },
                                       { 1.0f, 1.0f, 0.0f, 0.0f } };
        return std::make_shared<DeviceMandelbrotImage>( 2048, 2048, /*xmin=*/-2.0, /*ymin=*/-2.0,
                                                        /*xmax=*/2.0, /*ymax=*/2.0,
                                                        /*iterations=*/512, colors );
    }
    if( filename == "constant" )
    {
        // 2K, 1K, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1 = 13 colors
        std::vector<float4> mipColors = {
            { 1.0f, 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.5f, 0.0f, 0.0f },
            { 1.0f, 0.0f, .0f, 0.0f },  { 1.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.5f, 0.0f, 0.0f }, { 1.0f, 0.0f, .0f, 0.0f },
            { 1.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.5f, 0.0f, 0.0f },
        };
        return std::make_shared<DeviceConstantImage>( 2048, 2048, mipColors );
    }
    if( filename == "multichecker" )
    {
        return std::make_shared<MultiCheckerImage<float4>>( 2048, 2048, 16, true );
    }

    return imageSource::createImageSource( filename, directory );
}

}  // namespace imageSources
