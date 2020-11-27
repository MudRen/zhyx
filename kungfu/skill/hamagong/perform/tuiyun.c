// tui.c ����ʽ֮��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void yun_remove(object me,object target); 
int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦������ʽ��֮��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("���ֱֳ������޷�ʩչ��󡹦�ľ�����\n");
	         
	      if ((int)me->query_temp("tuitimes"))
                return notify_fail("���Ѿ������󡹦�ġ�����ʽ���ˡ�\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 280)
                return notify_fail("��ĸ�󡹦��Ϊ�����������ʹ�á�����ʽ����\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("���������Ϊ��������޷�ʩչ������ʽ����\n");

        if (me->query("neili") < 600)
                return notify_fail("��������������޷����á�����ʽ����\n");

        msg = HIY "$N" HIY "��������һ�·���ſ�ڵ��ϣ����á���һ����У�����������һ�ģ����ƴ���......\n" NOR;   
        me->set_temp("tuitimes", 1);
		me->set("qi",me->query("qi")*2);
		me->add_temp("apply/armor", skill*5);
        message_combatd(msg, me, target);
        me->start_busy(1+random(2));
		call_out("yun_remove", 60, me);    
        return 1;
}

void yun_remove(object me,object target) 
{
  string msg;
  int skill;
  skill = me->query_skill("hamagong", 1);
  if (!me) return;
  if ((int)me->query_temp("tuitimes"))
  {  
     msg = HIY "$N" HIY "�ĸ��������ʽ���˰��춼û�з�����й�ˡ�\n" NOR;  
     message_combatd(msg, me, target);	
     me->add_temp("apply/armor", -skill);	 
     me->delete_temp("tuitimes");
  }
  return;
}
