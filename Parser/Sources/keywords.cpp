//
//  Keywords
//  Parser
//
//  Created by Laurent on 12/05/2017.
//  Copyright © 2017 Laurent68k. All rights reserved.
//

#include <iostream>

#include "Keywords.h"

namespace Parser {

Keywords::Keywords() {

	this->m_keywords.push_front("Null");
	this->m_keywords.push_front("True");
	this->m_keywords.push_front("False");

	this->m_keywords.push_front("FOR");
	this->m_keywords.push_front("TO");
	this->m_keywords.push_front("NEXT");
	this->m_keywords.push_front("STEP");

	this->m_keywords.push_front("PRINT");

	this->m_keywords.push_front("IF");
	this->m_keywords.push_front("THEN");
	this->m_keywords.push_front("ELSE");
	this->m_keywords.push_front("ENDIF");
}


Keywords::~Keywords(void) {

	this->m_keywords.clear();
}

//	-----------------------------------------------------------------------------------------------------------------------------------------------------------

bool Keywords::find(const std::string& element) const {

	std::string aa(element);

	std::cout << m_keywords.size();

	bool found = (std::find(this->m_keywords.begin(), this->m_keywords.end(), aa) != this->m_keywords.end() );
	//bool found = (std::find( std::begin(keywords), std::end(keywords), aa) !=  std::end(keywords) );

	return found;
}

};
