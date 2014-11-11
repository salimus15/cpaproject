
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
	
	gimple callBeforeLoopNode = gimple_build_call(enter_functionBuild, 3, mystring_args_tree, mystringFName_args_tree, build_int_cst(integer_type_node, loopLine));
#ifndef NDEBUG
	if(callBeforeLoopNode == NULL){
		cerr << "\tcreateGimpleCallBeforeLoop : callBeforeLoopNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallBeforeLoop : callBeforeLoopNode : ";
		print_gimple_stmt(stdout, callBeforeLoopNode, 0, 0);
	}
#endif
	edge_iterator it = ei_start(loopHeader->preds);
	edge currentEdge;
	ei_cond(it, &currentEdge);
	basic_block prevBlock = currentEdge->src;              //on a bien le premier précédent block
	gimple_stmt_iterator gsi = gsi_start_bb(prevBlock);    //on récupère l'itérateur
	gsi_insert_before(&gsi, callBeforeLoopNode, GSI_NEW_STMT);
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

///fonction qui ajoute un appel à une fonction après la fin d'une boucle
/**	@param boucle : boucle après laquelle on veut appeler la fonction functionName
 * 	@param functionName : nom de la fonction à appeler
*/
void createGimpleCallAfterExitLoop(struct loop* boucle, const char * functionName){
	if(boucle == NULL || functionName == NULL) return;
	//on définit la fonction, type retourné et paramètre(s)
	tree enter_functionDefintion = build_function_type_list(void_type_node, NULL_TREE);
	tree enter_functionBuild = build_fn_decl(functionName, enter_functionDefintion);
	
	gimple callAfterLoopNode = gimple_build_call(enter_functionBuild, 0);
#ifndef NDEBUG
	if(callAfterLoopNode == NULL){
		cerr << "\tcreateGimpleCallAfterExitLoop : callAfterLoopNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallAfterExitLoop : callAfterLoopNode : ";
		print_gimple_stmt(stdout, callAfterLoopNode, 0, 0);
	}
#endif
	//on récupère toutes les arrêtes qui sortent de la boucle 
	vec<edge> loopExitEdges = get_loop_exit_edges(boucle);
	basic_block nextBlock;
	gimple_stmt_iterator gsi;
	size_t i(0);
	edge exitEdge;
	while(loopExitEdges.iterate(i, &exitEdge)){
		nextBlock = exitEdge->dest;              //on a bien le block suivant
		gsi = gsi_start_bb(nextBlock);             //on récupère l'itérateur
		gsi_insert_before(&gsi, callAfterLoopNode, GSI_NEW_STMT);
		++i;
	}
}

///fonction qui permet de renvoyer la taille d'une opérande gimple suivant son type
/**	@param op : opérande dotn on veut la taille
 * 	@return taille de l'opérande
*/
size_t getSizeofOperandGimple(const_tree op){
	size_t nbBlock(0);  //taille de l'accès mémoire
	
	//méthode bourin pour récuperer la taille de l'opérande (à défaut de faire un truc classe comme ajouter un sizeof)
	//mais je n'ai pas encore trouvé comment faire
	if(TREE_TYPE(op) == float_type_node){nbBlock = 4;		printfMihp("\t\033[34mfloat\033[0m");}			//float
	else if(TREE_TYPE(op) == double_type_node){nbBlock = 8;		printfMihp("\t\033[34mdouble\033[0m");}			//double
	else if(TREE_TYPE(op) == long_double_type_node){nbBlock = 16;	printfMihp("\t\033[34mlong double\033[0m");}		//long double
	
	else if(TREE_TYPE(op) == intQI_type_node){nbBlock = 4;		printfMihp("\t\033[34mint QI\033[0m");}			//int QI
	else if(TREE_TYPE(op) == intHI_type_node){nbBlock = 4;		printfMihp("\t\033[34mint HI\033[0m");}			//int HI
	else if(TREE_TYPE(op) == intSI_type_node){nbBlock = 4;		printfMihp("\t\033[34mint SI\033[0m");}			//int SI
	else if(TREE_TYPE(op) == intDI_type_node){nbBlock = 4;		printfMihp("\t\033[34mint DI\033[0m");}			//int DI
	else if(TREE_TYPE(op) == intTI_type_node){nbBlock = 4;		printfMihp("\t\033[34mint TI\033[0m");}			//int TI
	
	else if(TREE_TYPE(op) == unsigned_intQI_type_node){nbBlock = 4;	printfMihp("\t\033[34munsigned int QI\033[0m");}	//unsigned int QI
	else if(TREE_TYPE(op) == unsigned_intHI_type_node){nbBlock = 4;	printfMihp("\t\033[34munsigned int HI\033[0m");}	//unsigned int HI
	else if(TREE_TYPE(op) == unsigned_intSI_type_node){nbBlock = 4;	printfMihp("\t\033[34munsigned int SI\033[0m");}	//unsigned int SI
	else if(TREE_TYPE(op) == unsigned_intDI_type_node){nbBlock = 4;	printfMihp("\t\033[34munsigned int DI\033[0m");}	//unsigned int DI
	else if(TREE_TYPE(op) == unsigned_intTI_type_node){nbBlock = 4;	printfMihp("\t\033[34munsigned int TI\033[0m");}	//unsigned int TI
	
	else if(TREE_TYPE(op) == float_ptr_type_node){nbBlock = 4;		printfMihp("\t\033[34mfloat*\033[0m");}		//float*
	else if(TREE_TYPE(op) == dfloat32_ptr_type_node){nbBlock = 4;		printfMihp("\t\033[34mconst float*\033[0m");}		//float*
	else if(TREE_TYPE(op) == double_ptr_type_node){nbBlock = 8;		printfMihp("\t\033[34mdouble*\033[0m");}	//double*
	else if(TREE_TYPE(op) == long_double_ptr_type_node){nbBlock = 16;	printfMihp("\t\033[34mlong double*\033[0m");}	//long double*
	else if(TREE_TYPE(op) == integer_ptr_type_node){nbBlock = 4;		printfMihp("\t\033[34mint*\033[0m");}		//int*
	
	else if(TREE_TYPE(op) == ptr_type_node){nbBlock = sizeof(void*);		printfMihp("\t\033[34mvoid*\033[0m");}		//void*
	else if(TREE_TYPE(op) == const_ptr_type_node){nbBlock = sizeof(const void*);	printfMihp("\t\033[34mconst void*\033[0m");}	//const void*
	return nbBlock;
}

