// migong lev1

#include <ansi.h>

inherit NPC;


void create()

{
    
   set_name(RED"���"NOR, ({ "wu gong"}));
      
          set("race", "Ұ��");
       set("long",
"һֻ�ж��Ļ��ɫ����򼡣
��\n");
              set("attitude", "aggressive");
                set("vendetta/authority",1);

set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite" }) );
	       set("max_qi",500+random(500));
  set("max_jing",500+random(500));
  set("max_sen",500+random(500));
  set("max_mana",500+random(500));
  
      set("dex",20);
     set("str" ,25);
       
    set("age", 5);

       set("shen_type", -1);

        set("intellgent",1);

	set("pursuer",1);

        set("combat_exp", 300000);
                  
        set_temp("apply/attack", 50);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/defence",50);

   setup();

        

}

void init( )

{
	object ob;	
        remove_call_out("hunting");
	if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
	if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
	int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());

      }
}
