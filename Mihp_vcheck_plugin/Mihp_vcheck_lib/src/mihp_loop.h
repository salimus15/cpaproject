#include <list>
#include <string>
#include "mihp_iteration.h"

#ifndef MIHP_LOOP_H
#define MIHP_LOOP_H


/** \class Mihp_Loop [mihp_loop.h] [mihp_loop]
*\brief classe regroupant toutes les informations relatives à la boucle
*
*/

class Mihp_Loop{
	
	private:
		std::string func_name;		// nom dela fonction contenant la boucle
		std::string file_name;		// nom du fichier où la boucle est définie
		size_t loop_nline;		// numéro de ligne de la boucle actuelle dans le fichier

		std::list<Mihp_Iteration> iters; 		// liste des itérations de la boucle  see mihp_iteration.h
		std::list<Mihp_Iteration>::iterator it;		// iterateur pour le parcours de la liste des itérations
		
		/** \fn void CopieLoop(const Mihp_Loop & other)
		*	\brief fonction de copie 
		*	\param other Objet à copier 
		*	
		*/	
		void CopieLoop(const Mihp_Loop & other);
		
	public:
		
		
		/** \fn Mihp_Loop(
		* \brief Constructeur de la classe
		*/
		Mihp_Loop();
		
		Mihp_Loop(const std::string & funname, const std::string & filname, const unsigned int & linnumb );		
		
		/** \fn Mihp_Loop(const Mihp_Loop & other)
		* \brief Constructeur par copie de la classe
		*/
		
		Mihp_Loop(const Mihp_Loop & other);
		
		/** \fn ~Mihp_Loop()(
		* \brief Destructeur de la classe
		*/		
		~Mihp_Loop();
		
		void MihpSetFuncName(const std :: string & fname);
		
		void MihpSetFileName(const std :: string & filname);
		
		void MihpSetLineNum(size_t numline);
		
		
		/// ajout d'un élément a la liste des iterations
		void Mihp_add_iter(const Mihp_Iteration & new_iter);
		
		/// récupère l'élément suivant si il y en a sinon NULL
		//Mihp_Iteration Mihp_get_next_iter();
	
		
		/** \fn bool MihpCheckRecouvement()
		*	\brief test si il y a des recouvrement entre les adresses, inter-iterations
		*	\return Vrai si il y a recouvrement et Faux sinon 
		*/
		bool MihpCheckRecouvement();
		
		void MihpCheckIterDep();
		
		void AfficherIterations();
};

#endif
