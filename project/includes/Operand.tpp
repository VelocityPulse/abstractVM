/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:39:02 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 14:39:02 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP

#include "IOperand.hpp"

template <typename T>
class Operand<T> : public IOperand {

public:
	int getPrecision(void) const override {
		return 0;
	}

	eOperandType getType(void) const override {
		return nullptr;
	}

	IOperand const *operator+(IOperand const &rhs) const override {
		return nullptr;
	}

	IOperand const *operator-(IOperand const &rhs) const override {
		return nullptr;
	}

	IOperand const *operator*(IOperand const &rhs) const override {
		return nullptr;
	}

	IOperand const *operator/(IOperand const &rhs) const override {
		return nullptr;
	}

	IOperand const *operator%(IOperand const &rhs) const override {
		return nullptr;
	}

	std::string const &toString(void) const override {
		return <#initializer#>;
	}

};

#endif //ABSTRACTVM_OPERAND_HPP
