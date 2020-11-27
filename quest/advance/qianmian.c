// qianmian guai
// mon 8/7/97

inherit NPC;

void copy_status(object me, object ob, int power);

void create()
{
	set_name("ǧ���", ({ "qianmian guai", "guai", "qianmian", "qm" }) );
	set("gender", "����" );
	set("age", 30);
	set("attitude", "heroism");
  setup();

}


// this copy function is used by some other NPCs also,
// so if need to change here, please consider carefully.
// mon 1/13/99
void copy_status(object me, object ob, int ratio)
{
        mapping my, hp_status, skill_status, map_status;
        string *sname, *mname;
				int i,j, base=20;
				
				hp_status = ob->query_entire_dbase();
				my = me->query_entire_dbase();


//���ü���
			if(ratio<1) ratio=base;

        // delete old skills.
        if(skill_status = me->query_skills()) {
           sname  = keys(skill_status);
	   j=sizeof(skill_status);
           for(i=0; i<j; i++) {
	     me->delete_skill(sname[i]);
           }
        }

        //copy new skills.
	if (skill_status = ob->query_skills() ) {
	   sname  = keys(skill_status);
	   for(i=0; i<sizeof(skill_status); i++) {
		me->set_skill(sname[i], 
			skill_status[sname[i]]*ratio/base);
	   }
        }
	
	//delete old skill mappings.
	if(map_status = me->query_skill_map()) {
	  mname  = keys(map_status);
	  j=sizeof(map_status);
	  for(i=0; i<j; i++) {
	    me->map_skill(mname[i]);
          }
        }
         
        //add new skill mappings.
	if (map_status = ob->query_skill_map()) {
	  mname  = keys(map_status);
	  for(i=0; i<sizeof(map_status); i++) {
		me->map_skill(mname[i], map_status[mname[i]]);
	  }
        }


//����״̬
	
	      my["str"] = hp_status["str"] ;
        my["int"] = hp_status["int"] ;
        my["con"] = hp_status["con"] ;
        my["dex"] = hp_status["dex"] ;

        my["max_qi"]     = hp_status["max_qi"];
        my["eff_qi"]     = my["max_qi"];
        my["qi"]         = my["max_qi"];
        my["max_jing"]   = hp_status["max_jing"];
        my["eff_jing"]   = my["max_jing"];
        my["jing"]       = my["max_jing"];
        my["max_neili"]  = hp_status["max_neili"];
        my["jiali"]      = hp_status["jiali"];
        if (my["max_neili"] > 9000)
                // max_neili not more then 9k
                my["max_neili"] = 9000;
        my["neili"]      = my["max_neili"] * 2;

	return ;
}

