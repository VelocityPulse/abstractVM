/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:18:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 15:18:25 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AbstractVM.hpp"

bool AbstractVM::_debugFlag = true;
AbstractVM *AbstractVM::_singleton = nullptr;

AbstractVM::AbstractVM() {
	this->_createPointerTab.push_back(&AbstractVM::createInt8);
	this->_createPointerTab.push_back(&AbstractVM::createInt16);
	this->_createPointerTab.push_back(&AbstractVM::createInt32);
	this->_createPointerTab.push_back(&AbstractVM::createFloat);
	this->_createPointerTab.push_back(&AbstractVM::createDouble);
	this->_commandMap["push"] = &AbstractVM::push;
	this->_commandMap["pop"] = &AbstractVM::pop;
	this->_commandMap["dump"] = &AbstractVM::dump;
	this->_commandMap["assert"] = &AbstractVM::assert;
	this->_commandMap["add"] = &AbstractVM::add;
	this->_commandMap["sub"] = &AbstractVM::sub;
	this->_commandMap["mul"] = &AbstractVM::mul;
	this->_commandMap["div"] = &AbstractVM::div;
	this->_commandMap["mod"] = &AbstractVM::mod;
	this->_commandMap["print"] = &AbstractVM::print;
	this->_commandMap["exit"] = &AbstractVM::exit;
}

/* *************** PARSING *************** */

void AbstractVM::parseCommand(std::string prompt) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::parseCommand(std::string prompt)" << std::endl;
	}

	// split
	std::vector<std::string> split = stringSplit(prompt, ' ');

	// size security
	if (split.size() < 1) {
		throw AbstractVMException("Invalid command");
	}

	// test existing command
	MapCommandIterator it = this->_commandMap.find(split[0]);
	if (it == this->_commandMap.end()) {
		throw AbstractVMException("Command not found");
	}

	// calling execute command
	if (split.size() == 1) {
		executeCommand(split[0]);
	} else if (split.size() == 2) {
		executeCommand(split[0], split[1]);
	} else {
		throw AbstractVMException("Invalid command");
	}

	//TODO 12 Feb 2018 04:29 make a system for parse "int8(n)" "int16(n)" "double(z)" etc...

}

void AbstractVM::executeCommand(std::string cmd) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::executeCommand(std::string)" << std::endl;
	}
}

void AbstractVM::executeCommand(std::string cmd, std::string parameter) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::executeCommand(std::string cmd, std::string value)" << std::endl;
	}

	// test valid parameter
	const char *c_str = parameter.c_str();
	if (!std::strncmp(c_str, "int8(", 5)) {
		std::cout << getIntegerParameter(&parameter[5]) << std::endl;
	} else if (!std::strncmp(c_str, "int16(", 6)) {
		std::cout << getIntegerParameter(&parameter[6]) << std::endl;
	} else if (!std::strncmp(c_str, "int32(", 6)) {
		std::cout << getIntegerParameter(&parameter[6]) << std::endl;
	} else if (!std::strncmp(c_str, "float(", 6)) {
		std::cout << getFloatParameter(&parameter[6]) << std::endl;
	} else if (!std::strncmp(c_str, "double(", 7)) {
		std::cout << getDoubleParameter(&parameter[7]) << std::endl;
	} else {
		throw AbstractVMException(__FUNCTION__,  "Invalid parameter");
	}
}

