#include "exec/bureaucracy.hh"

using namespace fargo;

Bureaucrat::Bureaucrat() {}

Bureaucrat::~Bureaucrat() {}

void Bureaucrat::contextualize(const Context& otro_contexto) 
{
	this->context = Context(otro_contexto);
}

bool Bureaucrat::see_eligibility(unsigned long income) 
{
	return !(this->context.controls.monthly_benefit < (income / 2));
}

unsigned int Bureaucrat::see_benefit(unsigned long income) 
{
	if (this->see_eligibility(income))
		return this->context.controls.monthly_benefit - (income / 2);
	else
		return 0;
}
