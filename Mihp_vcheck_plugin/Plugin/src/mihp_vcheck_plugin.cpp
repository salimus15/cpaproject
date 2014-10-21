
#include <iostream>
#include <plugin.h>
#include <gcc-plugin.h>
#include <plugin-version.h>
#include <tree-pass.h>
#include <context.h>
#include <function.h>
#include <basic-block.h>
#include <is-a.h>
#include <tree.h>
#include <tree-ssa-alias.h>
#include <internal-fn.h>

#include <gimple-expr.h>

#include <gimple.h>
#include <gimple-builder.h>
#include <gimple-iterator.h>
#include <gimple-pretty-print.h>

int plugin_is_GPL_compatible;

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

class MihpVCheckPass : public gimple_opt_pass{
	public:
		MihpVCheckPass(gcc::context *ctxt)
			:gimple_opt_pass(mihpVCheckPassData, ctxt)
		{}
		virtual ~MihpVCheckPass(){}
		
		bool gate(){
			std::cout << "MihpVCheckPass::gate : done" << std::endl;
			return true;
		}
		
		unsigned int execute(){
			std::cout << "MihpVCheckPass::execute : done" << std::endl;
			return 0;
		}
		
		opt_pass* clone(){
			return new MihpVCheckPass(m_ctxt);
		}
};

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version){
	printf("plugin_init : initialisation de mon plugin\n");
	if(!plugin_default_version_check (version, &gcc_version)) return 1;
	
	struct register_pass_info pass_info;
	
	pass_info.pass = new MihpVCheckPass(g);
	pass_info.reference_pass_name = "cfg";
	pass_info.ref_pass_instance_number = 0;
	pass_info.pos_op = PASS_POS_INSERT_AFTER;
	
	register_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP, NULL, &pass_info);
	
	return 0;
}




