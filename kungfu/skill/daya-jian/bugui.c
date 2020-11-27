
#include <ansi.h>

inherit F_SSERVER;
#define bugui "��" HIW "����ʽ" NOR "��"

int perform(object me, object target)
{
        string msg,str,force;
        object weapon,weapon2;
        int n,count;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

		if (userp(me) && ! me->query("can_perform/daya-jian/bugui"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        skill = me->query_skill("daya-jian", 1);

        if (! me->is_fighting(target))
                return notify_fail(bugui"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("sword") != "daya-jian") 
                return notify_fail("��û���ô��Ž������޷�ʹ�ò���ʽ���У�\n");

        if (skill < 250)
                return notify_fail("��Ĵ��Ž����ȼ�������������������\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
		
		if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
        ap = me->query_skill("sword") + me->query_skill("force") + me->query_skill("dodge") + me->query_skill("parry") + me->query_skill("tanqin-jifa")/2 + me->query_skill("chess", 1)/2;
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("sword", 1); 
        dp = dp * 3/2 + target->query_skill("tanqin-jifa")/2 + target->query_skill("chess", 1)/2;

        damage = ap + random(ap);         
        

        msg = HIC "\n$N" HIC "���д���ھ�����������" NOR YEL "���ŹŽ���" HIC "��ʱ���������쾡�£�\n" +
              weapon->name() + HIC "������˸���û�Ϊ���콣Ӱ�������ĵ�֮ʽ����$n" HIC "��ȥ��\n" NOR;

        message_combatd(msg, me, target);

        n = 12;
		if (n>12)
			n=12;

                count = ap / 6;
		me->add_temp("apply/attack", count);
		me->add_temp("apply/damage", me->query_skill("tanqin-jifa", 1) / 3);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(2)==1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
		me->add_temp("apply/attack", -count);
		me->add_temp("apply/damage", -me->query_skill("tanqin-jifa", 1) / 3);

		if ((int)target->query("qi")> 0&& me->is_fighting(target))
		{
 
              force = me->query_skill_mapped("force");
              if (!stringp(force)) force = "force";
        
        msg = HIM "\n$N" HIM "һ���֮�󣬺�Ȼ��ʽһ�������μ��ˣ�������������֮�⡣\n"
              "$N" HIM "�̽�������˫Ŀ����$n" HIM "��"
              "$n" HIM "����Ϭ����Ŀ���ŵ�һ���£���ͷһ�����......\n"
              "����$N" HIM "���һ��:\n"
              HIW "����������ˮ����׳ʿһȥ�ⲻ����!\n"
              HIM "�����л�����ǿ����" HIR + to_chinese(force)+ HIM"��"
              "ֻ��$N" HIM "�˽���һ������$n" HIM "������" NOR CYN "���ŹŽ���" HIM "��" HIW "������ʽ��" HIM"����\n\n" NOR;

           weapon2 = target->query_temp("weapon");
        
            if (ap * 2/3 + random(ap) > dp || !living(target))
             {

				 if (me->query_skill_mapped("tanqin-jifa") == "tieqin-yin")
				 {
					  msg += HIR "$n" HIR "ֻ������һ������Ϣ���裬��������������\n" NOR;
					   target->add("neili", -damage*3);
					  if (target->query("neili") < 0)
                        target->set("neili", 0);
				 }
				 else if (me->query_skill_mapped("tanqin-jifa") == "qiuyue-lai")
				 {
					 msg += HIR "$n" HIR "ֻ��һ���������Ķ�������ͷһ����Ѫ���������\n" NOR;					 
                     target->receive_wound("qi", damage*2, me);
	                 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	     msg += "($n"+str+")\n";					 
				 }
				 else if (me->query_skill_mapped("tanqin-jifa") == "jian-jia")
				 {
					  msg += HIR "$n" HIR "ֻ��һ�ɺ���͸�Ķ����������������죬�������ģ�\n" NOR;
					  target->receive_wound("jing", damage, me);					 
				 }
               
        } else
        {
                if (weapon2)
                        msg += CYN "$n" CYN "��$N" CYN "�������ͣ���������ֵ�������" + weapon2->name() + CYN "һ�����" + weapon->name() + CYN "�Ľ���\n"
                               CYN "$N" CYN "������һ����������ʽ����Ȼ��գ�\n" NOR;
                else
                        msg += CYN "$n" CYN "��$N" CYN "�������ͣ���������ֵ����������˫�Ʒ������$N" CYN "\n"
                               CYN "$N" CYN "������һ����������ʽ����Ȼ��գ���$n" CYN "Ҳ��$N" CYN "�����Ѫ��ӿ��\n" NOR;
        }
		  message_vision(msg, me, target);
		}

        me->start_busy(3 + random(3));
        
        me->add("neili", -400);
        return 1;
}


