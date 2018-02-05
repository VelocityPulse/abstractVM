/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 10:42:28 by cchameyr          #+#    #+#             */
/*   Updated: 2018/02/05 10:42:30 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>


int main(int argc, char **argv) {

	(void)argv;

	if (argc == 2) {
		std::cout << "arguments" << std::endl;
	} else if (argc == 1) {
		std::cout << "standard entry" << std::endl;
	} else {
		std::cout << "bad entry" << std::end;
	}
}