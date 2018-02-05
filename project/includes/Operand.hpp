#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP

class Operand {

public:
	Operand(); // Canonical
	Operand(Operand const &copy); // Canonical
	~Operand(); // Canonical

	Operand &operator=(Operand const &copy); // Canonical

private:

};


#endif //ABSTRACTVM_OPERAND_HPP