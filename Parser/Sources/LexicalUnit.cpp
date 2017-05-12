//
//  LexicalAnalyser
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#include "Helper.h"

#include "LexicalUnit.h"

namespace Parser {

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Create a new instance of LexicalUnit regarding the lexeme in parameter
LexicalUnit::LexicalUnit(const Keywords* keywords, std::string lexemeText, unsigned int indice) : m_lexeme(lexemeText), m_type(LexicalError), m_indice(indice), m_keywords(keywords) {
	
	if (!m_lexeme.empty() ) {

		//	The order can be very important:
		m_type = (m_type == LexicalError && this->IsSeparator() ? SpaceSeparator : m_type);
		m_type = (m_type == LexicalError && this->IsParenthesisOpen() ? ParenthesisOpen : m_type);
		m_type = (m_type == LexicalError && this->IsParenthesisClose() ? ParenthesisClose : m_type);
		m_type = (m_type == LexicalError && this->IsNumber() ? Number : m_type);
		m_type = (m_type == LexicalError && this->IsPrefix() ? Unary : m_type);				
		m_type = (m_type == LexicalError && this->IsLogicalOperator() ? LogOp : m_type);
		m_type = (m_type == LexicalError && this->IsMathOperatorWeak() ? MathOpWeak : m_type);
		m_type = (m_type == LexicalError && this->IsMathOperatorStrong() ? MathOpStrong : m_type);
		m_type = (m_type == LexicalError && this->IsRelationalOperator() ? RelOp : m_type);
		m_type = (m_type == LexicalError && this->IsAssignOperator() ? AssignOp : m_type);
		m_type = (m_type == LexicalError && this->IsComma() ? Comma : m_type);
		m_type = (m_type == LexicalError && this->IsKeyword() ? Keyword : m_type);
		m_type = (m_type == LexicalError && this->IsIdentifier() ? Variable : m_type);
		m_type = (m_type == LexicalError && this->IsFunction() ? Function : m_type);				
		m_type = (m_type == LexicalError && this->IsLitteral() ? Litteral : m_type);
		m_type = (m_type == LexicalError && this->IsEndOfLine() ? EndOfLine : m_type);
	}
	else {

		m_type = EndOfText;
	}
}

LexicalUnit::~LexicalUnit(void) {
}

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------
/// Return true if the model applied to the current lexeme correspond to a Lexcial Unit separator
bool LexicalUnit::IsSeparator() {

	return ( Helper::Trim(m_lexeme).empty() );
}

/// Return true if the model applied to the current lexeme correspond to a Lexcial Unit parenthesis open
bool LexicalUnit::IsParenthesisOpen() {
	return (m_lexeme == "(");
}

bool LexicalUnit::IsParenthesisClose() {

	return (m_lexeme == ")");
}

bool LexicalUnit::IsComma() {

	return (m_lexeme == ",");
}

bool LexicalUnit::IsNumber() {			

	bool ret = false;

	if( m_lexeme.substr(0, 2) == "0x"  ) {

		/*unsigned int integer;
		ret = UInt32.TryParse(myString.Substring(2, m_lexeme), System.Globalization.NumberStyles.HexNumber, CultureInfo.InvariantCulture, out integer);*/		
		
		ret = true;
		try {
			std::stoi(m_lexeme, nullptr, 16);
		}
		catch( ... ) {
			ret = false;
		}
	}
	else if( m_lexeme.substr(0, 2) == "0b") {

		ret = true;				
		std::string subLexeme = Helper::Substring(2, m_lexeme);
		for( unsigned int index = 0; index < subLexeme.length(); index++ ) {
			char character = subLexeme[index];

			if( character != '0' && character != '1' ) {
				ret = false;
				break;
			}					
		}
	}
	else {
		ret = true;
		try {
			std::stod(m_lexeme);
		}
		catch( ... ) {
			ret = false;
		}
	}			
	return ret;			
}

bool LexicalUnit::IsPrefix() {

	return ( (!m_lexeme.empty()) && (m_lexeme == "!"  || m_lexeme == "~") );
}

bool LexicalUnit::IsIdentifier() {

	return ( (!m_lexeme.empty()) && ( (m_lexeme[0] >= 'A' && m_lexeme[0] <= 'Z') ||  (m_lexeme[0] >= 'a' && m_lexeme[0] <= 'z') || (m_lexeme[0] =='_') )
											&& m_lexeme[m_lexeme.length() - 1] != '(' ); 
}

//	Return true when a langage keyword is recognized
bool LexicalUnit::IsKeyword() {

	return this->m_keywords->find( m_lexeme );
	//return m_lexeme == "Null" || m_lexeme == "True" || m_lexeme == "False";
}

bool LexicalUnit::IsLitteral() {

	return (!m_lexeme.empty() && m_lexeme[0] == '\"' && m_lexeme[m_lexeme.length() - 1] == '\"');
}

bool LexicalUnit::IsLogicalOperator() {

	return (m_lexeme == "And" || m_lexeme == "Or");
}

bool LexicalUnit::IsMathOperatorWeak() {

	return (m_lexeme == "+" || m_lexeme == "-" || m_lexeme == "&" || m_lexeme == "|" || m_lexeme == "<<" || m_lexeme == ">>" || m_lexeme == "%" || m_lexeme == "^");
}

bool LexicalUnit::IsMathOperatorStrong() {

	return (m_lexeme == "*" || m_lexeme == "/" );
}

bool LexicalUnit::IsRelationalOperator() {

	return (m_lexeme == "<" || m_lexeme == ">" || m_lexeme == "<=" || m_lexeme == ">=" || m_lexeme == "==" || m_lexeme == "!=" || m_lexeme == "<>");
}

bool LexicalUnit::IsAssignOperator() {

	return (m_lexeme == "=");
}

bool LexicalUnit::IsFunction() {

	return ( (!m_lexeme.empty()) && ((m_lexeme[0] >= 'A' && m_lexeme[0] <= 'Z') || (m_lexeme[0] >= 'a' && m_lexeme[0] <= 'z')) && m_lexeme[m_lexeme.length() - 1] == '(' ); 
}

bool LexicalUnit::IsEndOfLine() {

	return (m_lexeme[0] == '\r' || m_lexeme[0] == '\n');
}

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------

/// Get the type of this lexical unit
LexicalUnit::What LexicalUnit::getType() const {
	return m_type;
}

/// Get the lexeme of this lexical unit
std::string LexicalUnit::getLexeme() const {
	return m_lexeme;
}

/// Get the position in the original stream of this lexical unit
unsigned int LexicalUnit::getPosition() const {
	return m_indice;
}

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------
//	-----------------------------------------------------------------------------------------------------------------------------------------------------------

std::string LexicalUnit::getTypeAsString(What type ) {
		
	std::string typeAsString = std::string("");

	switch( type ) {

	case	Number:
			typeAsString = "Number";
			break;

	case	Variable: 
			typeAsString = "Variable";
			break;

	case	Litteral:
			typeAsString = "Litteral";
			break;

	case	Keyword:
			typeAsString = "Keyword";
			break;

	case	Unary: 
			typeAsString = "Unary";
			break;

	case	LogOp:
			typeAsString = "LogOp";
			break;

	case	MathOpWeak:
			typeAsString = "MathOpWeak";
			break;

	case	MathOpStrong:
			typeAsString = "MathOpStrong";
			break;

	case	RelOp:
			typeAsString = "RelOp";
			break;

	case	AssignOp:
			typeAsString = "AssignOp";
			break;

	case	Function:
			typeAsString = "Function";
			break;

	case	SpaceSeparator:
			typeAsString = "SpaceSeparator";
			break;

	case	ParenthesisOpen:
			typeAsString = "ParenthesisOpen";
			break;

	case	ParenthesisClose:
			typeAsString = "ParenthesisClose";
			break;

	case	Comma:
			typeAsString = "Comma";
			break;

	case	EndOfText:
			typeAsString = "";
			break;

	case	EndOfLine:
			typeAsString = "EndOfLine";
			break;

	case	LexicalError:
			typeAsString = "LexicalError";
			break;

	}

	return typeAsString;
}

};
