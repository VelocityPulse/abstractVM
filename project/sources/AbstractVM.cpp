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

AbstractVM::AbstractVM() {
	createPointerTab.push_back(&AbstractVM::createInt8);
	createPointerTab.push_back(&AbstractVM::createInt16);
	createPointerTab.push_back(&AbstractVM::createInt32);
	createPointerTab.push_back(&AbstractVM::createFloat);
	createPointerTab.push_back(&AbstractVM::createDouble);
}

AbstractVM::AbstractVM(AbstractVM const &copy) {
	*this = copy;
}

AbstractVM::~AbstractVM() {

}

AbstractVM &AbstractVM::operator=(AbstractVM const &copy) {
	if (this != &copy) {
		// copy
		//TODO 05 Feb 2018 04:49 make this
	}
	return *this;
}

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
	std::cout << "create Int 32 : [" + value + "]"  << std::endl;
	return new Operand<int>(Int32, stoi(value));
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	std::cout << "create Float : [" + value + "]"  << std::endl;
	return new Operand<float>(Float, std::stof(value));
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	std::cout << "create Double : [" + value + "]"  << std::endl;
	return new Operand<double>(Double, std::stod(value));
}

std::ostream &operator<<(std::ostream &o, IOperand const &rhs) {
	o << rhs.toString();
	return o;
}