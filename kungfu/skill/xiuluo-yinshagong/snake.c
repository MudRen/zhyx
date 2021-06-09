// powerup.c ������ɷ������ by Kasumi

#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;

void snake_hit(object me, object target);

int exert(object me, object target)
{
	int times;
	object weapon;

	if (target != me)
		return notify_fail("��ֻ�ܷ������Լ��ı����ϡ�\n");

	if ( !objectp(weapon = me->query_temp("weapon")))
               return notify_fail("�����װ�������������߲������档\n");

	if (me->query("family/family_name") != "�嶾��")     
                return notify_fail("ֻ���嶾�̵��Ӳ������ߡ�\n");    

	 if( me->query_skill("xiuluo-yinshagong",1) < 350 )
                return notify_fail("���������ɷ��̫��޷����ߣ�\n");

	if ((int)me->query("neili") < 500 )
		return notify_fail("������������޷����ߡ�\n");

	if ((int)me->query_temp("snake"))
		return notify_fail("���Ѿ��������ڱ������ˡ�\n");

	times =  me->query_skill("xiuluo-yinshagong",1)/40;
	if (times > 20)
       times = 20;
	   
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIM "$N" HIM "�ó�һ���������ش���������ֻ����ಡ���һ����һ�����ߴܵ���" + weapon->name()+ HIM"����������\n" NOR, me);
	me->set_temp("snake", times);
    call_out("snake_hit",1, me,target);
	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void snake_hit(object me, object target)
{
    object weapon;
	object *victim;
	string msg,name;
	string *parts=({ "ͷ��", "����", "����", "����", "����", "�ؿ�", "����"});
	string part;
	int damage,i;

	if (!objectp(me) || !objectp(weapon = me->query_temp("weapon")))
       return;
               
	if (me->query_temp("snake") > 1)
	{
		me->set_temp("snake", me->query_temp("snake") -1);
 		if (me->is_fighting())
		{
			part = parts[random(sizeof(parts))];
			switch (part)
			{
			case "ͷ��":
			    damage = target->query("max_qi") * 0.3;
				break;
			case "����":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "����":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "����":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "����":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "�ؿ�":
			    damage = target->query("max_qi") * 0.2;
				break;
			case "����":
			    damage = target->query("max_qi") * 0.2;
				break;
			}
			victim = me->query_enemy();
			for (i = 0; i < sizeof(victim); i++)
			{
				victim[i]->receive_wound("qi", damage, me);
				name = victim[i]->name();
				msg = HIM"ֻ������������������Ȼ�ſ���"+ name+ HIM"��"HIR"��" + part + HIR"��"HIM"�ݺݵ�ҧ��һ�ڣ�\n"NOR;				
				message("vision", msg, environment(me), ({ victim[i] }));
			}
				
		}
		else
		{
		    msg = HIG "$N" HIG "����" + weapon->name()+ HIG"���������һ�����ߣ���˿˿��������"HIR"����"HIG"��\n" NOR;
			message_combatd(msg, me);
		}
	 	remove_call_out("snake_hit");
		call_out("snake_hit",3, me,target);
		return ;
	}
 	else 
	{
	    me->delete_temp("snake");
		msg = HIY "������$N" + weapon->name()+ HIY"�ϵĹ��ߣ���ಡ���һ���ܵ����ϲ�������Ӱ��\n" NOR;
		message_combatd(msg, me);
		return ;
	} 
} 
