#include <ansi.h>
#include <combat.h>

#define JIUZI "��" HIY "��������" NOR "��"
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg, sub_msg;

        if (userp(me) && ! me->query("can_perform/jiuzi-zhenyan/jiuzi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIUZI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("JIUZIֻ�ܿ���ʹ�á�\n");
                
        if (me->query("max_neili") < 6000)
                return notify_fail("���������Ϊ���������޷�ʩչJIUZI��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");

        if ((int)me->query("qi") < 1000)
                return notify_fail("����������ڲ�����\n");

        if ((int)me->query_skill("jiuzi-zhenyan", 1) < 300)
                return notify_fail("��ľ������Ի�򲻹����޷�ʹ��JIUZI��\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ��JIUZI��\n");

        if (me->query_skill_prepared("hand") != "jiuzi-zhenyan")
              return notify_fail("������û��׼��ʹ�þ������ԣ��޷�ʹ��JIUZI��\n");

        if ( me->query("int") < 38 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");   

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIY "$N" HIY "ٿ���������У�ʮָ��������ӡ�ᣬ������������"
		 	"��������ޱ߽�⣬��$n" HIY "������ס��\n" NOR;   
	
	ap = me->query_skill("buddhism",1) + me->query_skill("lamaism",1);
	damage = (int)me->query_skill("jiuzi-zhenyan",1);

	if ( ap > 600 )
		damage = damage + ap / 2;

	if ( ap > 700 )
		damage = damage * ap / 700;
	
        msg += HIW "\n���٣���$N���н��һ����˫��һ�ţ��߾��ڶ���ʩ����" HIY "��������ӡ" HIW "��\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n�����мܣ����ι������ޣ���ʱ�������ˣ��³�һ����Ѫ��\n" NOR);
	if ( ap > 400 )
	{
	msg += HIW "\n$N" HIW "����" HIR "����ӡ" HIW "�����ƽ���֮�䣬�����������˷����������ھ���$n" HIW "ӿȥ��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$nһ���Һ��������������������ۡ���Ż��һ�����Ѫ��\n" NOR);
	msg += HIW "\n$N" HIW "һ�����壬��Цһ������������$n��ͬʱ���ְ���" HIY "ʨ��ӡ" HIW "������һ�����͡���\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n�Ṧ��Ƿ���һ��������Ȼ���С�\n" NOR);
	}
	if ( ap > 500 )
	{
	msg += HIW "\n$N" HIW "���ְ���" HIR "��ʨ��ӡ" HIW "������һ�ӣ�ֻ��һ����ǽ��$n��ȥ��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n��æ�񵲣�������ֵ���ס��ֻ�������Ѫ���ߣ�����������\n" NOR);
	
	msg += HIW "\n$N" HIW "����" HIG "��ȭӡ" HIW "��ͻȻȭ��ͻ�䣬�����������ǣ���$n" HIW "����Ҫ����ȥ��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$nֻ����Ϣ���ͣ����㲻�ȣ���ʱӦӡ����ɳ�ȥ��\n" NOR);
	}
	if ( ap > 600 )
	{
	msg += HIW "\n$N" HIW "ʹ����" HIR "�ڸ�ӡ" HIW "�����������������棬�������Դ���������Ȼӿ��$n��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "���$n���������������������ڣ���ʱ������Ѫ���硣\n" NOR);

	msg += HIW "\n$N" HIW "�ɡ�" HIR "�ڸ�ӡ" HIW "����Ϊ��" HIY "�⸿ӡ" HIW "��Ĵָ������࣬�������£�����$n��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n��æ������ˣ��ɶ���������ȫ���Ѷ��������˿ڣ���Ѫ�ɽ���\n" NOR);
	}
	if ( ap > 800 )
	{
	msg += HIW "\n$N" HIW "����" HIM "������ӡ" HIW "�����Ϻ�����֣�ֻ��һ�����˳�$nӿȥ��\n" NOR;
      	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n�������ã���ʱ��$N�������ˡ�\n" NOR);
	}
	if ( ap > 900 )
	{
	msg += HIW "\n$N" HIW "����" HIR "��ƿӡ" HIW "�������ٷǸ߶ȼ��е�һ�ţ�������һ��ǽ��ֱ��$nѹ��ȥ��\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n��Ȼ�����ֿ�����ƾ������Ϯ����Ѫ���ϴӿ��������\n" NOR);
	}

        message_combatd(msg, me, target);
        me->start_busy(3 + random(5));
        me->add("neili", -900);
	

        return 1;
}

        