
#include "mihp_debug_plugin.h"

using namespace std;

///fonction qui affiche tout les statements gimple d'un block de base
/**	@param bb : block de base dont on veut afficher les statements gimple
*/
void printAllStmtBasicBlock(basic_block bb){
	gimple_stmt_iterator gsi = gsi_start_bb(bb);
	gimple stmt = gsi_stmt(gsi);
	printfMihp("\t\t\tBLOCK INDEX %d : LINE %d\n", bb->index, gimple_lineno(stmt));
	while(!gsi_end_p(gsi)){
		stmt = gsi_stmt(gsi);
		printfMihp("\t\t\t\t");
		//Il va falloir tester le type de statement pour appeler la fonction mihp_adress()
		print_gimple_stmt(stdout, stmt, 0, 0);
		gsi_next(&gsi);
	}
}



