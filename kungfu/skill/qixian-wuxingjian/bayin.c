//by gentl
//˵����÷ׯ�������ν�֮�ռ����У��򾫲������������Ч��ʹ�ô��������Բ�С��40.

#include <ansi.h>
#include <combat.h>

#define BAYIN "��" HIW "���Ұ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int ap, an, dn, dp, wp;
        int count;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }


        if (! me->is_fighting(target))
                return notify_fail(BAYIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("qixian-wuxingjian", 1);
		
        weapon = me->query_temp("weapon");		

        if (me->query_skill("force") < 1200)
                return notify_fail("����ڹ�����Ϊ�����������޷�ʹ��" BAYIN "��\n");

        if (skill < 800)
                return notify_fail("����������ν���Ϊ���ޣ������޷�ʹ��" BAYIN "��\n");

        if ((int)me->query_skill("xuantian-wujigong", 1) < 500)
                return notify_fail("��������޼�����Ϊ���ޣ������޷�ʹ��" BAYIN "��\n");

        if (me->query("neili") < 2500)
                return notify_fail("��������������޷�����" BAYIN "��\n");
                
        if ( me->query("int") < 40 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷����˾��У�\n");                   

        if (weapon && weapon->query("skill_type") != "sword")
                return notify_fail("�㲻��ʹ�����ֱ���ʩչ" BAYIN "��\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("������û��׼��ʹ���������ν����޷�ʩչ" BAYIN "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("������û��׼��ʹ���������ν����޷�ʩչ" BAYIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if (weapon)
        {
                msg = HIW "ֻ��$N" HIW "˫Ŀ΢�գ�������" + weapon->name() +
                      HIW "�����Ღ������ʱֻ������࣡��ƿ�֮����������"
                      "��������\n�����ν������������ֱ��$n" HIW "��ȥ�������ռ�����֮���Ұ�����\n" NOR;
        } else
        {
                msg = HIW "ֻ��$N" HIW "˫Ŀ΢�գ�˫��������Ū����Ȼ��ʮָһ"
                      "�����ţ���ʱֻ������࣡��ƿ�֮��������\n�ϣ�������"
                      "�����ν������������ֱ��$n" HIW "��ȥ�������ռ�����֮���Ұ�����\n" NOR;
        }
        
        msg += MAG "            ���д����������ǵ�����         \n"
               HIW " ����������           ��           ���������� \n"
               HIC "    ����������        ��        ����������\n"
               HIG "       ����������     ��     ����������\n"
               HIM "          ����������  ��  ����������\n"  NOR;	

        ap = skill + me->query_skill("force", 1) + me->query_skill("unarmed", 1) + me->query_skill("sword", 1) + me->query_skill("tanqin-jifa", 1);
        an = me->query("max_neili") / 20 + me->query_skill("tanqin-jifa", 1);
        dn = target->query("max_neili") / 20 + target->query_skill("tanqin-jifa", 1);
        dp = target->query_skill("force", 1) + target->query_skill("dodge") + target->query_skill("parry");

        if (an / 2 + random(an) > dn)
        {
                msg += HIR "һ����������������������ɱ������ս��ʿ�������ɣ���" HIR "$N" HIR "������й����\n" NOR;
                count = ap / 5;                
                ap += ap / 4;
        }

        me->add("neili", -250);
        damage = ap * 3 / 2 + random(ap * 3/2);

//��һ��
	    msg += HIW "\n$N" HIW "����������������������֮�й�ע�ϳ��������������ҵ�������\n" NOR;        
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ����$N" HIR "������������"
                       "������һ��������͸��Ĥ������һƬ���ҡ�\n";       	
                       
            target->receive_damage("jing", damage * 5 / 4, me);
            target->receive_wound("jing", damage, me);
            if (an / 3 + random(an) > dn && !userp(target))
            	{       
            		msg += HBWHT "ֻ��" HBWHT "$n" HBWHT "����������һ���������㲻֪������Ϊ�������ơ�\n" NOR;
            		 target->start_busy(3 + random(ap / 100));  

            	}
        } else
        {
                msg += CYN "����$n" CYN "��æ���������Ŭ��ʹ�Լ�"
                       "���������ĸ��ţ����ڻ�������һ�С�\n" NOR;
        }
        
        
//�ڶ���        
	    msg += HIG "\n$N" HIG "ʮָ���죬����Խ��Խ�����������ĵ�֮���罣������" HIG "$n" HIG "������\n" NOR;        
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ����$N" HIR "������������"
                       "������һ��������͸��Ĥ������һƬ���ҡ�\n";        	
                       
            target->receive_damage("jing", damage * 4 / 3, me);
            target->receive_wound("jing", damage, me);
                if (objectp(weapon = target->query_temp("weapon"))
                   && weapon->query("stable", 1) < 100
                   && ap / 3 + random(ap) > dp && !userp(target))
                  {
                        wp = weapon->name();
                        msg += HBGRN "ֻ�����ϡ���һ�����죬$n" HBGRN "��"
                               "�е�" + wp + HBGRN "��$N" HBGRN "��������"
                               "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR;
                        me->add("neili", -500);
                        weapon->set("consistence", 0);
                        weapon->move(environment(target));
                 }
        } else
        {
                msg += CYN "����$n" CYN "��æ���������Ŭ��ʹ�Լ�"
                       "���������ĸ��ţ����ڻ�������һ�С�\n" NOR;
        }        
             
//������   
	    msg += HIM "\nʱ���������ͬ�죬���ɰ˵�����ǰ��һ����׷������ɼ���ֱȡ" HIM "$n" HIM "��ȥ��\n" NOR;        
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ����$N" HIR "������������"
                       "������һ��������͸��Ĥ������һƬ���ҡ�\n";    
                       
            target->receive_damage("jing", damage * 3 / 2, me);
            target->receive_wound("jing", damage, me);
            if (an / 3 + random(an) > dn && !userp(target))
            	{       
                 target->set("neili", 0);
                 msg += HBMAG "$n" HBMAG "�������ƣ��ƺ�һ�������˼������پ���Ϣ��ɢ��\n" NOR;
                 
            	}
        } else
         {
                msg += CYN "����$n" CYN "��æ���������Ŭ��ʹ�Լ�"
                       "���������ĸ��ţ����ڻ�������һ�С�\n" NOR;
         }   
                
        me->add("neili", -1000);
        me->start_busy(3 + random(4));
        message_combatd(msg, me, target);
        return 1;		 
        
        
}        
        
        
