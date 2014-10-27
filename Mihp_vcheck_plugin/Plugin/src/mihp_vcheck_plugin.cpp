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
#include <c-family/c-common.h>
#include <diagnostic-core.h>
#include <output.h>
#include <vec.h>
#include <list>
#include <string>


#ifndef NDEBUG
#	define printMihpIO(X) std::cerr << X << std::endl;
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
	printMihpIO("isNameInListeFunction : begin");
	if(liste.size() == 0) return false;
	printMihpIO("isNameInListeFunction : iteration");
	ListeString::iterator it(liste.begin());
	while(it != liste.end()){
		if(*it == str){
			liste.erase(it);
			return true;
		}
		++it;
	}
	return false;
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

///fonction qui permet de créer une nouvelle boucle
/**	@param loopHeader : block de base d'entrée de la boucle
 * 	@param functionName : nom de la fonction où se trouve la boucle à analyser
 * 	@param currentFunctionName : nom de la fonction dans laquelle est la boucle
 * 	@param fileName : nom du fichier dans lequel est la fonction
 * 	@param loopLine : ligne du début de la boucle que l'on souhaite analyser
*/
void createGimpleCallBeforeLoop(basic_block loopHeader, const char * functionName, const char * currentFunctionName, const char* fileName, size_t loopLine){
	if(functionName == NULL || currentFunctionName == NULL || fileName == NULL) return;
	tree mystring_tree = fix_string_type(build_string(strlen(currentFunctionName) + 1, currentFunctionName));
	tree mystring_type = build_pointer_type(TREE_TYPE(TREE_TYPE(mystring_tree)));
	tree mystring_args_tree = build1(ADDR_EXPR, mystring_type, mystring_tree);
	
	tree mystringFName_tree = fix_string_type(build_string(strlen(fileName) + 1, fileName));
	tree mystringFName_type = build_pointer_type(TREE_TYPE(TREE_TYPE(mystringFName_tree)));
	tree mystringFName_args_tree = build1(ADDR_EXPR, mystringFName_type, mystringFName_tree);
	
	//on définit la fonction, type retourné et paramètre(s)
	tree enter_functionDefintion = build_function_type_list(void_type_node, string_type_node, integer_type_node, NULL_TREE);
	tree enter_functionBuild = build_fn_decl(functionName, enter_functionDefintion);
	
	gimple callPrintfNode = gimple_build_call(enter_functionBuild, 3, mystring_args_tree, mystringFName_args_tree, build_int_cst(integer_type_node, loopLine));
	if(callPrintfNode == NULL){
		cerr << "\tcreateGimpleCallBeforeLoop : callPrintfNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallBeforeLoop : callPrintfNode : ";
		print_gimple_stmt(stdout, callPrintfNode, 0, 0);
	}
	loopHeader = ENTRY_BLOCK_PTR_FOR_FN(cfun); //test en entrant dans la fonction
	basic_block nextBb;
	edge currentEdge;
	edge_iterator it;
	
	gimple_stmt_iterator gsi;
	gimple stmt;
	
// 	FOR_EACH_EDGE(currentEdge, it, loopHeader->preds){ //on parcours les edges d'un block de base
	FOR_EACH_EDGE(currentEdge, it, loopHeader->succs){ //on parcours les edges d'un block de base
		nextBb = currentEdge->dest;
		gsi = gsi_start_bb(nextBb);
		stmt = gsi_stmt(gsi);
		print_gimple_stmt (stdout, stmt, 0, 0);
		
		gsi_insert_before(&gsi, callPrintfNode, GSI_NEW_STMT);
	}
}

///fonction qui créer les Gimple Call vers les sondes de notre librairie d'analyse
/**	@param boucle : boucle à modifier avec des appels aux sondes de notre librairie d'analyse
 * 	Cette fonction ne teste pas si la boucle passée en paramètre est la plus interne ou non, car c'est la fonction addGimpleCallInLoop qui nous garantie cela
*/
void addGimpleCallInInnerLoop(struct loop* boucle){
	if(boucle == NULL) return;                //si la boucle est NULL on s'arrête
// 	location_t loc = get_loop_location(boucle);
// 	printMihpIO("\t\tLoop location : " << loc);
	
	basic_block loopHeader = boucle->header; //on récupère le header de la boucle pour appeler mihp_newLoop avant
	createGimpleCallBeforeLoop(loopHeader, "mihp_newLoop", current_function_name(), main_input_filename, 0);
	
	gimple_stmt_iterator gsi;
	gimple stmt;
	basic_block bb;
	basic_block* listeBlock = get_loop_body(boucle);
	if(listeBlock == NULL){                       //si la boucle est vide on s'arrête
		warning(OPT_Wpragmas, "\tEmpty loop'\n");
		return;
	}
	
	for(size_t i(0); i < boucle->num_nodes; ++i){ //on parcours tout les blocks de base
		bb = listeBlock[i];
		for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)){
			stmt = gsi_stmt(gsi);
			//Il va falloir tester le type de statement pour appeler la fonction mihp_adress()
			print_gimple_stmt(stdout, stmt, 0, 0);
			printfMihp("\t\t\tBLOCK INDEX %d : LINE %d\n", bb->index, gimple_lineno(stmt));
		}
	}
	
// 	edge latchEdge = loop_latch_edge(boucle); //on récupère l'arrête du latch de la boucle
	//on va pouvoir appeler mihp_newIteration()
	
	//on récupère toutes les arrêtes qui sortent de la boucle 
// 	vec<edge> loopExitEdges = get_loop_exit_edges(boucle);
	//on va pouvoir appeler mihp_endLoop()
	
	
}


///fonction qui ajoute les appels de fonctions (sondes) dans les boucles les plus internes de la fonction que l'on doit analyser
/**	@param boucle : boucle à analyser
*/
void addGimpleCallInLoop(struct loop* boucle){
	if(boucle == NULL) return;                //si la liste est vide on s'arrête
	struct loop* inner;                       //boucle plus interne
	for(inner = boucle->inner; inner != NULL; inner = inner->next){
		if(inner->inner == NULL){ //on est bien dans une boucle interne
			//on rajoute tout les appels de fonctions qui vont bien
			//on a la garantie que l'on est dans une boucle interne
			addGimpleCallInInnerLoop(inner);
		}else{                   //on va dans la boucle la plus interne
			addGimpleCallInLoop(inner);
		}
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
			if(cfun == NULL) return false;
			std::string functionName(current_function_name());
			printMihpIO("MihpVCheckPass::gate : '" << functionName << "'");
			if(isNameInListeFunction(listMihpFunctionName, functionName)){
				printMihpIO("\tfound '" << functionName << "'");
				return true;
			}else return false;
		}
		
		///fonction d'exécution de la passe
		/**	@return 0 si la fonction a réussie, 1 sinon
		*/
		unsigned int execute(){
			printMihpIO("MihpVCheckPass::execute : begin");
			if(cfun == NULL){
				cerr << "MihpVCheckPass::execute : function undifined" << endl;
				return 1;
			}
			//on récupère l'ensemble des boucle de la fonction
			struct loops * boucles = loops_for_fn(cfun);
			if(boucles->tree_root->inner == NULL){ //tree_root est une liste de loops, si inner est NULL c'est qu'il n'y en a pas
				warning(OPT_Wpragmas, "\tNo loop détected'\n");
				return 0;
			}else{
				printMihpIO("\tloop founded");
			}
			//À partir de là, on a la garantie d'avoir au moins une boucle dans la fonction cfun, dans la liste boucles->tree_root
			addGimpleCallInLoop(boucles->tree_root);
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




