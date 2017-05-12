//
//  LexicalAnalyser
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#pragma once

#ifndef	__LEXICAL_ANALYSER__
#define	__LEXICAL_ANALYSER__	__LEXICAL_ANALYSER__

#include "keywords.h"
#include "LexicalUnit.h"

#include <string>

namespace Parser {

class LexicalAnalyser
{
	private :

		const Keywords*			m_keywords;

	protected:

		static std::string		GetLexeme(std::string textToAnalyse, unsigned int& indexToAnalyse) ;

	public:

		LexicalAnalyser			();
		//LexicalAnalyser			(int);
		virtual ~LexicalAnalyser();

		LexicalUnit*			GetLexicalUnit	(std::string textToAnalyse, unsigned int& indexToAnalyse) const;
};

}

#endif

