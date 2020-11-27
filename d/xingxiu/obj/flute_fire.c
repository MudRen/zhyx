// Code of ShenZhou
// Ryu, 12/5/96

inherit ITEM;
#include <ansi.h>;

void init();
void wear(int);

int worn;

void create()
{
        set_name(HIR"һ�ѻ���"NOR,({"huo yan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR"�����Լ�ߣ�"+GRN+"ɫ�����̣�"+BLU+"����ɭɭ��"+HIR+"��Ѱ��������졣\n"NOR);
                set("unit", "��");
                set("value", 1);
                set("no_get", 1);
                set("no_drop", 1);
        }
        
        setup();
}

void init()
{
        worn = 0;
        call_out("wear", 100, 1); 
        add_action("do_kick","ti");
        add_action("do_kick","kick");
}


int do_kick(string arg){

	object ob, me, armor, temp_ob;
	mapping myfam;
	int exp1, exp2, damage;
	me=this_player();
	if( !arg || me != this_player(1)) return 0;
	ob = present(arg, environment(me));  
	
	damage = me->query_skill("feixing-shu",1);
	if(!ob) 
        {
               tell_object(me,"����û��" + arg + "������\n");
               return 1;
	}

	exp1=me->query("combat_exp");
	exp2=ob->query("combat_exp");
	
	if(!ob->is_character() || !me->is_fighting(ob) )
        {
                tell_object(me,"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
                return 1;
	}
	
	if (me->is_busy())
	{
               tell_object(me,"����æ���ء�\n");
	        return 1;
	}

	if ((damage<150)){
		message_vision(HIR"\n$N����һЦ������������������ȥ�����һ���ҽУ����������ˡ�\n"NOR,me);
      		me->set_temp("die_reason", "�����޶���������"); 
		me->receive_wound("qi", random(500));
		destruct(this_object());
		me->start_busy(random(2)+2);
		return 1;
	} else {
		
		me->add("neili",-damage);
		message_vision(HIR"\n$N��ɫһ�䣬����һ�Σ��Ѿ�ת��$n��󡣾����ҽţ�΢΢һ������������$n��ȥ��\n"NOR,me,ob);
		me->start_busy(random(2)+2);
		if (ob->query_skill_mapped("parry") == "dragon-strike" &&
		    !ob->query_temp("weapon") &&
		    ob->query_skill("dragon-strike",1) > damage/2 + random(damage/2))
		{
			message_vision(HIW"\n$Nһ��ŭ��˫�������ؿ��漴�����Ƴ���һ����ǽ��ӿ����ȴ�����Խ����ġ�����ʮ���ơ���\n"NOR,ob);
			message_vision(HIR"\n���������ȵ����˳���£���̼��Ը�����ٶ���$N�ɾ��ȥ��\n"NOR,me);
			temp_ob = ob;
			ob = me;
			me = temp_ob;
			damage = me->query_skill("dragon-strike",1);
		}
		if(random(exp1)>random(exp2))
		{
			if( ob->query_temp("armor/cloth")){
				armor = ob->query_temp("armor/cloth");
                		if( armor->query("id") != "armor") {
                     			message_vision(HIR"\nֻ��$N���ϵ�$n"+HIY+"�������յ���ɢ���ɡ�\n"NOR, ob, armor);
                    			armor->unequip();
       	             			armor->move(environment(ob));
                                        armor->set_name("�ս���" + armor->query("name"));
              				armor->set("value", 0);
              				armor->set("armor_prop/armor", 0);
               				ob->reset_action();
                		}
                	}
                	
			message_vision(HIR"\nֻ����һ���ҽУ�$n�������������������С�\n"NOR,me,ob);
       			ob->set_temp("die_reason", "�����޶���������"); 
			ob->receive_wound("qi", damage, me);
			ob->start_busy(random(2)+1);
			destruct(this_object());
			return 1;
		} else {
			message_vision(HIY"\n$n��֮�������������ֻ��$N΢΢��Ц��\n"NOR,me,ob);
			destruct(this_object());
			return 1;
		}
	}
	
}

void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", HIR"��������ȼ���ţ�"+GRN+"ɫ�����̣�"+BLU+"����ɭɭ��"+HIR+"��Ѱ��������졣\n"NOR);
                call_out("wear", 100, phase+1); 
                break;
        case 2:
                set("long", RED"����Խ��Խ���������������ˡ�\n"NOR);
                call_out("wear", 30, phase+1); 
                break;
        case 3:
                message("vision",RED"���潥����Ϩ���ˡ�\n"NOR, environment(this_object()));
                destruct(this_object());
                break;
        }       
}

// End of File 
