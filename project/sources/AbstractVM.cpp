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
	createOperand(Int16, "43");
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
	return dynamic_cast<>((this->*(this->createPointerTab[type]))(value));
}

IOperand const *AbstractVM::createInt8(std::string const &value) const {
	std::cout << "create Int 8 : [" + value + "]" << std::endl;
	return nullptr;
}

IOperand const *AbstractVM::createInt16(std::string const &value) const {
	std::cout << "create Int 16 : [" + value + "]" << std::endl;
	return nullptr;
}

IOperand const *AbstractVM::createInt32(std::string const &value) const {
	std::cout << "create Int 32 : [" + value + "]"  << std::endl;
	return nullptr;
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	std::cout << "create Float : [" + value + "]"  << std::endl;
	return nullptr;
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	std::cout << "create Double : [" + value + "]"  << std::endl;
	return nullptr;
}
