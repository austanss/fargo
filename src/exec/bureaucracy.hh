#pragma once
#include "exec/context.hh"

namespace fargo
{

	class Bureaucrat 
	{

	public:
		Bureaucrat();
		~Bureaucrat();
		void contextualize(const Context& otro_contexto);
		bool see_eligibility(unsigned long income);
		unsigned int see_benefit(unsigned long income);

	private:
		Context context;
	
	};
	
}