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
	if (globalDebugFlagNameFunction) {
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
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::executeCommand(std::string)" << std::endl;
	}
	(this->*(this->_commandMap[cmd]))(nullptr);
}

void AbstractVM::executeCommand(std::string cmd, std::string parameter) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::executeCommand(std::string cmd, std::string value)" << std::endl;
	}

	// test valid command
	if (cmd == "push" || cmd == "assert") {
		// test valid parameter
		IOperand *iOperand;
		const char *c_str = parameter.c_str();
		if (!std::strncmp(c_str, "int8(", 5)) {
			iOperand = const_cast<IOperand *>(CreateOperand::createOperand(Int8, getIntegerParameter(&parameter[5])));
		} else if (!std::strncmp(c_str, "int16(", 6)) {
			iOperand = const_cast<IOperand *>(CreateOperand::createOperand(Int16, getIntegerParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "int32(", 6)) {
			iOperand = const_cast<IOperand *>(CreateOperand::createOperand(Int32, getIntegerParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "float(", 6)) {
			iOperand = const_cast<IOperand *>(CreateOperand::createOperand(Float, getFloatParameter(&parameter[6])));
		} else if (!std::strncmp(c_str, "double(", 7)) {
			iOperand = const_cast<IOperand *>(CreateOperand::createOperand(Double, getDoubleParameter(&parameter[7])));
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
	if (globalDebugFlagNameFunction) {
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
	if (globalDebugFlagNameFunction) {
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
	if (globalDebugFlagNameFunction) {
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

/* ********************************* COMMANDS ********************************* */

void AbstractVM::push(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::push(IOperand *iOperand)" << std::endl;
	}
	this->_stack.push_back(iOperand);
}

void AbstractVM::pop(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
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
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::dump(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() == 0) {
		std::cout << "Stack is empty" << std::endl;
		return ;
	}
	std::vector<IOperand *>::reverse_iterator it = this->_stack.rbegin();
	while (it != this->_stack.rend()) {
		std::cout << Operand<>::stringOfType((*it)->getType()) + "(" + (*it)->toString() + ")" << std::endl;
		it++;
	}
}

void AbstractVM::assert(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM : assert command" << std::endl;
	}
	if (_stack.size() == 0) {
		throw AbstractVMException(__FUNCTION__, "Stack is empty");
	}
	IOperand *lastOne = this->_stack.back();
	if (iOperand->getType() != lastOne->getType() || iOperand->toString() != lastOne->toString()) {
		throw AbstractVMException(__FUNCTION__, "Value not match with the last on the stack");
	} else if (globalDebugFlagInfoMessage) {
		std::cout << "Assert success" << std::endl;
	}
}

void AbstractVM::add(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::add(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() < 2) {
		throw AbstractVMException(__FUNCTION__, "Stack size is under 2");
	}
	IOperand *iOperand1 = this->_stack.back();
	IOperand *iOperand2 = this->_stack.at(this->_stack.size() - 2);
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(const_cast<IOperand *>(*iOperand1 + *iOperand2));
	delete iOperand1;
	delete iOperand2;
}

void AbstractVM::sub(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::sub(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() < 2) {
		throw AbstractVMException(__FUNCTION__, "Stack size is under 2");
	}
	IOperand *iOperand1 = this->_stack.back();
	IOperand *iOperand2 = this->_stack.at(this->_stack.size() - 2);
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(const_cast<IOperand *>(*iOperand1 - *iOperand2));
	delete iOperand1;
	delete iOperand2;
}

void AbstractVM::mul(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::mul(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() < 2) {
		throw AbstractVMException(__FUNCTION__, "Stack size is under 2");
	}
	IOperand *iOperand1 = this->_stack.back();
	IOperand *iOperand2 = this->_stack.at(this->_stack.size() - 2);
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(const_cast<IOperand *>(*iOperand1 * *iOperand2));
	delete iOperand1;
	delete iOperand2;
}

void AbstractVM::div(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::div(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() < 2) {
		throw AbstractVMException(__FUNCTION__, "Stack size is under 2");
	}
	IOperand *iOperand1 = this->_stack.back();
	IOperand *iOperand2 = this->_stack.at(this->_stack.size() - 2);
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(const_cast<IOperand *>(*iOperand1 / *iOperand2));
	delete iOperand1;
	delete iOperand2;
}

void AbstractVM::mod(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::mod(IOperand *iOperand)" << std::endl;
	}
	if (this->_stack.size() < 2) {
		throw AbstractVMException(__FUNCTION__, "Stack size is under 2");
	}
	IOperand *iOperand1 = this->_stack.back();
	IOperand *iOperand2 = this->_stack.at(this->_stack.size() - 2);
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(const_cast<IOperand *>(*iOperand1 % *iOperand2));
	delete iOperand1;
	delete iOperand2;
}

void AbstractVM::print(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::print(IOperand *iOperand)" << std::endl;
 	}
	if (this->_stack.size() == 0) {
		throw AbstractVMException(__FUNCTION__, "Stack is empty");
	} else if (this->_stack.back()->getType() != Int8) {
		throw AbstractVMException(__FUNCTION__, "Last value on the stack is not Int8");
	}
	char c = static_cast<char>(std::stoi(this->_stack.back()->toString()));
	std::cout << c << std::endl;
}

void AbstractVM::exit(IOperand *iOperand) {
	if (globalDebugFlagNameFunction) {
		std::cout << "AbstractVM::exit(IOperand *iOperand)" << std::endl;
	}
	std::exit(0);
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