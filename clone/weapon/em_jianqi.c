#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{     	   
        set_name(HIW "�������ν�" NOR, ({ "emei jianqi", "jianqi", }));
        set_weight(1);
		
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "����һ�����������ɵĽ�����\n" NOR);             
				set("no_give", "��������޷������ˡ�");               
                set("material", "air");              
        }
		
        init_sword(100);
        setup();
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
       int ap,dp;
       int n,damage;	
		
		n = (int) (me->query_skill("mahayana", 1)/10);
		damage = (int) me->query_skill("mahayana", 1);
		
		if ( me->query_temp("no_exert") || !me->query_skill("mahayana", 1)|| me->query("family/family_name") != "������")
		{
			 destruct(this_object());
			 message_combatd(HIW "һ��΢��������������ν�������ȥ��\n" NOR, me);
		}


		if (random(6)<n)
		{
		     victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
             return HIG "$N" HIG "������â������һ��������$n" HIG "�����$n��Ѫ������\n" NOR;		
		} 
        
        return ;
}
