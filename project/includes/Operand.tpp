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
#include "OperandCreator.hpp"

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

	Operand(Operand const &copy) {
		(void)copy;
	}  // Canonical

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

	IOperand const *operator+(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		double lhsValue = this->_value;
		double rhsValue = std::stod(rhs.toString());

		switch (biggerType) {
			case Int8:
				flowCheck<char>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, lhsValue + rhsValue));
			case Int16:
				flowCheck<short>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, lhsValue + rhsValue));
			case Int32:
				flowCheck<int>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, lhsValue + rhsValue));
			case Float:
				flowCheck<float>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, lhsValue + rhsValue));
			case Double:
				flowCheck<double>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, lhsValue + rhsValue));
		}
		return nullptr;
	}

	IOperand const *operator-(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		double lhsValue = this->_value;
		double rhsValue = std::stod(rhs.toString());

		switch (biggerType) {
			case Int8:
				flowCheck<char>(lhsValue, rhsValue * -1);
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, lhsValue - rhsValue));
			case Int16:
				flowCheck<short>(lhsValue, rhsValue * -1);
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, lhsValue - rhsValue));
			case Int32:
				flowCheck<int>(lhsValue, rhsValue * -1);
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, lhsValue - rhsValue));
			case Float:
				flowCheck<float>(lhsValue, rhsValue * -1);
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, lhsValue - rhsValue));
			case Double:
				flowCheck<double>(lhsValue, rhsValue * -1);
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, lhsValue - rhsValue));
		}
		return nullptr;
	}

	IOperand const *operator*(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		double lhsValue = this->_value;
		double rhsValue = std::stod(rhs.toString());

		switch (biggerType) {
			case Int8:
				multFlowCheck<char>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, lhsValue * rhsValue));
			case Int16:
				multFlowCheck<short>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, lhsValue * rhsValue));
			case Int32:
				multFlowCheck<int>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, lhsValue * rhsValue));
			case Float:
				multFlowCheck<float>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, lhsValue * rhsValue));
			case Double:
				multFlowCheck<double>(lhsValue, rhsValue);
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, lhsValue * rhsValue));
		}
		return nullptr;
	}

	IOperand const *operator/(IOperand const &rhs) const override {
		eOperandType biggerType = (this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType());

		double lhsValue = this->_value;
		double rhsValue = std::stod(rhs.toString());
		if (lhsValue == 0 || rhsValue == 0) {
			throw AbstractVMException("Div by 0");
		}

		switch (biggerType) {
			case Int8:
				return reinterpret_cast<IOperand *>(new Operand<char>(biggerType, lhsValue / rhsValue));
			case Int16:
				return reinterpret_cast<IOperand *>(new Operand<short>(biggerType, lhsValue / rhsValue));
			case Int32:
				return reinterpret_cast<IOperand *>(new Operand<int>(biggerType, lhsValue / rhsValue));
			case Float:
				return reinterpret_cast<IOperand *>(new Operand<float>(biggerType, lhsValue / rhsValue));
			case Double:
				return reinterpret_cast<IOperand *>(new Operand<double>(biggerType, lhsValue / rhsValue));
		}
		return nullptr;
	}

	IOperand const *operator%(IOperand const &rhs) const override {
		if (this->getType() == Double || this->getType() == Float || rhs.getType() == Double ||
			rhs.getType() == Float) {
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
			case Float:
				break;
			case Double:
				break;
		}
		return nullptr;
	}

	std::string const &toString(void) const override {
		return *new std::string(std::to_string(this->_value));
	}

// max 2147483647
	template<typename G>
	void flowCheck(double a, double b) const {
		G sum = a + b;
		if ((a < 0) == (b < 0)) {
			if (a < 0 && sum > b) {
				throw AbstractVMException("Underflow");
			} else if (sum < b) {
				throw AbstractVMException("Overflow");
			}
		}
	}

	template<typename G>
	void multFlowCheck(double a, double b) const {
		G max = std::numeric_limits<G>::max();
		G abs_a = (a < 0 ? a * -1 : a);
		G abs_b = (b < 0 ? b * -1 : b);
		if (abs_a > max / abs_b) {
			if ((a < 0) && (b < 0)) {
				throw AbstractVMException("Overflow");
			} else if ((a > 0) && (b > 0)) {
				throw AbstractVMException("Overflow");
			} else {
				throw AbstractVMException("Underflow");
			}
		}
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