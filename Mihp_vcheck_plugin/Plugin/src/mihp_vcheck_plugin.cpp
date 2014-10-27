#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <gcc-plugin.h>
#include <plugin-version.h>
#include <plugin-api.h>

#include <is-a.h>
#include <tree.h>
#include <basic-block.h>
#include <internal-fn.h>
#include <gimple-expr.h>
#include <tree-ssa-alias.h>
#include <gimple.h>
#include <tree-pass.h>
#include <context.h>
#include <function.h>
#include <gimple-iterator.h>
#include <gimple-pretty-print.h>
#include <tree-iterator.h>
#include <cfgloop.h>
#include <c-family/c-pragma.h>
#include <diagnostic-core.h>
#include <vec.h>
#include <list>
#include <string>


#ifndef NDEBUG
#	define printMihpIO(X) std::cout << X << std::endl;
#	define printfMihp(X, ...) printf(X, ##__VA_ARGS__)
#else
#	define printMihpIO(X)
#	define printfMihp(X, ...)
#endif

typedef std::list<std::string> ListeString;

int plugin_is_GPL_compatible;

///liste des fonctions à traiter avec le plugin
ListeString listMihpFunctionName;

using namespace std;

///fonction qui dit si une chaîne de caractères est dans une liste de string ou pas
/**	@param liste : liste de string
 * 	@param str : string
 * 	@return true si str est dans liste, false sinon
*/
bool isNameInListeFunction(ListeString & liste, const std::string & str){
	if(liste.size() == 0) return false;
	bool isFound(false);
	ListeString::iterator it(liste.begin());
	while(!isFound && it != liste.end()){
		if(*it == str){
			isFound = true;
			it = liste.erase(it);
		}
		++it;
	}
	return isFound;
}

///fonction qui permet de gérer le #pragma mihp vcheck
/**	@param dummy : variable qui sera inutilisée
 * 	Que l'on est obliger de mettre dans ce .cpp pour ne pas avoir de warning de variable non utilisée
*/
static void initMihpPragmaListFunction(cpp_reader *dummy ATTRIBUTE_UNUSED){
	printfMihp("initMihpPragmaListFunction begin\n");
	const char * fname = current_function_name();
	if(strcmp(fname, "(nofn)") != 0){  //ou si cfun == NULL
		printf("\tpragma mihp vcheck : fonction : '%s'\n", fname);
		printf("Le pragma instrument function doit être en dehors d'une fonction!!!\n");
		return;
	}
	std::string kind_string;        //la chaine de caractères que l'on va analyser
	tree x;                             //l'arbre des paramètres du pragma
	enum cpp_ttype token;              //le mot clè que l'on cherche
	token = pragma_lex(&x);
	if(token == CPP_NAME){            //si il n'y a qu'un seul mot clè
		kind_string = std::string(IDENTIFIER_POINTER(x)); //initialisation de la chaîne de caractères
		if(!isNameInListeFunction(listMihpFunctionName, kind_string)){
			listMihpFunctionName.push_back(kind_string);
		}else{
			cerr << "pragma mihp vcheck : La fonction '" << kind_string << "' a déjà été ajouté." << endl;
		}
	}else if(token == CPP_OPEN_PAREN){  //on est dans une liste
		token = pragma_lex(&x);    //on prend le prochain mot clè
		while(token == CPP_NAME){
			kind_string = std::string(IDENTIFIER_POINTER(x)); //initialisation de la chaîne de caractères
			if(!isNameInListeFunction(listMihpFunctionName, kind_string)){
				listMihpFunctionName.push_back(kind_string);
			}else{
				cerr << "pragma mihp vcheck : La fonction '" << kind_string << "' à déjà été ajouté." << endl;
			}
			token = pragma_lex(&x);          //on prend le prochain mot clè
			while(token == CPP_COMMA){
				token = pragma_lex(&x); //on prend le prochain mot clè
			}
		}
		if(token != CPP_CLOSE_PAREN){warning(OPT_Wpragmas, "Missing close parentèse ')'\n");}
	}else{
		warning(OPT_Wpragmas, "pragma mihp vcheck : missing function name, or (f1, f2, ..., fk)\n");
	}
}

const pass_data mihpVCheckPassData = {
	GIMPLE_PASS, /* type */
	"myPasse", /* name */
	0,
	true, /* has_gate */
	true, /* has_execute */
	TV_NONE, /* tv_id */
	0, /* properties_required */
	0, /* properties_provided */
	0, /* properties_destroyed */
	0, /* todo_flags_start */
	0, /* todo_flags_finish */
};

///@brief Classe qui décrit la passe GCC qui permet de vérifier si une boucle interne est vectorisable ou non
class MihpVCheckPass : public gimple_opt_pass{
	public:
		///Constructeur de MihpVCheckPass
		/**	@param ctxt : contexte gcc
		*/
		MihpVCheckPass(gcc::context *ctxt)
			:gimple_opt_pass(mihpVCheckPassData, ctxt)
		{}
		///destructeur de MihpVCheckPass
		virtual ~MihpVCheckPass(){}
		
		///fonction qui active ou non la passe
		/**	@return true si la passe doit être activée, false sinon
		*/
		bool gate(){
			printMihpIO("MihpVCheckPass::gate :");
			std::string functionName(current_function_name());
			if(isNameInListeFunction(listMihpFunctionName, functionName)){
				printMihpIO("\tfound '" << functionName << "'");
				return true;
			}else return false;
		}
		
		///fonction d'exécution de la passe
		/**	@return 0 si la fonction a réussie, 1 sinon
		*/
		unsigned int execute(){
			if(cfun == NULL){
				cerr << "MihpVCheckPass::execute : function undifined" << endl;
				return 1;
			}
			printMihpIO("MihpVCheckPass::execute : done");
			
			
			
			
			
			return 0;
		}
		
		opt_pass* clone(){
			return new MihpVCheckPass(m_ctxt);
		}
};

///fonction qui peremt de tester si toutes les fonctions spécifiées par l'utilisateur ont été taités
void callBackCheckMihpPragmaFinish(void *gcc_data, void *user_data){
	printfMihp("callBackCheckMihpPragmaFinish :\n");
	if(listMihpFunctionName.size() != 0){
		cerr << "pragma mihp vcheck : Toutes les fonctions spécifiées n'ont pas été trouvées" << endl;
		for(std::list<std::string>::iterator it(listMihpFunctionName.begin()); it != listMihpFunctionName.end(); ++it){
			std::cout << "fonction '" << *it << "'" << std::endl;
		}
		cerr << "\tn'ont pas été trouvées, mais spécfiées." << endl;
	}else{
		cout << "\tAll done" << endl;
	}
}

///fonction d'initialisation du plugin
/**	@param plugin_info : informations sur le plugin
 * 	@param version : version du plugin
 * 	@return 0 si l'initialisation a réussie, 1 sinon
*/
int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version){
	printfMihp("plugin_init : initialisation du plugin mihp vcheck\n");
	if(!plugin_default_version_check (version, &gcc_version)) return 1;
	
	struct register_pass_info pass_info;
	
	pass_info.pass = new MihpVCheckPass(g);
	pass_info.reference_pass_name = "cfg";
	pass_info.ref_pass_instance_number = 0;
	pass_info.pos_op = PASS_POS_INSERT_AFTER;
	
	register_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP, NULL, &pass_info);
	register_callback("pluginCheckMihpVcheckFinish", PLUGIN_FINISH, callBackCheckMihpPragmaFinish, NULL);
	c_register_pragma("mihp", "vcheck", initMihpPragmaListFunction);
	return 0;
}




