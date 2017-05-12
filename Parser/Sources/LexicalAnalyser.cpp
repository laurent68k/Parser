//
//  LexicalAnalyser
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#include "LexicalAnalyser.h"

namespace Parser {

LexicalAnalyser::LexicalAnalyser() : m_keywords( new Keywords() )  {

}

/*LexicalAnalyser::LexicalAnalyser(int a) : m_keywords( new Keywords() )  {

}*/


LexicalAnalyser::~LexicalAnalyser(void)
{
	delete m_keywords;
}

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------
LexicalUnit* LexicalAnalyser::GetLexicalUnit(std::string textToAnalyse, unsigned int& indexToAnalyse) const
{
	std::string lexeme = LexicalAnalyser::GetLexeme(textToAnalyse, indexToAnalyse);

	return new LexicalUnit(this->m_keywords, lexeme, indexToAnalyse);
}
//	-----------------------------------------------------------------------------------------------------------------------------------------------------------				
/// Return the next Lexeme in the text stream input
std::string LexicalAnalyser::GetLexeme(std::string textToAnalyse, unsigned int& indexToAnalyse)
{
	std::string lexeme = std::string("");
	bool stop = false;

	unsigned int indice = indexToAnalyse;

	while (indice < textToAnalyse.length() && !stop)
	{
		char character = textToAnalyse[(int)indice];

		if (character == ' ' && !(lexeme.length() != 0 && lexeme[0] == '\"') )
		{
			if (lexeme.length() == 0)
			{
				lexeme = std::string(1, character);	
				indice++;
				indexToAnalyse++;
				break;
			}
			else
			{
				stop = true;
			}
		}
		else
		{
			//	If we started to evaluate a literal
			if (lexeme.length() != 0 && lexeme[0] == '\"'	)
			{
				//	Add the new char if there is only ONE ' in the string
				if( lexeme.find_first_of('\"') == lexeme.find_last_of('\"') )
				{
					lexeme += std::string(1, character);	
				}
				else
				{
					stop = true;
				}
			}
			//	We are analysing a string: may be a VARCONST or Number with 0x or 0b
			else if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z') || (character == '_') )
			{
				if (lexeme.length() == 0)
				{
					lexeme += std::string(1, character);	
				}
				else if (lexeme.length() == 1)
				{

					if ((lexeme[0] >= 'A' && lexeme[0] <= 'Z') || (lexeme[0] >= 'a' && lexeme[0] <= 'z') || (lexeme[0] == '_'))
					{
						lexeme += std::string(1, character);	
					}
						//	Accept a hexadecimal lexeme
					else if (lexeme[0] == '0' && character == 'x')
					{
						lexeme += std::string(1, character);	
					}
						//	Accept a binary lexeme
					else if (lexeme[0] == '0' && character == 'b')
					{
						lexeme += std::string(1, character);	
					}
					else
					{
						stop = true;
					}
				}
				else
				{
					lexeme += std::string(1, character);	
				}
			}					
			else if ((character >= '0' && character <= '9') || character == '.')
			{
				if (lexeme.length() == 0 && character != '.')
				{
					lexeme += std::string(1, character);	
				}
				else if (lexeme.length() == 1)
				{
					if (lexeme[0] >= '0' && lexeme[0] <= '9')
					{
						lexeme += std::string(1, character);	
					}
					else
					{
						stop = true;
					}
				}
				else
				{
					lexeme += std::string(1, character);	
				}
			}
			else if (	character == '+' || character == '-' || character == '*' || character == '/' ||
						character == '&' || character == '=' || character == '<' || character == '>' ||
						character == '!' || character == '%' || character == '^' || character == '|')
			{
				if (lexeme.length() == 0)
				{
					lexeme += std::string(1, character);	
				}
				else if (lexeme.length() == 1)
				{
					if (lexeme[0] == '!' || lexeme[0] == '=' || lexeme[0] == '<' || lexeme[0] == '>' )
					{
						lexeme += std::string(1, character);	
						indice++;
						stop = true;
					}
					else
					{
						stop = true;
					}
				}
				else
				{
					stop = true;
				}
			}
			else if( character == '(' || character == ')' )
			{
				if (lexeme.length() == 0)
				{
					lexeme = std::string(1, character);	
					stop = true;
					indice++;
				}
				else
				{
					//	may be a Func identifier was evaluated
					if (character == '('&& ((lexeme[0] >= 'A' && lexeme[0] <= 'Z') || (lexeme[0] >= 'a' && lexeme[0] <= 'z')) )
					{
						lexeme += std::string(1, character);	
						stop = true;
						indice++;
					}
					else
					{
						stop = true;
					}
				}
			}
			else if (character == '!' || character == '~' || character == ',')
			{
				if (lexeme.length() == 0)
				{
					lexeme = std::string(1, character);
					stop = true;
					indice++;
				}
				else
				{
					stop = true;
				}
			}
			else if (character == '\"') {
				if (lexeme.length() == 0) {
					lexeme += std::string(1, character);	
				}
				else if (lexeme.length() == 1 && lexeme[0] == '\"' ) {
					lexeme += std::string(1, character);	
				}
				else {
					stop = true;
				}
			}
			else if (character == '\r' || character == '\n') {

				if (lexeme.length() == 0)
				{
					lexeme = std::string(1, character);
					stop = true;
					indice++;
				}
				else
				{
					stop = true;
				}
			}
			else
			{
				lexeme = std::string(1, character);	
				stop = true;
				indice++;

			}

		}
		if (!stop)
		{
			indice++;
		}
	}
	indexToAnalyse = indice;

	return lexeme;
}
//	-----------------------------------------------------------------------------------------------------------------------------------------------------------

}

