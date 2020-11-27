#include <ansi.h>

inherit F_CLEAN_UP;

void dest_sword(object me);

int exert(object me, object target)
{
        object weapon;
		int damage;

        if (target != me)
                return notify_fail("�������ν�ֻ��ͨ���Լ�ʹ�á�\n");

        if ((int)me->query("neili") < me->query("max_neili") / 2 )
                return notify_fail("�����������������ʩչ�������ν���\n");

		if ((int)me->query("jingli") < 500)
                return notify_fail("��ľ�������������ʩչ�������ν���\n");
		
		if ((int)me->query_skill("linji-zhuang", 1) < 300)
                return notify_fail("����ټ�ʮ��ׯ��򲻹�������ʩչ�������ν���\n");

		if ((int)me->query_skill("mahayana", 1) < 200)
                return notify_fail("��Ĵ����������򲻹�������ʩչ�������ν���\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ѿ��������ˡ�\n");

        if (present("emei jianqi", me))
                return notify_fail("�������Ѿ���һ�������ˡ�\n");
				
	    if (me->query("family/family_name") != "������")     
                return notify_fail("���ѷǶ����ɵ��ӣ���Ե���ô˾�ѧ�ˡ�\n");
				
        me->add("neili", -100);
		me->add("jingli", -100);

        message_combatd(HIW "$N" HIW "ʳָ��㣬ָ���ʱ����������²�����"
                        "��â������һ�����ν�����\n" NOR, me);

        weapon = new("/clone/weapon/em_jianqi");
		damage=(int) me->query_skill("mahayana", 1);
		weapon->set("weapon_prop/damage",damage);
        weapon->move(me);
        //weapon->wield();
		

        me->start_call_out((: call_other, __FILE__, "dest_sword",
                              me :), 120);

        if (me->is_fighting())
        me->start_busy(1);

        return 1;
}

void dest_sword(object me)
{
        object weapon;      
		   
		if (present("emei jianqi",me))   
        {
		        weapon = present("emei jianqi",me);
                if (me->is_fighting())
                        me->start_call_out((: call_other, __FILE__, "dest_sword",
                                              me :), 2);
                else
				message_combatd(HIW "һ��΢�������$N" HIW "���ϵ��������ν�����ȥ��\n" NOR, me);
                destruct(weapon);
        }
}
