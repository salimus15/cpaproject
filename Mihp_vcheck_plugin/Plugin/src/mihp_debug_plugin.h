#ifndef __MIHP_DEBUG_PLUGIN_H__
#define __MIHP_DEBUG_PLUGIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <gcc-plugin.h>
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
#	define printfMihp(X, ...) printf(X, ##__VA_ARGS__);
#else
#	define printMihpIO(X)
#	define printfMihp(X, ...)
#endif

void printAllStmtBasicBlock(basic_block bb);
void printAllPrevousBasicBlock(basic_block bb);
void printAllNextBasicBlock(basic_block bb);
void printAllBlockInLoop(struct loop* boucle);


#endif

