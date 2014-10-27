
#include "mihp_debug_plugin.h"

using namespace std;

///fonction qui affiche tout les statements gimple d'un block de base
/**	@param bb : block de base dont on veut afficher les statements gimple
*/
void printAllStmtBasicBlock(basic_block bb){
	gimple_stmt_iterator gsi = gsi_start_bb(bb);
	if(gsi_end_p(gsi)) return;
	gimple stmt = gsi_stmt(gsi);
	printfMihp("\t\tBLOCK INDEX %d : LINE %d\n", bb->index, gimple_lineno(stmt));
	while(!gsi_end_p(gsi)){
		stmt = gsi_stmt(gsi);
		printfMihp("\t\t\t");
		//Il va falloir tester le type de statement pour appeler la fonction mihp_adress()
		print_gimple_stmt(stdout, stmt, 0, 0);
		gsi_next(&gsi);
	}
}

///fonction qui affiche tous les blocks précédent celui donné en paramètre
/**	@param bb : block de base dont on veut afficher les précédents
*/
void printAllPrevousBasicBlock(basic_block bb){
	printfMihp("printAllPrevousBasicBlock : current block\n");
	printAllStmtBasicBlock(bb);
	printfMihp("\t previous blocks\n");
	edge currentEdge;
	edge_iterator it;
	FOR_EACH_EDGE(currentEdge, it, bb->preds){ //on parcours les edges d'un block de base
		printAllStmtBasicBlock(currentEdge->src);
	}
}

///fonction qui affiche tous les blocks suivants celui donné en paramètre
/**	@param bb : block de base dont on veut afficher les suivants
*/
void printAllNextBasicBlock(basic_block bb){
	printfMihp("printAllNextBasicBlock : current block\n");
	printAllStmtBasicBlock(bb);
	printfMihp("\t Next blocks\n");
	edge currentEdge;
	edge_iterator it;
	FOR_EACH_EDGE(currentEdge, it, bb->succs){ //on parcours les edges d'un block de base
		printAllStmtBasicBlock(currentEdge->dest);
	}
}

///fonction qui affiche les différents blocks de base que l'on trouve dans une boucle
/**	@param boucle : boucle que l'on veut afficher
*/
void printAllBlockInLoop(struct loop* boucle){
	if(boucle == NULL) return;
	if(boucle->header != NULL){
// 		printfMihp("Le block précédent du header de la boucle\n");
// 		printAllStmtBasicBlock(boucle->header->prev_bb);
		printfMihp("Le block de base du header de la boucle\n");
		printAllStmtBasicBlock(boucle->header);
	}
	if(boucle->latch != NULL){
		printfMihp("Le latch de la boucle\n");
		printAllStmtBasicBlock(boucle->latch);
	}
	printfMihp("Les autres blocks de base de la boucle\n");
	
	basic_block bb;
	basic_block* listeBlock = get_loop_body(boucle);
	if(listeBlock == NULL){                       //si la boucle est vide on s'arrête
		warning(OPT_Wpragmas, "\tEmpty loop'\n");
		return;
	}
	
	for(size_t i(0); i < boucle->num_nodes; ++i){ //on parcours tout les blocks de base
		bb = listeBlock[i];
		printAllStmtBasicBlock(bb);
	}
}


