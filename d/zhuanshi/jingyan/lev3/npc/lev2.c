// migong lev3

#include <ansi.h>

inherit NPC;


void create()

{
    
   set_name(BLU"�ڹھ���"NOR, ({ "ju mang" , "mang" }));
                set("race", "Ұ��");
       set("long",
"һֻ��Ȼ������������,����Ҫһ�ڰ������¡�
��\n");
              set("attitude", "aggressive");
                set("vendetta/authority",1);

set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite" }) );
	       set("max_qi",1500+random(1500));
  set("max_jing",1500+random(1500));
  set("max_sen",1500+random(1500));
  set("max_mana",1500+random(1500));
  
      set("dex",40);
     set("str" ,60);
       
    set("age", 5);

       set("shen_type", -1);

        set("intellgent",1);

	set("pursuer",1);

        set("combat_exp", 1200000);
                  
        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/defence",100);

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




int hit_ob(object me, object ob, int damage)
{
   if( random(damage) > (int)ob->query_temp("apply/armor")
	&&	(int)ob->query_condition("snake_poison") < 10 ) {
		ob->apply_condition("snake_poison", 30);
        tell_object(ob, HIG "����ñ�ҧ�еĵط�һ��������\n" NOR );
	}
}
