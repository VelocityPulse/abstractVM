/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:04:04 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/06 14:04:04 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP

#include "IOperand.hpp"
#include "AbstractVMException.hpp"
#include "CreateOperand.hpp"

extern bool globalDebugFlagNameFunction;
extern bool globalDebugFlagInfoMessage;

template<typename T = int>
class Operand : public IOperand {

private:
	Operand() {} // Canonical
	eOperandType _type;
	T _value;

public:
	Operand<T>(eOperandType type, T value) : _type(type), _value(value) {
		if (globalDebugFlagInfoMessage) {
			std::cout << "Operand::Operand<T>(eOperandType " << this->_type << ", T " << toString() << ")" << std::endl;
		}
	}

	Operand(Operand const &copy) {}  // Canonical

	~Operand() {} //Canonical

	Operand &operator=(Operand const &copy) { // Canonical
		if (this != &copy) {
			this->_type = copy._type;
			this->_value = copy._value;
			//TODO 06 Feb 2018 01:31 make this
		}
		return *this;
	}

	int getPrecision(void) const override {
		return this->_type;
	}

	eOperandType getType(void) const override {
		return this->_type;
	}

	//TODO 26 Feb 2018 02:48 add the overflow and underflow security

	IOperand const *operator+(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, this->_value + std::stod(rhs.toString())));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, this->_value + std::stod(rhs.toString())));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, this->_value + std::stod(rhs.toString())));
			case Float:
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, this->_value + std::stod(rhs.toString())));
			case Double:
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, this->_value + std::stod(rhs.toString())));
		}
		return nullptr;
	}

	IOperand const *operator-(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, this->_value - std::stod(rhs.toString())));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, this->_value - std::stod(rhs.toString())));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, this->_value - std::stod(rhs.toString())));
			case Float:
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, this->_value - std::stod(rhs.toString())));
			case Double:
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, this->_value - std::stod(rhs.toString())));
		}
		return nullptr;
	}

	IOperand const *operator*(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, this->_value * std::stod(rhs.toString())));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, this->_value * std::stod(rhs.toString())));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, this->_value * std::stod(rhs.toString())));
			case Float:
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, this->_value * std::stod(rhs.toString())));
			case Double:
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, this->_value * std::stod(rhs.toString())));
		}
		return nullptr;
	}

	IOperand const *operator/(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, this->_value / std::stod(rhs.toString())));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, this->_value / std::stod(rhs.toString())));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, this->_value / std::stod(rhs.toString())));
			case Float:
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, this->_value / std::stod(rhs.toString())));
			case Double:
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, this->_value / std::stod(rhs.toString())));
		}
		return nullptr;
	}

	IOperand const *operator%(IOperand const &rhs) const override {
		if (this->getType() == Double || this->getType() == Float || rhs.getType() == Double || rhs.getType() == Float) {
			throw AbstractVMException("Modulo with floating number");
		}
		if (std::stoi(rhs.toString()) == 0) {
			throw AbstractVMException("Modulo by 0");
		}
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());
		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, static_cast<int>(this->_value) % std::stoi(rhs.toString())));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, static_cast<int>(this->_value) % std::stoi(rhs.toString())));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, static_cast<int>(this->_value) % std::stoi(rhs.toString())));
			case Float:break;
			case Double:break;
		}
		return nullptr;
	}

	std::string const &toString(void) const override {
		return *new std::string(std::to_string(this->_value));
	}

	static std::string stringOfType(eOperandType type) {
		switch (type) {
			case Int8 :
				return "int8";
			case Int16:
				return "int16";
			case Int32:
				return "int32";
			case Float:
				return "float";
			case Double:
				return "double";
		}
	}
};

#endif //ABSTRACTVM_OPERAND_HPP