#include <ansi.h>
#include <combat.h>

#define WUJI "��" HIW "�����޼�" NOR "��"
inherit F_SSERVER;

int perform(object me, object target)
{
    object weapon;
    int ap, dp; 
    int i, count, shd, jia, layer, damage;
    string msg;
    

 
    if (! target) target = offensive_target(me);
    if (! target || ! me->is_fighting(target))
    		return notify_fail(WUJI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
    		return notify_fail(WUJI "ֻ�ܿ���ʩչ��\n");
    if ((int)me->query_skill("longxiang-gong", 1) < 420)
    		return notify_fail("��������������Ϊ����������ʩչ" WUJI "��\n");
    if (me->query("max_neili") < 8500)
    		return notify_fail("���������Ϊ���㣬����ʩչ" WUJI "��\n");
    if (me->query_skill_mapped("unarmed") != "longxiang-gong")
    		return notify_fail("��û�м������������Ϊȭ�ţ�����ʩչ" WUJI "��\n");
    if (me->query_skill_mapped("force") != "longxiang-gong")
    		return notify_fail("��û�м������������Ϊ�ڹ�������ʩչ" WUJI "��\n");
    if (me->query_skill_prepared("unarmed") != "longxiang-gong")
    		return notify_fail("��û��׼��ʹ�����������������ʩչ" WUJI "��\n");
    if (me->query("neili") < 1000)
    		return notify_fail("�����ڵ��������㣬����ʩչ" WUJI "��\n");
    if (! living(target))
    		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


    msg = HIY "$N" HIY "����һ��ŭ������������������������ޣ�ȫ���ʱ�"
        "�ŷ����������ڶ���������$N" HIY "\n�ķ�������ʯ�䣬$N" HIY "˫"
        "ȭ��Я���������֮�Ʊ����������������ﳾ�����������ھ�ѧ����������\n" NOR; 
    
        if ( me->query("max_neili") > target->query("max_neili") * 2 && me->query("neili") > 500 )
        {
        		msg += HIR "$n" HIR "ȫȻ�����赲������$N"
        		HIR "һȭ���÷������صĵ����ڵ��ϡ�\n" NOR;
        		me->add("neili", -500);
        		me->start_busy(3);
        		message_combatd(msg, me, target);
      	    target->unconcious();
      	    return 1;
       } else
       {      
                ap = me->query_skill("unarmed") + me->query_skill("force") + me->query_str() * 10;
                dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
                if (ap + random(ap) > dp)
         	{
        	    if (target->query_temp("shield"))
        	    {
        	    		shd = target->query_temp("apply/armor");
        	    		target->add_temp("apply/armor", -shd);
        	    		target->delete_temp("shield");
        	  		msg += HIW "$N" HIW "���ӿ������Ȼ���������ˣ���ʱ��$n"
        	  		   		HIW "�Ļ��������ݻٵõ�Ȼ�޴棡\n" NOR;
        	    }
        	    jia = me->query("jiali");
                    damage = me->query_skill("longxiang-gong", 1) * 10 + random(jia * 10);
        	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
        	    	      HIR "$n" HIR "�������ܣ��ٱ�$N" HIR
        	    	   	      "˫ȭ�������У������������룬��"
        	    	   	      "������������\n" NOR);
        	    me->add("neili", -400);
     	    } else
     	  	{
     	  	    me->add("neili", -200);
     	  	    msg += CYN "����$n" CYN "ʶ����$N"
     	  	     	    CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
     	  	}
			
			message_combatd(msg, me, target);

    msg = HIY "$N" HIY "����һ��ŭ������������������������ޣ�ȫ���ʱ�"
        "�ŷ����������ڶ���������$N" HIY "\n�ķ�������ʯ�䣬$N" HIY "˫"
        "ȭ��Я���������֮�Ʊ����������������ﳾ�����������ھ�ѧ����������\n" NOR;
 
    
        if ( me->query("max_neili") > target->query("max_neili") * 2 && me->query("neili") > 500 )
        {
        		msg += HIR "$n" HIR "ȫȻ�����赲������$N"
        		HIR "һȭ���÷������صĵ����ڵ��ϡ�\n" NOR;
        		me->add("neili", -500);
        		me->start_busy(3);
        		message_combatd(msg, me, target);
      	    target->unconcious();
      	    return 1;
       } else
       {      
                ap = me->query_skill("unarmed") + me->query_skill("force") + me->query_con() * 10;
                dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
                if (ap + random(ap) > dp)
         	{
        	    if (target->query_temp("shield"))
        	    {
        	    		shd = target->query_temp("apply/armor");
        	    		target->add_temp("apply/armor", -shd);
        	    		target->delete_temp("shield");
        	  		msg += HIW "$N" HIW "���ӿ������Ȼ���������ˣ���ʱ��$n"
        	  		   		HIW "�Ļ��������ݻٵõ�Ȼ�޴棡\n" NOR;
        	    }
        	    jia = me->query("jiali");
                    damage = me->query_skill("longxiang-gong", 1) * 10 + random(jia * 10);
        	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
        	    	      HIR "$n" HIR "�������ܣ��ٱ�$N" HIR
        	    	   	      "˫ȭ�������У������������룬��"
        	    	   	      "������������\n" NOR);
        	    me->add("neili", -400);
     	    } else
     	  	{
     	  	    me->add("neili", -200);
     	  	    msg += CYN "����$n" CYN "ʶ����$N"
     	  	     	    CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
     	  	}
			
			message_combatd(msg, me, target);
			
	    msg = HIY "$N" HIY "һ��������������ű�ӿ���˵ڶ���������������������"
        "���಻����������磡ֱ��$N" HIY "\n��ʮ�����������꣬����������"
        "�ŵ�������������ˣ���$n" HIY "��ʱȴ���Ǳ��޿ɱܣ�\n" NOR;
			
                if (ap + random(ap) > dp)
     	  	{
     	 	      count = ap / 10;
     	 	 	    msg += HIR "$n" HIR "��$N" HIR "����Ѹ��֮����һʱ��֪����"
     	 	 	    	    "�������ֵ���������������\n" NOR;
     	 	 	} else
     	 	 	{
     	 	 	    msg += HIC "$n" HIC "��$N" HIC "����Ѹ��֮�������ѷ�������"
     	 	 	    	    "æ��������С�ĵֵ���\n" NOR;
     	 	 	    count = 0;
     	 		}
     	 			message_combatd(msg, me, target);
     	 			me->add_temp("apply/attack", count);
     	 			me->add("neili", -200);
     	 				for (i = 0; i < 8; i++)
     	 				{
     	 			    if (! me->is_fighting(target))
     	 			   		break;
     	 			    if (random(5) < 2 && ! target->is_busy())
     	 			    			target->start_busy(1);
     	 			    COMBAT_D->do_attack(me, target, 0, 0);
     	 			  }
     	 		me->start_busy(3 + random(3));
     	 		me->add_temp("apply/attack", -count);
     	  	return 1;
      }
}
}
