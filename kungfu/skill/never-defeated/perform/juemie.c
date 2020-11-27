// juemi.c ��ؾ���
// updated by kasumi 2007/4/4
// ���ж��ֺ󣬽��Ͷ��ֵ�jifa force��dodge��parry
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
string attack1(object me, object target, int damage);
 
int perform(object me, object target)
{
  object weapon;
	string msg;
	int ap, dp;
  int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ؾ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("never-defeated", 1) < 250)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ����ؾ���\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("������ֱֳ��в���ʩչ��ؾ���\n");

        if (me->query("neili") < 500)
                return notify_fail("�����������������ʹ����ؾ���\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
              
       if (target->query_temp("never_juemie"))
                return notify_fail("�Է������Ѿ������������ŵ������ɡ�\n");
              
              
  message_vision(HIC "$N" HIC "������˼�������Ȼһ�����е�" + weapon->name() +
                 HIC "��Ѹ���ޱȵ�ɨ��$n" HIC "���仯����֮��������˼�飡\n"
                       NOR, me, target);	
 
	ap = me->query_skill("never-defeated", 1);
	dp = target->query_skill("dodge",1); 
	
        if (ap * 2 / 3 + random(ap*2) > dp)
        {        	
           damage = ap*5 + random(ap*3);
           me->start_busy(3+random(3));
           me->add("neili", -400);
                
          msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   (: attack1, me, target, damage :));    
                        		
        } else
	      {
	       	msg = HIG "ֻ��$n" HIG "�������ţ�ֻ������һ�����Ͷ����$N"
	               HIG "��һ����\n"NOR;
	         me->start_busy(2+random(3));
           me->add("neili", -400);
	      }

	message_vision(msg, me, target);
	return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "��æ�񵲣�������һ��ʵ���ǹ���Ī"
                           "�⣬������ĥ��͸����ʱ����$P" HIR "���ش���\n" NOR;

        if (! target->query_temp("never_juemie"))
        {
                msg += HIM "$nֻ���û��������ϣ�ȫ�����������һ˿"
                       "˿Զ���Լ���ȥ������֮����\n" NOR;

                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("never_juemie", 1);
        }
        call_out("juemie_end", 15 + random(15), me, target);
        return msg;
}

void juemie_end(object me, object target)
{
        if (target && target->query_temp("never_juemie"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��������ɫ��"
                                        "��ת�죬�������ö��ˡ�\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("never_juemie");
        }
        return;
}