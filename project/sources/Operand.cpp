#include "../includes/Operand.hpp"

Operand::Operand() {

}

Operand::Operand(Operand const &copy) {
	*this = copy;
}

Operand::~Operand() {

}

Operand &Operand::operator=(Operand const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}