#include <ansi.h>
#include <combat.h>

#define YH "��" HIR "�ƻ��" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        string msg,dodge_str,parry_str;
        int ap, dp, damage;
        int i,skill,times;
		object weapon;	

        me = this_player();  

		skill = (int) me->query_skill("jiuyin-shengong",1);
		times = 4 + skill / 80;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YH "ֻ����ս���жԶ���ʹ�á�\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 400)
                return notify_fail("������񹦲�����죬����ʩչ" YH "��\n");
 
        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("���ڹ���������������ʩչ" YH "��\n");   

        if (me->query_skill_mapped("force") != "jiuyin-shengong")
                return notify_fail("��û�м���������Ϊ�ڹ�������ʩչ" YH "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����ڵ���������������ʩչ" YH "��\n");

		
	    if(me->query_temp("no_yihun"))
                return notify_fail("����Ϣδ�ȣ��޷�ʹ��" YH "��\n");     

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
                            
        msg = HIM "\n$N" HIM "��Ȼ���Хһ����ʩչ���������еġ�" HIR "�ƻ��" HIM"����"
              "ֻ��$N" HIM "������ʽǧ��ٹ֡��仯��ˣ�����ϲŭ���֣���״�ٳ���\n" NOR;

		dodge_str=target->query_skill_mapped("dodge");
		parry_str=target->query_skill_mapped("parry");
        ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("force", 1);
        dp = target->query_skill("jiuyin-shengong", 1) + target->query_skill("force", 1);

        if (ap * 11 / 20 + random(ap) > dp)
        {
             msg += HIG "$n" HIG "����׼��ȡЦ$N��ȴ��֪������ѧ��$N�ı��顣" HIG
                    "$N��Ȼ�������Լ������Ķ�����$n�������Լ������ƵĹ�������������Խ��Խ�أ�\n" NOR; 
			 message_sort(msg, me, target);			
		 
			 target->map_skill("dodge", 0);
			 target->map_skill("parry", 0);
            
		     for (i = 0; i < times; i++)
		     {
				       if (! me->is_fighting(target))
                        break;
                      
					   if (objectp(weapon = target->query_temp("weapon")))
			               COMBAT_D->do_attack(target, target, weapon, 0);
					   else COMBAT_D->do_attack(target, target, 0, 0);
		      }
	
		    target->map_skill("dodge", dodge_str);
			 target->map_skill("parry", parry_str);
		 
            
			me->start_busy(2 + random(4));
             me->add("neili", -600);
            

        } else
        {
              msg += NOR + CYN "$n" NOR + CYN "ŭ�ȵ��������������������Ի��ң�������Ȼ�䣬��ʽ���죬"
                     "����$N" NOR + CYN "������ȥ��\n" NOR;
			  message_sort(msg, me, target);

              me->add("neili", -200);
              me->start_busy(1 + random(2));
        }

		me->set_temp("no_yihun",1);
		call_out("yihun_ok", 3 + random(2), me);    

        return 1;
}

void yihun_ok(object me)
{
	if (!me) return;
	me->delete_temp("no_yihun");
}