int AbstractVM::getIntegerParameter(std::string string) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::getIntegerParameter(std::string const string)" << std::endl;
	}
	char *p;
	strtol(string.c_str(), &p, 10);
	if (*p == ')' && std::count(string.begin(), string.end(), ')') == 1) {
		// pop back for remove last char ')'
		string.pop_back();
		if (isInteger(string)) {
			return std::stoi(string);
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
}

float AbstractVM::getFloatParameter(std::string string) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::getFloatParameter(std::string const string)" << std::endl;
	}
	char *p;
	strtof(string.c_str(), &p);
	if (std::count(string.begin(), string.end(), ')') != 1) {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
	if (*p == ')' || (p[0] == 'f' && p[1] == ')')) {
		// pop back for remove last char ')'
		string.pop_back();
		if (isFloat(string)) {
			return std::stof(string);
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
}

double AbstractVM::getDoubleParameter(std::string string) {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM::getDoubleParameter(std::string string)" << std::endl;
	}
	char *p;
	strtod(string.c_str(), &p);
	if (*p == ')' && std::count(string.begin(), string.end(), ')') == 1) {
		// pop back for remove last char ')'
		string.pop_back();
		if (isDouble(string)) {
			return std::stod(string);
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}

}


/* *************** CREATORS *************** */

IOperand const *AbstractVM::createOperand(eOperandType type, std::string const &value) const {
	return dynamic_cast<IOperand const *>((this->*(this->_createPointerTab[type]))(value));
}

IOperand const *AbstractVM::createInt8(std::string const &value) const {
	if (AbstractVM::_debugFlag) {
		std::cout << "create Int 8 : [" + value + "]" << std::endl;
	}
	//TODO 06 Feb 2018 02:52 check if throw is required when > than max int8 or < than min int8
	return new Operand<char>(Int8, static_cast<char>(stoi(value)));
}

IOperand const *AbstractVM::createInt16(std::string const &value) const {
	if (AbstractVM::_debugFlag) {
		std::cout << "create Int 16 : [" + value + "]" << std::endl;
	}
	return new Operand<short>(Int16, static_cast<short>(stoi(value)));
}

IOperand const *AbstractVM::createInt32(std::string const &value) const {
	if (AbstractVM::_debugFlag) {
		std::cout << "create Int 32 : [" + value + "]" << std::endl;
	}
	return new Operand<int>(Int32, stoi(value));
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	if (AbstractVM::_debugFlag) {
		std::cout << "create Float : [" + value + "]" << std::endl;
	}
	return new Operand<float>(Float, std::stof(value));
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	if (AbstractVM::_debugFlag) {
		std::cout << "create Double : [" + value + "]" << std::endl;
	}
	return new Operand<double>(Double, std::stod(value));
}

std::ostream &operator<<(std::ostream &o, IOperand const &rhs) {
	o << rhs.toString();
	return o;
}

/* *************** COMMANDS *************** */

void AbstractVM::push() {
//	throw AbstractVMException("push throw test");

	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : push command" << std::endl;
	}
}

void AbstractVM::pop() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : pop command" << std::endl;
	}
}

void AbstractVM::dump() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : dump command" << std::endl;
	}
}

void AbstractVM::assert() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : assert command" << std::endl;
	}
}

void AbstractVM::add() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : add command" << std::endl;
	}
}

void AbstractVM::sub() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : sub command" << std::endl;
	}
}

void AbstractVM::mul() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : mul command" << std::endl;
	}
}

void AbstractVM::div() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : div command" << std::endl;
	}
}

void AbstractVM::mod() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : mod command" << std::endl;
	}
}

void AbstractVM::print() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : print command" << std::endl;
	}
}

void AbstractVM::exit() {
	if (AbstractVM::_debugFlag) {
		std::cout << "AbstractVM : exit command" << std::endl;
	}
}

/* *************** COMMONS *************** */

AbstractVM::AbstractVM(AbstractVM const &copy) {
	*this = copy;
}

AbstractVM &AbstractVM::operator=(AbstractVM const &copy) {
	(void) copy;
	return *this;
}

AbstractVM *AbstractVM::getInstance() {
	if (!AbstractVM::_singleton)
		AbstractVM::_singleton = new AbstractVM();
	return AbstractVM::_singleton;
}

std::string AbstractVM::stringTrim(const std::string &str) {
	if (str.empty()) return str;
	std::string::size_type i;
	std::string::size_type j;
	i = 0;
	while (i < str.size() && isspace(str[i]))
		++i;
	if (i == str.size())
		return ""; // empty string
	j = str.size() - 1;
	while (isspace(str[j]))
		--j;
	return str.substr(i, j - i + 1);
}

std::vector<std::string> AbstractVM::stringSplit(const std::string &string, char c) {
	std::vector<std::string> split;
	char *pch;
	pch = strtok(const_cast<char *>(string.c_str()), &c);
	while (pch != NULL) {
		split.push_back(pch);
		pch = strtok(NULL, &c);
	}
	return split;
}

bool AbstractVM::isDouble(const std::string &string) {
	try {
		std::stod(string);
	}
	catch (std::exception) {
		return false;
	}
	return true;
}

bool AbstractVM::isInteger(const std::string &string) {
	try {
		std::stoi(string);
	}
	catch (std::exception) {
		return false;
	}
	return true;
}

bool AbstractVM::isFloat(const std::string &string) {
	try {
		std::stof(string);
	}
	catch (std::exception) {
		return false;
	}
	return true;
}

