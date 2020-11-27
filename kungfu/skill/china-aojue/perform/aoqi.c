#include <ansi.h>
#include <combat.h>

#define AOJUE "��" HIR "�����л�" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl, idle, i, count;

        if (userp(me) && ! me->query("can_perform/china-aojue/aoqi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(AOJUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("����ڹ���Ϊ����������ʩչ" AOJUE "��\n");

        if ((int)me->query("max_neili") < 6000)
                return notify_fail("���������Ϊ����������ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("china-aojue", 1) < 450)
                return notify_fail("���л�������򲻹�������ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("idle-force", 1) < 300)
                return notify_fail("�㷢���񹦵ȼ�����������ʩչ" AOJUE "��\n");

        if (me->query_skill_mapped("sword") != "china-aojue")
                return notify_fail("��û�м����л�����Ϊ����������ʩչ" AOJUE "��\n");

        if (me->query_skill_mapped("force") != "china-aojue")
                return notify_fail("��û�м����л�����Ϊ�ڹ�������ʩչ" AOJUE "��\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" AOJUE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();
        
        msg=HIG"$N" HIG"��" +wn+HIG"��أ�˫�ָ��ڱ�������������������ˣ����ǡ��л����������һʽ:\n\n"
            HIR"                         �������л���\n" NOR;

       message_combatd(msg, me, target);
                        
       msg = HIY "$N" HIY"һ�����ɣ�����˫�ƣ�����һ����"+wn+HIY"������ճ���\n"
                 "�漴$N"HIY"����һ�ģ�����"+wn+HIY"����֮�ϣ��������$n"HIY"�ؿڼ��̶�ȥ......\n"NOR;
       ap = me->query_skill("sword") + me->query_skill("force")+ me->query_skill("idle-force", 1) * 2;
       dp = target->query_skill("parry") + target->query_skill("dodge")+ target->query_skill("idle-force", 1) * 2;  
       
       if (ap * 4/ 5 + random(ap) > dp)
       	{
       		 damage = ap * 2 + random(ap);
             me->add("neili", -300);
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                        HIR "$n" HIR "���ֲ����������Ѵ��ض�������Ѫ����һ�ء�\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += CYN "$n" CYN"δ��ϸ�룬��æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);
        
        msg=HIY"������"+wn+HIY"�ɻ�$N"HIY"���У�$N"HIY"���������������ķ�������������\n"
        HIY"$n"HIY"ȫ�������ڽ���֮��......\n"NOR;
        message_combatd(msg, me, target);  
        
        count=ap/2;    

        me->add_temp("apply/attack", count);
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, i * 2 );
				 me->add("neili", -50);   
        }
        me->add_temp("apply/attack", -count);
        

        msg = HIR "\nͻȻ$N" HIR "������ģ�������ͣ�����"+wn+HIR"Ʈ�������ر���$n��\n" NOR;
        
        ap = me->query_skill("force",1) + me->query_skill("idle-force", 1);
        dp = target->query_skill("force",1) + target->query_skill("idle-force",1);   
         
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 4 + random(ap*2);                
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "���$n" HIR "�мܲ�������$N" HIR
                                           "һ�������ؿڣ������̶��������߹ǣ����"
                                           "һ�����Ѫ��\n" NOR);           

        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
			    me->add("neili", -50);
        }
        message_vision(msg, me, target);
        me->start_busy(3 + random(4));
        
        return 1;
}


