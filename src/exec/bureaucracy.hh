#pragma once
#include "exec/context.hh"
#include "data/entity.hh"

namespace fargo
{

	class Bureaucrat 
	{

	public:
		Bureaucrat();
		~Bureaucrat();
		void contextualize(const Context& otro_contexto);
		bool see_eligibility(const Entity& subject);
		unsigned int see_benefit(const Entity& subject);

	private:
		Context context;
	
	};
	
}