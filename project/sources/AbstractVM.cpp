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

AbstractVM::AbstractVM() {
	this->createPointerTab.push_back(&AbstractVM::createInt8);
	this->createPointerTab.push_back(&AbstractVM::createInt16);
	this->createPointerTab.push_back(&AbstractVM::createInt32);
	this->createPointerTab.push_back(&AbstractVM::createFloat);
	this->createPointerTab.push_back(&AbstractVM::createDouble);
    this->commandMap["push"] = &AbstractVM::push;
	this->commandMap["exit"] = &AbstractVM::push;

}


IOperand const *AbstractVM::createOperand(eOperandType type, std::string const &value) const {
	return dynamic_cast<IOperand const *>((this->*(this->createPointerTab[type]))(value));
}

/* *************** COMMANDS *************** */

// todo finish to work the comments

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
        std::cout << "AbstractVM : eixt command" << std::endl;
    }
}

/* *************** CREATORS *************** */

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

/* *************** COPY *************** */

AbstractVM::AbstractVM(AbstractVM const &copy) {
    *this = copy;
}

AbstractVM &AbstractVM::operator=(AbstractVM const &copy) {
    if (this != &copy) {
        // copy
        //TODO 05 Feb 2018 04:49 make this
    }
    return *this;
}
