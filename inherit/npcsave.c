// npc.c

#include <origin.h>
#include <user.h>

inherit NPC;
//inherit F_AUTOLOAD;
inherit F_SAVE;

string SAVE_NAME="npc_save";
nomask int can_save=1;

string query_save_name() {return SAVE_NAME;}

void reload(string savename)
{
      if(clonep()) {
        if(sizeof(filter_array(children(base_name(this_object())), 
          (:clonep:)))>1) {
            can_save=0;
	    call_out("self_destroy",1);
	    return;
	}
      }

   if(clonep() && savename && can_save) { 
   // only cloned obj can save and restore.
     SAVE_NAME=savename;
     if(!restore())
       log_file("npc_save",sprintf("Failed to restore %s(%s).\n",
         this_object()->query("id"),savename));
   }   
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = SAVE_NAME;
	if( !stringp(id) ) return 0;
	return sprintf(DATA_DIR "npc/%c/%s", id[0], id);
}

int save()
{
	int res;
	string file=query_save_file();
	string dir=DATA_DIR "npc/";
	int len=strlen(dir);
	
	if(!file || strlen(file)<=len) return 0;
	// can only save to DATA_DIR "npc/" dir.
	if(file[0..(len-1)]!=dir) return 0;

        if(clonep() && can_save) {
//      save_autoload();    // NPC don't need autoload. mon 5/19/98
	  res = ::save();
//	  clean_up_autoload();		// To save memory
	  return res;
	} else
	  return 0;  
}

void setup()
{
      ::setup();
//      restore_autoload();
}

// create() is actually no use since all NPC has their own create().
void create()
{
     set_name("��ʹ�������", ({ "npc object", "npc", "object" }) );
}

void self_destroy()
{
    if(this_object())
	destruct(this_object());
}

