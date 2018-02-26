/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateOperand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:34:13 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/26 11:34:13 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_CREATEOPERAND_HPP
#define ABSTRACTVM_CREATEOPERAND_HPP

#include <vector>
#include "IOperand.hpp"

class CreateOperand {

public:
	CreateOperand(); // Canonical
	~CreateOperand(); // Canonical

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

private:
	CreateOperand(CreateOperand const &copy); // Canonical
	CreateOperand &operator=(CreateOperand const &copy); // Canonical

	typedef std::vector<const IOperand *(CreateOperand::*)(const std::string &) const> VectorOperand;
	VectorOperand _createPointerTab;

};


#endif //ABSTRACTVM_CREATEOPERAND_HPP