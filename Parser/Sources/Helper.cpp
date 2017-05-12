//
//  Helper
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#include "Helper.h"

namespace Parser {

Helper::Helper(void) {

}

Helper::~Helper(void) {
}

std::string Helper::Trim( const std::string& src ) {

	size_t first = src.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return std::string("");
	}
	size_t last = src.find_last_not_of(' ');
	return src.substr(first, (last - first + 1));
}	

std::string Helper::Substring( unsigned int offset, const std::string& src ) {

	return src.substr(2, src.length() - 2 );
}

}
