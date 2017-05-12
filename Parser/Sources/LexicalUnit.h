//
//  LexicalAnalyser
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#pragma once

#ifndef	__LEXICALUNIT__
#define	__LEXICALUNIT__	__LEXICALUNIT__

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <list>
#include <iostream>     // std::cout
#include <algorithm>    // std::find
#include <vector>       // std::vector

#include "keywords.h"

namespace Parser {

class LexicalUnit {

	public:

		/// Definition of Lexical Unit
		typedef enum {	Number = 1, 
						Variable, 
						Litteral, 
						Keyword, 
						Unary, 
						LogOp, 
						MathOpWeak, 
						MathOpStrong, 
						RelOp, 
						AssignOp,
						Function, 
						SpaceSeparator, 
						ParenthesisOpen, 
						ParenthesisClose, 
						Comma, 
						EndOfText, 
						EndOfLine,
						LexicalError } What;

	protected:

		const Keywords*			m_keywords;

		std::string				m_lexeme;
		What					m_type; 
		unsigned int			m_indice; 

		virtual bool			IsSeparator();
		virtual bool			IsParenthesisOpen();
		virtual bool			IsParenthesisClose();
		virtual bool			IsComma();
		virtual bool			IsNumber();
		virtual bool			IsPrefix();
		virtual bool			IsIdentifier();
		virtual bool			IsKeyword();
		virtual bool			IsLitteral();
		virtual bool			IsLogicalOperator();
		virtual bool			IsMathOperatorWeak();
		virtual bool			IsMathOperatorStrong();
		virtual bool			IsRelationalOperator();
		virtual bool			IsFunction();
		virtual bool			IsAssignOperator();
		virtual bool			IsEndOfLine();

	public:

		//	Constructors/Destructors
		LexicalUnit				(const Keywords* keywords, std::string lexemeText, unsigned int indice);
		virtual ~LexicalUnit	();

		virtual What			getType() const;
		virtual std::string		getLexeme() const;
		virtual	unsigned int	getPosition() const;

		static std::string		getTypeAsString(What type );
};
};

#endif
