 // sandou ��������

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"��������"NOR;}

int perform(object me, object target)
{
      int lv,ap,dp,fp,pp,damage;
	  string msg;
      object weapon;

      weapon = me->query_temp("weapon");
      lv = me->query_skill("yinshe-bianfa",1);
 
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target) )
            return notify_fail("������������ֻ����ս���жԶ���ʹ�á�\n");

      if(!weapon
       || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "yinshe-bianfa")
            return notify_fail("������û�бޣ��޷�ʹ�á�������������\n");             

      if((int)me->query_skill("yinshe-bianfa",1) < 200 )
            return notify_fail("������߱޷�������죬����ʹ�á�������������\n");

        if((int)me->query("neili") < 500 )
            return notify_fail("�������̫�٣�����ʹ�á�������������\n");
      
      message_vision(HIY"\n$N�����������б��ӣ�"+weapon->query("name")+HIY+"ѭ�Ź����;����$nϮȥ��\n"NOR, me,target);
	    ap = me->query_skill("whip");
        dp = target->query_skill("dodge",1);
        fp = target->query_skill("force",1);
        pp = target->query_skill("parry",1);

		 msg = HIM "$N" HIM "������ȫ���˵��˱��ϣ�����һ�ޣ���ͷֱ�顣\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "б��������\n" NOR;
        else
        {
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70 + random(10),
                                           HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"
                                           HIR "��һ�޳��Ѫ��ģ�����������ˡ�\n" NOR);
        }

        msg += HIM "\n$N" HIM "һ������" + weapon->name() + HIM "�������볤���۾��Ƶģ���ת����$n�����˷�����˼��\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "����ӱ���Խ����\n" NOR;
        else
        {
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(10),
                                           HIR "�������Ƶ���켰��$n" HIR "�������ü���"
                                           "���мܣ�ֻ��$N" HIR "�����ӹ���$n"
                                           HIR "������ʱ��Ѫ���죡\n" NOR);
        }

        msg += HIM "\n$N" HIM "�ٶ��˶�����"+ weapon->name()+ HIM "ֱ��$n���ģ��ٶ�֮�죬��λ֮׼����������δ�š�\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "���ڿ��У��������У�ֻ�ܻӳ�һ�У�������$N"
                       CYN "���ϣ���һ������ƮȻ��ȥ��\n" NOR;
        else
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(10),
                                           HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
                                           HIR "�˱޳����$n" HIR "�����Һ�����Ѫ���·ɽ���\n" NOR);
        }

		me->add("neili", -300);
        me->start_busy(3);
        message_combatd(msg, me, target);

      return 1;
}
