//
// Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
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

#include <OptiXToolkit/Gui/glad.h>  // Glad insists on being included first.

#include <OptiXToolkit/Error/cudaErrorCheck.h>

#include <iostream>
#include <sstream>

namespace otk {
    
const char* getGLErrorString( GLenum error )
{
    switch( error )
    {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        //case GL_STACK_OVERFLOW:      return "Stack overflow";
        //case GL_STACK_UNDERFLOW:     return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        //case GL_TABLE_TOO_LARGE:     return "Table too large";
        default:
            return "Unknown GL error";
    }
}

void glCheck( const char* call, const char* file, unsigned int line )
{
    GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
        std::stringstream ss;
        ss << "GL error " << getGLErrorString( err ) << " at " << file << "(" << line << "): " << call << '\n';
        std::cerr << ss.str() << std::endl;
        throw std::runtime_error( ss.str().c_str() );
    }
}

void glCheckErrors( const char* file, unsigned int line )
{
    GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
        std::stringstream ss;
        ss << "GL error " << getGLErrorString( err ) << " at " << file << "(" << line << ")";
        std::cerr << ss.str() << std::endl;
        throw std::runtime_error( ss.str().c_str() );
    }
}

void checkGLError()
{
    GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
        std::ostringstream oss;
        do
        {
            oss << "GL error: " << getGLErrorString( err ) << '\n';
            err = glGetError();
        } while( err != GL_NO_ERROR );

        throw std::runtime_error( oss.str().c_str() );
    }
}

} // namespace otk
