//
//  Keywords
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#pragma once

#ifndef	__KEYWORDS__
#define	__KEYWORDS__	__KEYWORDS__

#include <list>
#include <algorithm>
#include <string>

namespace Parser {

	class Keywords {

	
		private:

			std::list<std::string>	m_keywords;

		public:

			Keywords();		
			virtual ~Keywords(void);

			bool find			(const std::string& element) const;
	};
};

#endif
