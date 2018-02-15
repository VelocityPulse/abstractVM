/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 12:07:13 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 12:07:13 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_IOPERAND_HPP
#define ABSTRACTVM_IOPERAND_HPP

#include <string>

enum eOperandType {
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand {

public:
	virtual ~IOperand(void) {}
	virtual int getPrecision(void) const = 0; // Precision of the _type of the instance

	virtual eOperandType getType(void) const = 0; // Type of the instance
	virtual IOperand const *operator+(IOperand const &rhs) const = 0; // Sum
	virtual IOperand const *operator-(IOperand const &rhs) const = 0; // Difference
	virtual IOperand const *operator*(IOperand const &rhs) const = 0; // Product
	virtual IOperand const *operator/(IOperand const &rhs) const = 0; // Quotient
	virtual IOperand const *operator%(IOperand const &rhs) const = 0; // Modulo

	virtual std::string const &toString(void) const = 0; // String representation of the instance
};

std::ostream &operator<<(std::ostream &o, IOperand const &rhs) {
	o << rhs.toString();
	return o;
}

#endif //ABSTRACT_IOPERAND_HPP