#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>

#include "mihp_adress.h"

#ifndef MIHP_ITERATION_H
#define MIHP_ITERATION_H

typedef Mihp_Adress Mihp_Adress;


/** \class Mihp_Iteration [mihp_iteration.h] [mihp_iteration]
*\brief classe regroupant toutes les informations relatives à une itération de la boucle
*
*/
class Mihp_Iteration{
	
	private:
	
		
		
		std::list<Mihp_Adress> adres_acc; 		// liste des adresses accédées lors d'une itérationde la boucle
		std::list<Mihp_Adress>::iterator it;	// iterateur pour parcourir la liste
		
		/** \fn void CopieMihpAdress( const Mihp_Adress & other)
		*	\brief fonction de copie 
		*	\param other Objet à copier 
		*	
		*/	
		void CopieIteration (const Mihp_Iteration & other);
		
				
	public:
	
		/** \fn Mihp_Iteration(
		* \brief Constructeur de la classe
		*/
		Mihp_Iteration();
		
	
		
		/** \fn Mihp_Iteration(const Mihp_Iteration & other)
		* \brief Constructeur par copie de la classe
		*/
		Mihp_Iteration(const Mihp_Iteration & other);
		
				
		/** \fn ~Mihp_Iteration()
		* \brief Destructeur de la classe
		*/
		~Mihp_Iteration();
		
		
		/// ajout d'un élément a la liste des adresses
		void MihpAddAdr(const Mihp_Adress & new_adr);
		
		/** \fn bool MihpCheckAdressRecouvrement(const void * & a_d1, const void * & a_f1, const void * & a_d2, const void * & a_f2 )
		*	\brief test si il y a des recouvrement entre deux adresses,
		*	\param a_d1 adresse de debut de la premiere adresse
		*	\param a_d2 adresse de debut de la seconde adresse
		*	\param a_f1 adresse de fin de la premiere adresse
		*	\param a_f2 adresse de fin de la seconde adresse
		*
		*	\return Vrai si il y a recouvrement et Faux sinon 
		*/
		bool MihpCheckAdressRecouvrement(const void *  a_d1, const void *  a_f1, const void *  a_d2, const void *  a_f2 );
			
		/** \fn bool MihpCheckIterRecouvrement(const Mihp_Iteration & other)
		*	\brief teste si il y a des recouvrement entre l'iteration courante et l'iteration other
		*	\param other iteration dont on souhaite si elle a des recouvrements avec l'iteration courante 
		*	\return Vrai si il y a recouverement et Faux sinon
		*
		*/ 
		bool MihpCheckIterRecouvrement(const Mihp_Iteration & other);
		
		/// récupère l'élément suivant si il y en a sinon NULL
		//Mihp_Adress MihpGetNext_adr();
	
		
		
};

#endif
