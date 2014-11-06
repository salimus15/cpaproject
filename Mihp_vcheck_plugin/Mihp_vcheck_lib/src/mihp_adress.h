#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>



#ifndef MIHP_ADRESS_H
#define MIHP_ADRESS_H

/** \class Mihp_Adress [mihp_adress.h] [mihp_adress]
*\brief classe regroupe les informations relatives aux adresses memoire accédées durant le déroulement de la boucle
* Elle nous renseigne sur l'adresse mémoire accédée lors d'une itération de boucle, le type d'accés (lecture ou écriture) ainsi que la taille du block qu'occupe la variable accédée
*
*/

class Mihp_Adress{
	
	protected:
	
		
			// Adresse de la variable 
	bool acc_type;    // acc_type = 0 when reading & acc_type = 1 when writing.
	  // taille de la variable ie: nombre de block à considerer à partir de p_adr
		
		
		/** \fn void CopieMihpAdress( const Mihp_Adress & other)
		*	\brief fonction de copie 
		*	\param other Objet à copier 
		*	
		*/		
	void CopieMihpAdress( const Mihp_Adress & other);
		
		
		
	public:
	size_t data_tsize;
	void * p_adr;
		/** \fn Mihp_Adress()
		* \brief Constructeur de la classe
		*/
	Mihp_Adress();
		
		/** \fn Mihp_Adress(const Mihp_Adress & other)
		* \brief Constructeur par copie de la classe
		* \param other élément à copier 
		*/
	Mihp_Adress (const Mihp_Adress & other);  
		
		/** \fn ~Mihp_Adress()
		* \brief Destructeur de la classe
		*/
	~Mihp_Adress();
		
		/** \fn Mihp_Adress & operator= (const Mihp_Adress & other)
		* \brief Surcharge de l'operateur '=' pour cette classe
		* \param other élément à copier, où opérande de  droite de l'opration '='
		* \return Objet Mihp_Adress qui est une copie de 'other'
		*/
	Mihp_Adress & operator= (const Mihp_Adress & other);
		
		/** \fn bool Mihp_Adress_get_t()
		* \brief fonction qui retourne le type d'accés à l'adresse mémoire
		* elle retourne la valeur de la variable  acc_type, si c'est une écriture ou une lecture
		* \return 0 si c'est une lecture et 1 si c'est une écriture
		*/
	bool Mihp_Adress_get_t() const;
		 
		 /** \fn size_t Mihp_Adress_get_size()
		* \brief fonction qui retourne la taille de la variable
		* elle retourne la valeur de la variable  data_tsize
		* \return taille de la variable 
		*/
	size_t Mihp_Adress_get_size() const;
		 
		 /** \fn void * Mihp_Adress_get_adr();
		* \brief fonction qui retourne l'adresse mémoire accédée 
		* elle retourne la valeur de la variable  p_adr
		* \return adresse mémoire accédée
		*/
	void * Mihp_Adress_get_adr() const;
	
		/** \fn void Mihp_Adress_set_t(bool rw )
		* \brief initialise la variable acc_type à la valeur donée en entrée
		*
		* \param rw booleen définissant le type d'accés à l'adresse
		* 
		*/
	void Mihp_Adress_set_t(bool rw );
	
		/** \fn void Mihp_Adress_set_size(size_t s )
		* \brief initialise la variable data_tsize
		*
		* \param s taille du type de la variable 
		* 
		*/
	void Mihp_Adress_set_size(size_t s );
	
		/** \fn void Mihp_Adress_set_adr(void * p_ad )
		* \brief initialise la variable p_adr
		*
		* \param p_ad valeur à attribuer à la variable p_adr
		* 
		*/
	void Mihp_Adress_set_adr(void * p_ad );
		
		/** \fn bool Is_same_adress(const Mihp_Adress & adress1,const Mihp_Adress & adress2)
		* \brief verifie si deux objets Mihp_Adress ont la meme valeur de p_adr
		*	cette fonction verifie que deux objets ont la meme valeur de p_adr, donc savoir si il s'agit de la meme adresse mémoire.
		* \param adress1 Objet de type Mihp_Adress à verifier
		* \param adress2 Objet de type Mihp_Adress à verifier 
		* \return retourne Vrai si les deux adress1 et adress2 sont identiaques et Faux sinon
		*/	
	bool Is_same_adress(const Mihp_Adress & adress1,const Mihp_Adress & adress2);
	
		/** \fn bool Is_writing_same_adress(const Mihp_Adress & adress1, const Mihp_Adress & adress2)
		* \brief meme que Is_same_adress sauf qu'elle verifie que c'est une écriture qui se fait
		*verifie si deux objet Mihp_Adress ont la méme valeur de p_adr et si ils s'agit d'une écriture dans les deux cas
		* \param adress1 Objet de type Mihp_Adress à verifier
		* \param adress2 Objet de type Mihp_Adress à verifier 
		* \return Vrai si c'est écriture sur la meme adresse et Faux sinon
		*/
	bool Is_writing_same_adress(const Mihp_Adress & adress1, const Mihp_Adress & adress2);

};

#endif
