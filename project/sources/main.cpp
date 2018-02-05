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

void manageStandardEntry() {
	std::string line;

	while (std::getline(std::cin, line)) {
		std::cout << "line : " + line << std::endl;
	}
	std::cout << "end of line" << std::endl;
}

int main(int argc, char **argv) {

	(void)argv;

	if (argc == 2) {
		std::cout << "arguments" << std::endl;
	} else if (argc == 1) {

		manageStandardEntry();

		std::cout << "standard entry" << std::endl;
	} else {
		std::cout << "bad entry" << std::endl;
	}
}
