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
#include "AbstractVM.hpp"

class CreateOperand {

public:
	typedef std::vector<const IOperand *(*)(std::string const &)> VectorOperand;

	static IOperand const * createOperand( eOperandType type, std::string const & value );
	static IOperand const * createInt8( std::string const & value );
	static IOperand const * createInt16( std::string const & value );
	static IOperand const * createInt32( std::string const & value );
	static IOperand const * createFloat( std::string const & value );
	static IOperand const * createDouble( std::string const & value );

private:
	CreateOperand(); // Canonical
	~CreateOperand(); // Canonical
	CreateOperand(CreateOperand const &copy); // Canonical
	CreateOperand &operator=(CreateOperand const &copy); // Canonical

	static VectorOperand _createPointerTab;

};


#endif //ABSTRACTVM_CREATEOPERAND_HPP