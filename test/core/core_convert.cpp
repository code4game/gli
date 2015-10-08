//////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/core_convert.cpp
/// @date 2015-10-05 / 2015-10-05
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/sampler2d.hpp>

namespace texel
{
	int test()
	{
		int Error = 0;

		{
			gli::texture2D Texture(gli::FORMAT_RGBA8_UINT, gli::texture2D::dim_type(1), 1);
			detail::convert<glm::u8, glm::u8, gli::defaultp, gli::tvec4, false, false>::write(Texture, gli::texture2D::dim_type(0), 0, gli::u8vec4(255, 127, 0, 255));
			glm::u8vec4 Texel = detail::convert<glm::u8, glm::u8, gli::defaultp, gli::tvec4, false, false>::fetch(Texture, gli::texture2D::dim_type(0), 0);

			Error += Texel == gli::u8vec4(255, 127, 0, 255) ? 0 : 1;
		}

		{
			gli::texture2D Texture(gli::FORMAT_RGBA8_UNORM, gli::texture2D::dim_type(1), 1);
			detail::convert<float, glm::u8, gli::defaultp, gli::tvec4, true, false>::write(Texture, gli::texture2D::dim_type(0), 0, gli::vec4(1.0f, 0.5f, 0.0f, 1.0f));
			glm::vec4 Texel = detail::convert<float, glm::u8, gli::defaultp, gli::tvec4, true, false>::fetch(Texture, gli::texture2D::dim_type(0), 0);

			Error += glm::all(glm::epsilonEqual(Texel, gli::vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.01f)) ? 0 : 1;
		}

		{
			gli::texture2D Texture(gli::FORMAT_RGBA8_SRGB, gli::texture2D::dim_type(1), 1);
			detail::convert<float, glm::u8, gli::defaultp, gli::tvec4, true, true>::write(Texture, gli::texture2D::dim_type(0), 0, gli::vec4(1.0f, 0.5f, 0.0f, 1.0f));
			glm::vec4 Texel = detail::convert<float, glm::u8, gli::defaultp, gli::tvec4, true, true>::fetch(Texture, gli::texture2D::dim_type(0), 0);

			Error += glm::all(glm::epsilonEqual(Texel, gli::vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.01f)) ? 0 : 1;
		}

		return Error;
	}
}//namespace texel

int main()
{
	int Error = 0;

	Error += texel::test();

	return Error;
}

