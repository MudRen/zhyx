// wanli.c �������
// updated by kasumi 2007.4.5
// ��������pfm�������𼶷�����


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object  weapon;
	      int     damage;
	      string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp,n,i;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("never-defeated", 1) < 320)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ��������\n");
        /*
        if (((int)me->query_skill("count", 1) > 1) && (me->query("reborn")))
		return notify_fail("������ķ����ң��޴�ʹ��������\n");
        */	                        
        if ((int)me->query("neili", 1) < 1000)
		return notify_fail("����������̫��������ʹ��������\n");
			
        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("������ֱֳ��в���ʩչ������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("never-defeated", 1) * 3 / 2 + me->query_skill("martial-cognize", 1) + me->query_skill("dodge", 1) * 3 / 4;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);
        
        damage = (int) me->query_skill("never-defeated", 1);
        
        n=1+4;      
        
        for (i = 1; i < n+1; i++)        
        {
        	 if (! me->is_fighting(target))
                        break; 
           message_sort(HIC "$N" HIC "����" + weapon->name() + HIC "��һ"
                            "ȦȦ�Ļ���$n" HIC "����$p" HIC "���ڵ��У�\n" NOR, me, target);   
        	 damage=damage*i;        	 
           if (ap * 3 / 5 + random(ap * 2) > dp)
            {	
               if (arrayp(limbs = target->query("limbs")))
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "Ҫ��";
                pmsg = HIR "$n"HIR"��æ��Ų������Ȼ�������ꡱһ����" + weapon->name() +
		                   HIR "���û���$p" HIR "��" + limb + "��$p"
		                   HIR "һ���ҽУ�����������\n" NOR;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                message_sort(msg, me, target);
                
	          } else 
	          {		
	          	message_sort(CYN "����$p" CYN "������$P"
                       CYN "�ı仯�����в��У�û���ܵ��κ��˺���\n"NOR, me, target);         
	          }
	          
        }
        me->add("neili", -100*n);
        me->start_busy(2+random(5));

	return 1;
}
