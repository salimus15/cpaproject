
#include "mihp_loop_analysis.h"

using namespace std;

///fonction qui permet de créer une nouvelle boucle
/**	@param loopHeader : block de base d'entrée de la boucle
 * 	@param loopLatch : block de base qui reboucle sur le block d'entrée
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
#ifndef NDEBUG
	if(callPrintfNode == NULL){
		cerr << "\tcreateGimpleCallBeforeLoop : callPrintfNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallBeforeLoop : callPrintfNode : ";
		print_gimple_stmt(stdout, callPrintfNode, 0, 0);
	}
#endif
	edge_iterator it = ei_start(loopHeader->preds);
	edge currentEdge;
	ei_cond(it, &currentEdge);
	basic_block prevBlock = currentEdge->src;              //on a bien le premier précédent block
	gimple_stmt_iterator gsi = gsi_start_bb(prevBlock);    //on récupère l'itérateur
	gsi_insert_before(&gsi, callPrintfNode, GSI_NEW_STMT);
}

///fonction qui permet de créer une nouvelle boucle
/**	@param loopLatch : block de base qui reboucle sur le block d'entrée
 * 	@param functionName : nom de la fonction où se trouve la boucle à analyser
*/
void createGimpleCallAfterLatchLoop(basic_block loopLatch, const char * functionName){
	if(functionName == NULL) return;
	//on définit la fonction, type retourné et paramètre(s)
	tree enter_functionDefintion = build_function_type_list(void_type_node, NULL_TREE);
	tree enter_functionBuild = build_fn_decl(functionName, enter_functionDefintion);
	
	gimple callBeforeLatchNode = gimple_build_call(enter_functionBuild, 0);
#ifndef NDEBUG
	if(callBeforeLatchNode == NULL){
		cerr << "\tcreateGimpleCallAfterLatchLoop : callBeforeLatchNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallAfterLatchLoop : callBeforeLatchNode : ";
		print_gimple_stmt(stdout, callBeforeLatchNode, 0, 0);
	}
#endif
	edge_iterator it = ei_start(loopLatch->preds);
	edge currentEdge;
	ei_cond(it, &currentEdge);
	basic_block prevBlock = currentEdge->src;              //on a bien le premier précédent block
	gimple_stmt_iterator gsi = gsi_start_bb(prevBlock);    //on récupère l'itérateur
	gsi_insert_before(&gsi, callBeforeLatchNode, GSI_NEW_STMT);
	
}

///fonction qui créer les Gimple Call vers les sondes de notre librairie d'analyse
/**	@param boucle : boucle à modifier avec des appels aux sondes de notre librairie d'analyse
 * 	Cette fonction ne teste pas si la boucle passée en paramètre est la plus interne ou non, car c'est la fonction addGimpleCallInLoop qui nous garantie cela
*/
void addGimpleCallInInnerLoop(struct loop* boucle){
	if(boucle == NULL) return;                //si la boucle est NULL on s'arrête
	//on rajoute l'appel de fonction avant la boucle
	createGimpleCallBeforeLoop(boucle->header, "mihp_newLoop", current_function_name(), main_input_filename, getLoopLine(boucle));
	//on ajout l'appel de fonction avant le latch
	createGimpleCallAfterLatchLoop(boucle->latch, "mihp_newIteration");
	
// 	gimple_stmt_iterator gsi;
// 	gimple stmt;
// 	basic_block bb;
	basic_block* listeBlock = get_loop_body(boucle);
	if(listeBlock == NULL){                       //si la boucle est vide on s'arrête
		warning(OPT_Wpragmas, "\tEmpty loop'\n");
		return;
	}
	
// 	if(boucle->superloops != NULL){
// 		printfMihp("superloops exists!!!!\n");
// 		printMihpIO("superloops lentgh : " << boucle->superloops->length());
// 		if(!boucle->superloops->is_empty()){
// 			struct loop * ptOuterLoop = boucle->superloops->last();
// 			printfMihp("ptOuterLoop content :\n");
// // 			printAllStmtBasicBlock(ptOuterLoop);
// 			printAllBlockInLoop(ptOuterLoop);
// 		}
// 	}
	
// 	for(size_t i(0); i < boucle->num_nodes; ++i){ //on parcours tout les blocks de base
// 		bb = listeBlock[i];
// 		printAllStmtBasicBlock(bb);
// // 		for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)){
// // 			stmt = gsi_stmt(gsi);
// // 			//Il va falloir tester le type de statement pour appeler la fonction mihp_adress()
// // 			print_gimple_stmt(stdout, stmt, 0, 0);
// // 			printfMihp("\t\t\tBLOCK INDEX %d : LINE %d\n", bb->index, gimple_lineno(stmt));
// // 		}
// 	}
	
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
			printAllBlockInLoop(inner);
			addGimpleCallInInnerLoop(inner);
		}else{                   //on va dans la boucle la plus interne
			addGimpleCallInLoop(inner);
		}
	}
}

///fonction qui renvoie la ligne de déclaration d'une boucle
/**	@param boucle : boucle dont on veut la ligne
 * 	@return ligne de déclaration de la boucle
*/
int getLoopLine(struct loop* boucle){
	if(boucle == NULL) return 0;
	basic_block bb = boucle->header;
	gimple_stmt_iterator gsi = gsi_start_bb(bb);
	gimple stmt = gsi_stmt(gsi);
	return gimple_lineno(stmt);
}


