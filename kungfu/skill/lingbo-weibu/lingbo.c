// This program is a part of NITAN MudLIB
// ��busy�ˣ����ܽ��Է�����Чdodge���������貨��1000������busy����һ�������ܡ�

#include <ansi.h>
#include <combat.h>

#define LING "��" HIW "�����貨" NOR "��"

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);


int perform(object me, object target)
{
        string msg;
        int level, ap, dp, count, counta;
        int tm;
        
        if (! target) target = offensive_target(me); 
        if (! target || ! target->is_character() || ! me->is_fighting(target)) 
                return notify_fail("��һ��������ô��\n");

        if (userp(me) && ! me->query("can_perform/lingbo-weibu/ling"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if ( me->query_temp("no_lingbo") ) 
                return notify_fail("��ո�ʹ�ù������貨��������δƽ����\n" NOR);             

        if ((level = me->query_skill("lingbo-weibu", 1)) < 120)
                return notify_fail("����貨΢������������������ʩչ" LING "��\n" NOR);

        if ((int)me->query("neili") < 600)
                return notify_fail("�������������㣬����ʩչ" LING "��\n" NOR);


        if( me->query("gender") == "Ů��")
               msg = HIW "\n$N" HIW "�����������������������ʮ"
                     "���ԣ����貨΢����ͷ��βѸ���ޱȵ�����һ�Ρ�\n"
                     HIW"$N" HIW "�����������������ζ�ʱ��ӯ�ޱȣ�"
                     "΢���貨���������ң���ַ��ӵ����쾡����\n" NOR;

        else   msg = HIC "\n$N" HIC "�����������������������ʮ"
                     "���ԣ����貨΢����ͷ��βѸ���ޱȵ�����һ�Ρ�\n"
                     HIC"ֻ��$N" HIC "��̬Ʈ�ݣ�Ӱ���ҷɣ����ζ�ʱ��"
                     "ӯ�ޱȣ��������ң���ַ��ӵ����쾡����\n" NOR;

        message_combatd(msg, me, target);
        count = level / 2;
        counta = 4 - (int)level / 249;
        if (counta < 0) counta = 0;
        	  
	      ap = me->query_skill("dodge");
	      dp = target->query_skill("dodge",1);   // ���������������Ը�

                   
        if (ap / 2 + random(ap) > dp)
        {      
	              me->set_temp("no_lingbo",1);
                call_out("lingbo_ok", 3+random(3), me);       
                msg = HIW "$N���������·���$n������$N���貽ת�˸�ͷ���ۻ���\n" NOR;          
                if (! target->is_busy())
                  target->start_busy(3 + random(level / 100));
                if (! target->query_temp("lb_ling") && !userp(target))
                	{
                		msg += HIW "$n�ֽž�ȻҲ����ʹ���ˣ�\n" NOR;  
                		target->add_temp("apply/dodge", -count);    // ��һ����ֻ�ܳɹ���һ��
                		target->set_temp("lb_ling", 1);                	      
                	}
                	
                me->add("neili", -400);
                me->start_busy(counta);    // �貨΢����1000���Ժ󣬴��н�û��busy
        } else 
        {
                msg = HIG "����$n������$N���貽,��̬���ݵĶ��˹�ȥ\n" NOR;
                me->add("neili", -100);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;

}

void lingbo_ok(object me) {
  if (!me) return;
  me->delete_temp("no_lingbo");
}


