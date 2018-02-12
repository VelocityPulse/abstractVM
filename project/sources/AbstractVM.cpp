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

#include <iostream>
#include "../includes/AbstractVM.hpp"

bool AbstractVM::debugFlag = true;
AbstractVM *AbstractVM = nullptr;

AbstractVM::AbstractVM() {
	this->createPointerTab.push_back(&AbstractVM::createInt8);
	this->createPointerTab.push_back(&AbstractVM::createInt16);
	this->createPointerTab.push_back(&AbstractVM::createInt32);
	this->createPointerTab.push_back(&AbstractVM::createFloat);
	this->createPointerTab.push_back(&AbstractVM::createDouble);
	this->commandMap["push"] = &AbstractVM::push;
	this->commandMap["pop"] = &AbstractVM::pop;
	this->commandMap["dump"] = &AbstractVM::dump;
	this->commandMap["assert"] = &AbstractVM::assert;
	this->commandMap["add"] = &AbstractVM::add;
	this->commandMap["sub"] = &AbstractVM::sub;
	this->commandMap["mul"] = &AbstractVM::mul;
	this->commandMap["div"] = &AbstractVM::div;
	this->commandMap["mod"] = &AbstractVM::mod;
	this->commandMap["print"] = &AbstractVM::print;
	this->commandMap["exit"] = &AbstractVM::exit;
}

/* *************** PARSING *************** */

void AbstractVM::parseCommand(std::string prompt) {
	std::map<std::string, TypeCommandFunction>::iterator it = this->commandMap.find(prompt);

	(this->*(this->commandMap[prompt]))();

//	if (this->commandMap.count(prompt)) {
//		std::cout << "found" << std::endl;
//	} else {
//		std::cout << "error : [" + prompt + "]" << std::endl;
//	}
//
//	if (it != this->commandMap.end()) {
//		(this->*(it)->second)();
//	} else {
//		std::cout << "error : [" + prompt + "]" << std::endl;
//	}
}

/* *************** CREATORS *************** */

IOperand const *AbstractVM::createOperand(eOperandType type, std::string const &value) const {
	return dynamic_cast<IOperand const *>((this->*(this->createPointerTab[type]))(value));
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
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : push command" << std::endl;
	}
}

void AbstractVM::pop() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : pop command" << std::endl;
	}
}

void AbstractVM::dump() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : dump command" << std::endl;
	}
}

void AbstractVM::assert() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : assert command" << std::endl;
	}
}

void AbstractVM::add() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : add command" << std::endl;
	}
}

void AbstractVM::sub() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : sub command" << std::endl;
	}
}

void AbstractVM::mul() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : mul command" << std::endl;
	}
}

void AbstractVM::div() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : div command" << std::endl;
	}
}

void AbstractVM::mod() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : mod command" << std::endl;
	}
}

void AbstractVM::print() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : print command" << std::endl;
	}
}

void AbstractVM::exit() {
	if (AbstractVM::debugFlag) {
		std::cout << "AbstractVM : exit command" << std::endl;
	}
}

/* *************** COMMONS *************** */

AbstractVM::AbstractVM(AbstractVM const &copy) {
	*this = copy;
}

AbstractVM &AbstractVM::operator=(AbstractVM const &copy) {
	return *this;
}

AbstractVM *AbstractVM::getInstance() {
	if (!AbstractVM::singleton)
		AbstractVM::singleton = new AbstractVM();
	return AbstractVM::singleton;
}

std::string AbstractVM::stringTrim(std::string &str) {
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
