/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVMException.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:39:10 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/12 13:39:10 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AbstractVMException.hpp"

AbstractVMException::AbstractVMException() {

}

AbstractVMException::AbstractVMException(std::string msg) : _msg(msg) {

}

AbstractVMException::~AbstractVMException() {

}

AbstractVMException::AbstractVMException(AbstractVMException const &copy) {
	*this = copy;
}

AbstractVMException &AbstractVMException::operator=(AbstractVMException const &copy) {
	if (this != &copy) {
		// copy
		this->_msg = copy._msg;
	}
	return *this;
}

const char *AbstractVMException::what() const throw() {
//	return exception::what();
	return std::string("AbstractVM Exception : " + this->_msg).c_str();
}