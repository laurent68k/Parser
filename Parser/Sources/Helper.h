//
//  Helper
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#pragma once

#ifndef	__HELPER__
#define	__HELPER__	__HELPER__

#include <string>

namespace Parser {

class Helper {

	public:

		Helper();
		virtual ~Helper();

		static std::string Trim( const std::string& src );
		static std::string Substring( unsigned int offset, const std::string& src );
};

}

#endif
