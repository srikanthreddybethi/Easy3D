/*
*	Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
*	https://3d.bk.tudelft.nl/liangliang/
*
*	This file is part of Easy3D: software for processing and rendering
*   meshes and point clouds.
*
*	Easy3D is free software; you can redistribute it and/or modify
*	it under the terms of the GNU General Public License Version 3
*	as published by the Free Software Foundation.
*
*	Easy3D is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include <easy3d/opengl_error.h>

#include <iostream>

#include <3rd_party/glew/include/GL/glew.h>


namespace easy3d {

	// Convert an OpenGL error code into a descriptive string.
	inline const char* gl_error_string(GLenum code) {
		switch (code)
		{
		case GL_NO_ERROR:			return "No error";
		case GL_INVALID_ENUM:		return "Invalid enum";
		case GL_INVALID_VALUE:		return "Invalid value";
		case GL_INVALID_OPERATION:	return "Invalid operation";
		case GL_OUT_OF_MEMORY:		return "Out of memory";
		case GL_STACK_OVERFLOW:		return "Stack overflow";
		case GL_STACK_UNDERFLOW:	return "Stack underflow";
		case GL_TABLE_TOO_LARGE:	return "Table too large";
		case GL_INVALID_FRAMEBUFFER_OPERATION_EXT:	return "Invalid framebuffer operation";
		}
		return "Unknown error";
	}


	bool check_gl_error(const std::string& file, int line) {
		GLenum error_code = glGetError();
		if (error_code != GL_NO_ERROR) {
			const char* str = gl_error_string(error_code);
			if (str) {
				std::cerr << "GL error in file \'" << file << "\' @ line " << line << ": " << str << std::endl;
				return false;
			}
		}
		return true;
	}

	bool gl_error(std::string& log) {
		GLenum error_code = glGetError();
		if (error_code != GL_NO_ERROR) {
			const char* str = gl_error_string(error_code);
			if (str)
				log = std::string(str);
			return true;
		}
		else
			return false;
	}


	bool check_frame_buffer_error(const std::string& file, int line) {
		std::string msg;
		if (frame_buffer_error(msg) && !msg.empty()) {
			std::cerr << "framebuffer error in file \'" << file << "\' @ line " << line << ": " << msg << std::endl;
			return false;
		}
		return true;
	}


    bool frame_buffer_error(std::string& log)
	{
		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch (Status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			return true;
			break;
		case GL_FRAMEBUFFER_UNDEFINED:
            log = "GL_FRAMEBUFFER_UNDEFINED";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            log = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            log = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            log = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            log = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
            log = "GL_FRAMEBUFFER_UNSUPPORTED";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            log = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            log = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
			break;
		default:
            log = "unknown error";
		}

		return false;
	}


}