///fonction qui créé l'appel à la fonction qui gère les accès aux variables
/**	@param functionName : nom de la fonction à appeler
 * 	@param op : opérande à passée en paramètre à la fonction
 * 	@param isWrited : true si on écrit, false si on lit l'opérande
 * 	@param bb : block de base à la fin duquel on va ajouter l'appel de la fonction functionName
*/
void createGimpleCallForOpInLoop(const char * functionName, const_tree op, bool isWrited, basic_block bb){
	if(functionName == NULL) return;
	
// 	size_t nbBlock(getSizeofOperandGimple(op));
// 	size_t nbBlock = sizeof_vn_nary_op(TREE_CODE_LENGTH(TREE_CODE (op))); //renvoie 32 pour toutes les opérandes
	size_t nbBlock = int_size_in_bytes(TREE_TYPE (op));
	//on définit la fonction, type retourné et paramètre(s)
	//on a bien un void f(const void*, size_t, int )
	tree enter_functionDefintion = build_function_type_list(void_type_node, const_ptr_type_node, long_unsigned_type_node, integer_type_node, NULL_TREE);
	tree enter_functionBuild = build_fn_decl(functionName, enter_functionDefintion);
	
	gimple callOpInNode = gimple_build_call(enter_functionBuild, 3,
						op,  //compile, et fonctionne, je ne vois pas trop pourquoi, mais comme ça fait trois jours que je galère, je prends
						build_int_cst(long_unsigned_type_node, nbBlock),
						build_int_cst(integer_type_node, isWrited));
	// type void* = build_pointer_type (void_type_node)
	// build_reference_type(TREE_TYPE(op));  //construit un type &
	// build_pointer_type(TREE_TYPE(op));    //construit un type *
	//addr = create_tmp_var (build_pointer_type (TREE_TYPE (decl)), NULL); //créé une variable temporaire
#ifndef NDEBUG
	if(callOpInNode == NULL){
		cerr << "\tcreateGimpleCallForOpInLoop : callOpInNode = NULL" << endl;
		return;
	}else{
		cerr << "\tcreateGimpleCallForOpInLoop : callOpInNode : ";
		print_gimple_stmt(stdout, callOpInNode, 0, 0);
	}
#endif
	
#ifndef DONT_ADD_GIMPLE_NODE_MIHP_ADDRESS
	edge_iterator it = ei_start(bb->succs);
	edge currentEdge;
	ei_cond(it, &currentEdge);
	basic_block prevBlock = currentEdge->dest;              //on a bien le premier précédent block
	gimple_stmt_iterator gsi = gsi_last_bb(prevBlock);      //on récupère l'itérateur, on se met à la fin des statements
	gsi_insert_after(&gsi, callOpInNode, GSI_NEW_STMT);
#endif
}

