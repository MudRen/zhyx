#include <ansi.h>
#include <combat.h>

#define PO "��" HIY "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object anqi;
        int damage;
        string msg;
        int ap, dp, att;

        if (! target) target = offensive_target(me);

//        if (userp(me) && ! me->query("can_perform/sixiang-shengong/jing"))
//                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "ֻ����ս���жԶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail(PO "ֻ�ܿ���ʩչ��\n");

        if (! objectp(anqi = me->query_temp("handing"))
           || (string)anqi->query("skill_type") != "throwing")
                return notify_fail("���������в�û�����Ű�����\n");

        if (anqi->query_amount() < 5) 
                return notify_fail("���������а�������, �޷�����PO��\n");
     
        if (me->query_skill_mapped("throwing") != "sixiang-shengong") 
                return notify_fail("��û�м��������񹦣�����ʩչ" PO "��\n");

        if ((int)me->query_skill("sixiang-shengong", 1) < 10)
                return notify_fail("��İ׻�������ǿ��������ʩչ" PO "��\n");

        if ((int)me->query_skill("force") < 15)
                return notify_fail("����ڹ���򲻹�������ʩչ" PO "��\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������㣬����ʩչ" PO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "ͻȻֻ��$N" HIY "�ȵ�����$n" HIY "����һ������������"
              "˵�������������£���׶�ʱ�ܳ�����׹⣬����·��$n" HIY
              "ֱ�ֶ�ȥ��\n" NOR;

        ap = me->query_str() * 5 + 
             me->query_skill("throwing", 1) +
             me->query_skill("unarmed", 1);

        dp = target->query_str() * 5 + 
             target->query_skill("throwing", 1) +
             target->query_skill("unarmed");

        att = (int)me->query_skill("sixiang-shengong", 1);

	damage = anqi->query("weapon_prop/damage") + ap/5;

        me->start_busy(3);

        me->add("neili", -150);

        if (anqi->query_amount() > 5) anqi->add_amount(-5);

        if (ap / 2 + random(ap) > dp)
        { 
                if ( att < 100)
                     { msg += HIW + "$n��״��æ���ܣ����������ķ�" + anqi->name() + HIW ","
                              HIW + "��֪����֮�ƾ�������һʵ��$n�������ܣ������һ�����˸����С�" NOR;
                                    "�ҽ�һ����Ѫ����ע��\n" NOR;
                        damage += 50;
                      }
 
                if ( att >= 100 && att < 120 ) 
                      { msg += HIW + "$n��״��æ���ܣ��ۿ�����������" + anqi->name() + HIW ","
                              HIW + "��֪����֮�ƾ���������ʵ��$n�������ܣ�������������˸����У�"
                                    "ð������Ѫ����\n" NOR;
                        damage += 100;
                       }
  
                if ( att >= 120 && att < 140 ) 
                      { msg += HIW + "$n��״��æ���ܣ�������������" + anqi->name() + HIW ","
                               HIW + "��֪����֮�ƾ���������ʵ��$n�������ܣ��������ǣ�"
                                    "�ܳ�����Ѫ����\n" NOR;
                            damage += 150;
                       }

                if ( att >= 140 && att < 160 ) 
                      { msg += HIW + "$n��״��æ���ܣ���ǿ��������һ��" + anqi->name() + HIW ","
                              HIW + "��֪����֮�ƾ���һ����ʵ��$n�������ܣ��������ķ�������ţ�"
                                    "�������һ����Ѫ��\n" NOR;
                            damage += 200;
                       }


                if ( att >= 160 && att < 180 )
                       { msg += HIW + "$n�ѿ��������ƣ����巢" + anqi->name() + HIW "��������,"
                              HIW + "��ʱѪ���ɡ�\n" NOR;
                            damage += 250;
                       }

                if ( att >= 180 ) 
                       {msg += HIW + "ֻ���巢" + anqi->name() + HIW "������󣬾��ֳ�����֮��"
                              HIW + "$n����Ŀ�ɿڴ�����" + anqi->name() + HIW "���ش�����\n" NOR;
                            damage += 300;
                       }
		target->receive_damage("qi", damage, me);
        } else
        {
                msg += HIY "����$p" HIY "������$P" HIY "����ʽ������"
                       "���������ѳ��������ֵķ�Χ��\n" NOR;
                damage = 10;
        }
        
	message_combatd(msg, me, target);
        return 1;
}