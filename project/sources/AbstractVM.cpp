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

/* ********************************* PARSING ********************************* */

void AbstractVM::parseCommand(std::string prompt) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::parseCommand(std::string prompt)" << std::endl;
	}

	// split
	std::vector<std::string> split = stringSplit(prompt, " ");

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
}

void AbstractVM::executeCommand(std::string cmd) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::executeCommand(std::string)" << std::endl;
	}
	(this->*(this->_commandMap[cmd]))(nullptr);
}

void AbstractVM::executeCommand(std::string cmd, std::string parameter) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::executeCommand(std::string cmd, std::string value)" << std::endl;
	}

	// test valid command
	if (cmd == "push" || cmd == "assert") {
		// test valid parameter
		IOperand *iOperand;
		const char *c_str = parameter.c_str();
		if (!std::strncmp(c_str, "int8(", 5)) {
			iOperand = const_cast<IOperand *>(createOperand(Int8, getIntegerParameter(&parameter[5])));
		} else if (!std::strncmp(c_str, "int16(", 6)) {
			iOperand = const_cast<IOperand *>(createOperand(Int16, getIntegerParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "int32(", 6)) {
			iOperand = const_cast<IOperand *>(createOperand(Int32, getIntegerParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "float(", 6)) {
			iOperand = const_cast<IOperand *>(createOperand(Float, getFloatParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "double(", 7)) {
			iOperand = const_cast<IOperand *>(createOperand(Double, getDoubleParameter(&parameter[7])));
		} else {
			throw AbstractVMException(__FUNCTION__, "Invalid parameter");
		}
		if (cmd == "push") {
			push(iOperand);
		} else {
			assert(iOperand);
		}
	} else {
		throw AbstractVMException("Invalid command for parameter");
	}
}

std::string AbstractVM::getIntegerParameter(std::string string) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::getIntegerParameter(std::string const string)" << std::endl;
	}
	char *p;
	strtol(string.c_str(), &p, 10);
	if (*p == ')' && std::count(string.begin(), string.end(), ')') == 1) {
		// pop back for remove last char ')'
		string.pop_back();
		if (isInteger(string)) {
			return string;
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
}

std::string AbstractVM::getFloatParameter(std::string string) {
	if (globalDebugFlag) {
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
			return string;
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
}

std::string AbstractVM::getDoubleParameter(std::string string) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::getDoubleParameter(std::string string)" << std::endl;
	}
	char *p;
	strtod(string.c_str(), &p);
	if (*p == ')' && std::count(string.begin(), string.end(), ')') == 1) {
		// pop back for remove last char ')'
		string.pop_back();
		if (isDouble(string)) {
			return string;
		} else {
			throw AbstractVMException("Bad length");
		}
	} else {
		throw AbstractVMException(__FUNCTION__, "Invalid parameter");
	}
}

/* ********************************* CREATORS ********************************* */

IOperand const *AbstractVM::createOperand(eOperandType type, std::string const &value) const {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createOperand(eOperandType type, std::string const &value)" << std::endl;
	}
	return dynamic_cast<IOperand const *>((this->*(this->_createPointerTab[type]))(value));
}

IOperand const *AbstractVM::createInt8(std::string const &value) const {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt8(std::string const &value)" << std::endl;
	}
	if (v > INT8_MAX || v < INT8_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<char>(Int8, static_cast<char>(v));
}

IOperand const *AbstractVM::createInt16(std::string const &value) const {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt16(std::string const &value)" << std::endl;
	}
	if (v > INT16_MAX || v < INT16_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<short>(Int16, static_cast<short>(stoi(value)));
}

IOperand const *AbstractVM::createInt32(std::string const &value) const {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt32(std::string const &value)" << std::endl;
	}
	if (v > INT32_MAX || v < INT32_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<int>(Int32, stoi(value));
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createFloat(std::string const &value)" << std::endl;
	}
	return new Operand<float>(Float, std::stof(value));
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createDouble(std::string const &value)" << std::endl;
	}
	return new Operand<double>(Double, std::stod(value));
}

/* ********************************* COMMANDS ********************************* */

void AbstractVM::push(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::push(IOperand *iOperand)" << std::endl;
	}
	this->_stack.push_back(iOperand);
}

void AbstractVM::pop(IOperand *iOperand) {
	//TODO 15 Feb 2018 11:21 think to free
	if (globalDebugFlag) {
		std::cout << "AbstractVM::pop(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() == 0) {
		throw AbstractVMException(__FUNCTION__, "Stack is empty");
	} else {
		delete this->_stack.back();
		this->_stack.pop_back();
	}
}

void AbstractVM::dump(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::dump(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::assert(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM : assert command" << std::endl;
	}
	if (_stack.size() == 0) {
		throw AbstractVMException(__FUNCTION__, "Stack is empty");
	}
	IOperand *lastOne = this->_stack.back();
	if (iOperand->getType() != lastOne->getType() || iOperand->toString() != lastOne->toString()) {
		throw AbstractVMException(__FUNCTION__, "Value not match with the last on the stack");
	} else if (globalDebugFlag) {
		std::cout << "Assert success" << std::endl;
	}
}

void AbstractVM::add(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::add(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::sub(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::sub(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::mul(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::mul(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::div(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::div(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::mod(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::mod(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::print(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::print(IOperand *iOperand)" << std::endl;
	}
}

void AbstractVM::exit(IOperand *iOperand) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::exit(IOperand *iOperand)" << std::endl;
	}
}

/* ********************************* COMMONS ********************************* */

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

std::vector<std::string> AbstractVM::stringSplit(const std::string &string, const char *c) {
	char *pch;
	std::vector<std::string> split;

	pch = strtok(const_cast<char *>(string.c_str()), c);
	while (pch != NULL) {
		split.push_back(pch);
		pch = strtok(NULL, c);
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

std::ostream &operator<<(std::ostream &o, IOperand const &rhs) {
	o << rhs.toString();
	return o;
}