///fonction qui analyse une opérande d'un GIMPLE_ASSIGN
/**	@param op : opérande à analyser
 * 	@param isWrited : true si l'opérande est écrite, false sinon
 * 	@param bb : block de base à la fin duquel sera ajouter l'appel à la fonction qui inserera l'appel à la fonction mihp_address
*/
void analyseSingleOperand(const_tree op, bool isWrited, basic_block bb){
	switch(TREE_CODE(op)){
		case INTEGER_CST:
			printfMihp("\t\033[33mINTEGER_CST\033[0m\n"); //c'est une constante donc on ne fait rien
			break;
		case REAL_CST:
			printfMihp("\t\033[33mREAL_CST\033[0m"); //c'est une constante donc on ne fait rien
// 			createGimpleCallForOpInLoop("mihp_adress", op, isWrited, bb);
			break;
		case VAR_DECL:
			printfMihp("\t\033[33mVAR_DECL\033[0m");
			createGimpleCallForOpInLoop("mihp_adress", op, isWrited, bb);
			break;
		case PARM_DECL:
			printfMihp("\t\033[33mPARM_DECL\033[0m");
			createGimpleCallForOpInLoop("mihp_adress", op, isWrited, bb);
			break;
		case CONST_DECL:
			printfMihp("\t\033[33mCONST_DECL\033[0m\n"); //c'est une constante donc on ne fait rien
			break;
		case STRING_CST:
			printfMihp("\t\033[33mSTRING_CST\033[0m\n");
			break;
		case SSA_NAME:
			printfMihp("\t\033[33mSSA_NAME\033[0m\n");
			break;
		case MEM_REF:
			printfMihp("\t\033[33mMEM_REF\033[0m\n");
// 			createGimpleCallForOpInLoop("mihp_adress", op, isWrited, bb);
			break;
		case ADDR_EXPR:
			printfMihp("\tADDR_EXPR\t");
			createGimpleCallForOpInLoop("mihp_adress", op, isWrited, bb);
			break;
		case ARRAY_REF:
			printfMihp("\tARRAY_REF\t");analyseSingleOperand(TREE_OPERAND(op,0), isWrited, bb);   //l'adresse de base
			printfMihp("\tARRAY_REF\t");analyseSingleOperand(TREE_OPERAND(op,1), false, bb);      //le décallage de l'opérateur []
			break;
		default:
			printfMihp("\tdefault\n");
			break;
	}
}

///fonction qui analyse la boucle pour créer des appels à la fonction mihp_adress pour chaque opérande
/**	@param boucle : boucle à analyser
*/
void analyseLoopBlockStmtOp(struct loop* boucle){
	if(boucle == NULL) return;
	
// 	basic_block callBlock = alloc_block();
// 	link_block(boucle->header, callBlock);
// 	link_block(callBlock, boucle->latch); //le suivant de callBlock est latch
	
	basic_block* listeBlock = get_loop_body(boucle);
	if(listeBlock == NULL){                       //si la boucle est vide on s'arrête
		warning(OPT_Wpragmas, "\tEmpty loop'\n");
		return;
	}
	gimple_stmt_iterator gsi;
	gimple stmt;
	basic_block bb;
	const_tree op;
	for(size_t i(0); i < boucle->num_nodes; ++i){                            //on parcours tout les blocks de base
		bb = listeBlock[i];
		if(bb == boucle->header) continue;
		for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)){   //on parcours tout les statements
			stmt = gsi_stmt(gsi);
			//Il va falloir tester le type de statement pour appeler la fonction mihp_adress()
			if(gimple_code(stmt) == GIMPLE_ASSIGN){                 //on ne s'intéresse au'aux Gimple Assign
				printfMihp("\tGIMPLE_ASSIGN : BLOCK INDEX %d : LINE %d\n\t\t", bb->index, gimple_lineno(stmt));
				print_gimple_stmt(stdout, stmt, 0, 0);
				printf("\t\t\tOpération %s\n", get_tree_code_name(gimple_assign_rhs_code(stmt)));
				for(size_t i(0); i < gimple_num_ops(stmt); i++){  //on parcours toutes les opérandes
					op = gimple_op(stmt, i);
					if(!op)continue;
					analyseSingleOperand(op, i == 0, boucle->header); //on analyse l'opérande courante (boucle->latch ou boucle->header)
// 					return;
				}
			}
		}
	}
}

///fonction qui créer les Gimple Call vers les sondes de notre librairie d'analyse
/**	@param boucle : boucle à modifier avec des appels aux sondes de notre librairie d'analyse
 * 	Cette fonction ne teste pas si la boucle passée en paramètre est la plus interne ou non, car c'est la fonction addGimpleCallInLoop qui nous garantie cela
*/
void addGimpleCallInInnerLoop(struct loop* boucle){
	if(boucle == NULL) return;                //si la boucle est NULL on s'arrête
	//on rajoute l'appel de fonction avant la boucle
	createGimpleCallBeforeLoop(boucle->header, "mihp_newLoop", current_function_name(), main_input_filename, getLoopLine(boucle));
	//on ajoute l'appel de fonction à la fin de la boucle
	createGimpleCallAfterExitLoop(boucle, "mihp_endLoop");
	//on analyse les opérandes des blocks contenus dans la boucle
	analyseLoopBlockStmtOp(boucle);
	//on ajout l'appel de fonction avant le latch
	createGimpleCallAfterLatchLoop(boucle->latch, "mihp_newIteration");
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
			printfMihp("Après addGimpleCallInInnerLoop :\n");
			printAllBlockInLoop(inner);
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

