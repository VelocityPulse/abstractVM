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
	std::vector<std::string> split = stringSplit(prompt, ' ');
//	if (split.size() == 2 && !isDouble(split[1])) {
//		throw AbstractVMException("Invalid command argument");
//	} else {
//		std::cout << "number : " + split[1] << std::endl;
//	}
	if (split.size() == 1) {
		std::map<std::string, TypeCommandFunction>::iterator it = this->_commandMap.find(prompt);
		if (it != this->_commandMap.end()) {
			(this->*(it)->second)();
		} else {
			throw AbstractVMException("Command not found");
		}
	} else if (split.size() == 2) {
		push();
	} else {
		throw AbstractVMException("Invalid command");
	}
}

/* *************** CREATORS *************** */

IOperand const *AbstractVM::createOperand(eOperandType type, std::string const &value) const {
	return dynamic_cast<IOperand const *>((this->*(this->_createPointerTab[type]))(value));
}

IOperand const *AbstractVM::createInt8(std::string const &value) const {
	std::cout << "create Int 8 : [" + value + "]" << std::endl;
	//TODO 06 Feb 2018 02:52 check if throw is required when > than max int8 or < than min int8
	return new Operand<char>(Int8, static_cast<char>(stoi(value)));
}

IOperand const *AbstractVM::createInt16(std::string const &value) const {
	std::cout << "create Int 16 : [" + value + "]" << std::endl;
	return new Operand<short>(Int16, static_cast<short>(stoi(value)));
}

IOperand const *AbstractVM::createInt32(std::string const &value) const {
	std::cout << "create Int 32 : [" + value + "]" << std::endl;
	return new Operand<int>(Int32, stoi(value));
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	std::cout << "create Float : [" + value + "]" << std::endl;
	return new Operand<float>(Float, std::stof(value));
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	std::cout << "create Double : [" + value + "]" << std::endl;
	return new Operand<double>(Double, std::stod(value));
}

std::ostream &operator<<(std::ostream &o, IOperand const &rhs) {
	o << rhs.toString();
	return o;
}

/* *************** COMMANDS *************** */

void AbstractVM::push() {
	throw AbstractVMException("test to remove");

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
	char * pch;
	pch = strtok (const_cast<char *>(string.c_str()), &c);
	while (pch != NULL) {
		split.push_back(pch);
		pch = strtok (NULL, &c);
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
