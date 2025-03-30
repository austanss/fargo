#include "exec/bureaucracy.hh"

using namespace fargo;

Bureaucrat::Bureaucrat() {}

Bureaucrat::~Bureaucrat() {}

void Bureaucrat::contextualize(const Context& otro_contexto) 
{
	this->context = Context(otro_contexto);
}

bool Bureaucrat::see_eligibility(const Entity& subject) 
{
	return !(this->context.controls.monthly_benefit < (subject.month_revenue / 2));
}

unsigned int Bureaucrat::see_benefit(const Entity& subject) 
{
	if (this->see_eligibility(subject))
		return this->context.controls.monthly_benefit - (subject.month_revenue / 2);
	else
		return 0;
}
