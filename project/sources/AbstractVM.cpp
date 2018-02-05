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

AbstractVM::AbstractVM() {

//	createPointerTab.push_back(AbstractVM::createInt8);
	createPointerTab.push_back(&AbstractVM::createInt32);


	lol.push_back(43.f);

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
//	IOperand const *(*pFunction[])(const std::string &value) = {
//			&AbstractVM::createInt8,
//			&createInt16,
//			&createInt32,
//			&createFloat,
//			&createDouble };
//
//	return pFunction[type](value);
	return nullptr;
}

IOperand const *AbstractVM::createInt8(std::string const &value) const {
	return nullptr;
}

IOperand const *AbstractVM::createInt16(std::string const &value) const {
	return nullptr;
}

IOperand const *AbstractVM::createInt32(std::string const &value) const {
	return nullptr;
}

IOperand const *AbstractVM::createFloat(std::string const &value) const {
	return nullptr;
}

IOperand const *AbstractVM::createDouble(std::string const &value) const {
	return nullptr;
}
