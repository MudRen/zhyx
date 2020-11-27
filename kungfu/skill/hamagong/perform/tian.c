// ������
// wrote by kasumi 2009.6
#include <ansi.h>

inherit F_SSERVER;
void tie_hit(object me, object target);
#define TIAN "��" HIG "������" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
       

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(TIAN "ֻ�ܿ���ʹ�á�\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("�㵱ǰ�������㣬�޷�ʩչ" TIAN "��\n");

        if ((int)me->query_skill("hamagong", 1) < 350)
                return notify_fail("��ĸ�󡹦��򲻹����޷�ʩչ" TIAN "��\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("����ڹ���Ϊ�������޷�ʩչ" TIAN "��\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("������û��׼��ʹ�ø�󡹦���޷�ʩչ" TIAN "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	    ap = me->query_skill("force") + me->query_skill("unarmed");
        dp = target->query_skill("force") + target->query_skill("dodge");
		
	    msg = HIM "$Nһ����Х��ȫ�����ŷ����������Ȼ�ᵽ���£�ֻ��$N˫��һ�ǣ�˫���ಢ\n" ;   
	    msg += HIM "��ǰ�����Ƴ���$n��ͬ��ǰ��Բ����ȫ��"HIG"�������졹"HIM"��������֮�£�\n" ; 
		
		if (ap * 3 / 5 + random(ap) > dp)
		{
          msg += HIY "$n���һ����������ǿ�н�����һ�ơ�ֻ���öԷ������������������������ֿ���\n" NOR;    
          message_combatd(msg, me, target);    
          target->start_busy(3);
	      me->start_busy(3);
          call_out("tie_hit",1, me,target);
		}
		else
		{
		 msg += HIC "$n" HIC "����С��$N" HIC "�����У���Ų���������������˸���񹦵��������֡�\n" NOR;
		 me->start_busy(3+random(3));
		 me->add("neili", -200);
         message_combatd(msg, me, target); 
        }		 
		

        return 1;
}

void tie_hit(object me, object target)
{
	int sum, n1, n2;
	string msg;

	if( !target || !me->is_fighting(target) ) return;

	if( !living(me) || me->is_ghost() ) return;

	if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

	sum = me->query_skill("force") + me->query_skill("unarmed") + target->query_skill("force") + target->query_skill("parry");
	n1 = me->query("neili");
	n2 = target->query("neili");

	me->add("neili", -100 * sum / me->query_skill("force",1) ); 
	if(me->query("neili")<0)me->set("neili",0);

	target->add("neili", -150 * sum / target->query_skill("force",1));
	if(target->query("neili")<0)target->set("neili",0);

	if( n1 > 3000 && n2 > 3000) {
		msg = HIW"��ʱ˫����������ǿ��������ʤ������ʹ�Է��ش����ɡ�\n"NOR;

		if( n1 > n2 )
		msg += HIW"�����ֽ���һ�ᣬ$nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
		else msg += HIW"�����ֽ���һ�ᣬ$Nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
	}

	else {

		if( n1 > n2 ) msg = HIY"$N���ϴ߶���󡹦�;�������˥�Ǽ����Թ�Ƭ�̣�$n����ȫ������졣\n"NOR;
		else msg = HIY"$N���Ϻ�����ʢ������󡹦���ӵ��˼��¡��Թ�Ƭ�̣�$N����ȫ������졣$n�ƺ���Ȼ����ʮ�㣬ͷ�������������ϡ�\n"NOR;
		}

	message_combatd(msg , me,target );


	if( me->query("neili") > 0 && target->query("neili") > 0 && me->is_busy() && target->is_busy() && living(me) && living(target) )
	{
		target->start_busy(3);
		me->start_busy(3);
		remove_call_out("tie_hit");
		call_out("tie_hit",1, me,target);
		return;
	}

	if( target->query("neili") <= 0 )
	{
	    msg = HIR "\n$nͻȻ������������ȫ������ԭ��������ȫ���ľ���ͻ��ǰ��һƬ����֮����\n";
		msg += HIR"�ѱ���󡹦һ�ƻ��У���Ҳ�߲���һ����һͷ�Ե��ڵأ��������ϡ�\n\n" NOR;
		message_combatd(msg , me,target );
		target->unconcious();  
		return;
	}

	if( me->query("neili") <= 0 )
	{
		message_vision(HIR "\n$N���Ϻ���������ͻȻ������������ȫ������ԭ��������ȫ���ľ�����󡹦��ʱȫ������������\n"
		                    "����ǰ��һƬ����֮������Ҳ�߲���һ����һͷ�Ե��ڵأ��������ϡ�\n\n" NOR, me);
	    me->unconcious();   
	}
}