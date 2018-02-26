/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateOperand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:34:04 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/26 11:34:04 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CreateOperand.hpp"
#include "../includes/AbstractVM.hpp"

CreateOperand::VectorOperand CreateOperand::_createPointerTab({
		&CreateOperand::createInt8,
		&CreateOperand::createInt16,
		&CreateOperand::createInt32,
		&CreateOperand::createFloat,
		&CreateOperand::createDouble });

/* ********************************* CREATORS ********************************* */

IOperand const *CreateOperand::createOperand(eOperandType type, std::string const &value) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createOperand(eOperandType type, std::string const &value)" << std::endl;
	}
	return dynamic_cast<IOperand const *>((*(CreateOperand::_createPointerTab[type]))(value));
}

IOperand const *CreateOperand::createInt8(std::string const &value) {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt8(std::string const &value)" << std::endl;
	}
	if (v > INT8_MAX || v < INT8_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<char>(Int8, static_cast<char>(v));
}

IOperand const *CreateOperand::createInt16(std::string const &value) {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt16(std::string const &value)" << std::endl;
	}
	if (v > INT16_MAX || v < INT16_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<short>(Int16, static_cast<short>(stoi(value)));
}

IOperand const *CreateOperand::createInt32(std::string const &value) {
	double v = stoi(value);
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createInt32(std::string const &value)" << std::endl;
	}
	if (v > INT32_MAX || v < INT32_MIN) {
		throw AbstractVMException(__FUNCTION__, "Out of range");
	}
	return new Operand<int>(Int32, stoi(value));
}

IOperand const *CreateOperand::createFloat(std::string const &value) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createFloat(std::string const &value)" << std::endl;
	}
	return new Operand<float>(Float, std::stof(value));
}

IOperand const *CreateOperand::createDouble(std::string const &value) {
	if (globalDebugFlag) {
		std::cout << "AbstractVM::createDouble(std::string const &value)" << std::endl;
	}
	return new Operand<double>(Double, std::stod(value));
}

/* ********************************* CONSTRUCTORS ********************************* */

CreateOperand::CreateOperand() {
}

CreateOperand::CreateOperand(CreateOperand const &copy) {
	*this = copy;
}

CreateOperand::~CreateOperand() {

}

CreateOperand &CreateOperand::operator=(CreateOperand const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}