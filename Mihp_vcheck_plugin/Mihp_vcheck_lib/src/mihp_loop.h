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
	
	public:
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
		
	
		
		
		/** \fn Mihp_Loop()
		* \brief Constructeur de la classe
		*/
		Mihp_Loop();
		
		 //fn Mihp_Loop(const std::string & funname, const std::string & filname, const unsigned int & linnumb )		   
		
		/** \brief constructeur avec toutes les donnees relative a la boucle a analyser 
		* \param funname nom de la fonction contenant la boucle a analyser
		* \param filname nom duf fichier contenant la fonction funName
 		* \param linenumb Numero de la ligne de la boucle
		*/
		Mihp_Loop(const std::string & funame, const std::string & filname, const unsigned int & linnumb );		
		
		/** \fn Mihp_Loop(const Mihp_Loop & other)
		* \brief Constructeur par copie de la classe
		*/
		
		Mihp_Loop(const Mihp_Loop & other);
		
		/** \fn virtual ~Mihp_Loop()
		* \brief Destructeur de la classe
		**/		
		
		virtual ~Mihp_Loop();
		
		/** \fn void MihpSetFuncName(const std :: string & fname) 
		* \brief initialise le nom de la fonction a fname 
		* \param fname nom de la fonction 
		*
		**/
				
		void MihpSetFuncName(const std :: string & fname);
		
		/** \fn void MihpSetFileName(const std :: string & filname) 
		* \brief initialise le nom du fichier a filname 
		* \param filname nom du fichier 
		*
		**/
		void MihpSetFileName(const std :: string & filname);

		/** \fn void MihpSetLineNum(size_t numline)
		* \brief initialise le numero de ligne de la boucle
		* \param numline : numero de ligne de la boucle 
		*
		**/
		void MihpSetLineNum(size_t numline);
		
		/** \fn void Mihp_add_iter(const Mihp_Iteration & new_iter)
		* \brief ajout d'un élément a la liste des iterations
		* \param new_iter nouvelle iteration a rajouter
		*
		**/
		
		void Mihp_add_iter(const Mihp_Iteration & new_iter);
		
		
		/** \fn void Mihp_add_adr( const Mihp_Adress & new_adr)
		* \brief ajoute une nouvelle adresse a l'iteration courante ( derniere)
		* \param new_adr nouvelle adresse a rajouter
		*
		**/		 
		void Mihp_add_adr( const Mihp_Adress & new_adr);
		
				
		// récupère l'élément suivant si il y en a sinon NULL
		//Mihp_Iteration Mihp_get_next_iter();
		
		/** \fn void MihpLoopClear()
		* \brief efface les iterations de la boucle
		*
		**/
		void MihpLoopClear();
		
		/** \fn bool MihpCheckRecouvement()
		*	\brief test si il y a des recouvrement entre les adresses, inter-iterations
		*	\return Vrai si il y a recouvrement et Faux sinon 
		*/
		bool MihpCheckRecouvement();
		/** \fn void MihpCheckIterDep()
		* \brief Fonction qui vérifie si il y a des dépendances entre les itérations de la boucle
		*/
		void MihpCheckIterDep();
		
		/** \fn void AfficherIterations()
		*	\brief affiche toutes les iterations
		*	
		*/
		void AfficherIterations();
};

#endif
