//updated by kasumi 
#include <ansi.h>
#include <combat.h>

#define LONG "��" HIC "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;
        int ap, dp,i;
        int damage,count;
        int neili, hit_point, time;


        if (! target) target = offensive_target(me);
		

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" LONG "��\n");

        if (me->query_skill("hanbing-zhenqi", 1) < 500)
                return notify_fail("��ĺ���������Ϊ����������ʩչ" LONG "��\n");

        if (me->query_skill("wuyue-shenjian", 1) < 800)
                return notify_fail("�����������Ϊ����������ʩչ" LONG "��\n");

        if (! me->query("reborn"))         
                return notify_fail("����δת���������޷����˾��У�\n"); 
				
	if ((int)me->query("max_neili") < 6000)
                return notify_fail("���������Ϊ���㣬����ʩչ" LONG "��\n");

        if (me->query("neili") < 1200)
                return notify_fail("�����������������ʩչ" LONG "��\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("��û�м��������񽣣�����ʩչ" LONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");



		ap = me->query_skill("sword") + me->query_skill("force");
		dp = target->query_skill("dodge",1) + target->query_skill("force");

           
		 msg = HIW "\n����$N" HIW "����" + weapon->name() + HIW 
                      "�԰���к��������������ֱ������һ������һ�㣬��"
                      "�������񽣵ľ��衸" HIY "��������" HIW "����һ"
                      "��������$N" HIW "ʹ�������ߣ�����������Ȼ������$n" 
                      HIW "��\n" NOR;
        
        message_sort(msg, me, target);

        if (ap * 2/ 3 + random(ap) > dp)
        {
		    damage = ap * 3 + random(ap*2);
            target->receive_damage("qi", damage,me);
            target->receive_wound("qi", damage*4/5, me);
			me->add("neili", -300);        
	        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	       	msg = "($n"+str+")\n";       
               
        } else
        {
                me->add("neili", -100);               
                msg = CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                      CYN "$N" CYN "�������͵�һ�С�\n" NOR;
        }
        message_vision(msg, me, target);    
	  	   
	   if (me->query_skill("hanbing-zhenqi", 1) > 500 && me->query_skill_mapped("force") == "hanbing-zhenqi"){
	   
			msg = HIW "ֻ��$N"HIW"���������������������£�����������Ϊ������������������$n" HIW "��\n" NOR;
			message_combatd(msg, me, target);
			for (i = 0; i < 6; i++){
					damage = ap*2/3 + random(ap)/2;  
					msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80+random(30),
                                           HIR "$n" HIR "ֻ����ǰһ�ڣ��������������������Ѷ�����Ѫ����ֹ��Ѫ������\n" NOR);
					me->add("neili", -150);
					message_combatd(msg, me, target);
			}
		}else{
			msg = HIW "ֻ��$N"HIW"���Ʋ���������" + weapon->name() + HIW "�����̻���������������$n" HIW "��\n" NOR;
			message_combatd(msg, me, target);
			count = me->query_skill("sword",1)*2/3;
           me->add_temp("apply/attack", count);
           me->add_temp("apply/damage", count/2);
		   for (i = 0; i < 12; i++)
      	   {
               	if (! me->is_fighting(target))
               	        break;
				 if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1); 
                COMBAT_D->do_attack(me, target, weapon, 0);
			    me->add("neili", -50);
           }
		   me->add_temp("apply/attack", -count);
           me->add_temp("apply/damage", -count/2);
		}
		

	   
	    me->start_busy(2+random(4));

        return 1;
}