#include <ansi.h>
#include <combat.h>

#define JQJY "��" HIB "����"HIW"����" NOR "��"
#define JQ "��" HIR "����" NOR "��"
#define JY "��" RED "����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = (int)me->query_skill("yinyang-ren", 1), i;
        string type1, type2, msg, nextmsg, edmsg,name;
        object weapon1, weapon2, equipment;
        int ap, dp, damage, j, count;

        if (me->query("dex") < 54)                
        return notify_fail("���������̫�ͣ�����ʩչ��" JQJY "��\n");

        if (me->query_skill("yinyang-ren", 1) < 450)
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(JQJY "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ������������ʩչ" JQJY "��\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");

        type1 = weapon1->query("skill_type");
        type2 = weapon2->query("skill_type");

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" JQJY "��\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("��û��ͬʱװ������������ʩչ" JQJY "��\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
           || me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("��û�м��������У�����ʩչ" JQJY "��\n");

    if ((int)me->query_skill("yinyang-ren", 1) < 800)
        return notify_fail("���������е���Ϊ������������������"JQJY"��\n");

    if ((int)me->query_skill("fenxin-jue", 1) < 500)
        return notify_fail("������ľ�����Ϊ������������������"JQJY"��\n");

    if (me->query("max_neili") < 10000)
        return notify_fail("���������Ϊ��������"JQJY"���裡\n");

    if (me->query("neili") < 2000)
        return notify_fail("���������������"JQJY"���裡\n");

    if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
    
  
    msg =WHT "$N���ձ��󣬵�����ǰ��������" YEL "������Ͷֹ˼�ż������������Ÿ������Ժᵶ����Ц��ȥ���ε������أ���" WHT "��\n"
                     "$n���룬��ʫ�����س������˿���������Ӧ�ò����Ǳ����޳�֮ͽ,���Ƿ��ɵľ��裬��ʱ�Ż��󿪡�\n"
                     "$N������תʹ����"NOR""JQJY"֮"JY""WHT"ʽ��ɲ�Ǽ���������ܲ���\n"
                     "$n�����༸��ֹͣ������������������$N��$N�������ܿ�����ֻ���������ѵ�" RED "���塿" WHT "��\n"NOR;

        ap = me->query_skill("yinyang-ren", 1) + me->query_skill("blade") + me->query_skill("sword") + me->query_skill("force"); 
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap * 3 / 5 + random(ap) > dp)
        {
        	 me->add("neili",-800);
            damage = ap*2 + random(ap)*2;
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
              BLU "$nû�뵽$N��ͻȻ����͵Ϯ��������ҡ�$N����"+weapon1->name()+
              RED "��ͬ��ǧ������������壬��$n���޿ɱܣ�\n" NOR);  
			
			   if (objectp(equipment = target->query_temp("weapon")))
			   {
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "���ϡ���һ�����죬$n" HIR "��"
										"�ֵ�" + name + HIR "��$N" HIR "������ɻ���"
										"������䣬������ؽ��ǡ�\n" NOR;  			 
                           }
        } else
        {
           me->add("neili",-500);
            msg += HIG "Ȼ��$n" HIG "ʶ�ô�������������׼������$N" HIG
            "�Ĺ���һһ���⡣\n" NOR;
        } 
         message_vision(msg, me, target);
  
        nextmsg =HIM "$NĿ����ͣ��������" HIC "�������䣬��Ϊ���ֱ�������������ϵر�˫�ɿͣ��ϳἸ�غ��\n"
                                 "����Ȥ�����࣬���и��гն�Ů����Ӧ�����������ƣ�ǧɽĺѩ��ֻӰΪ˭ȥ����" HIM "\n"
                                 "�������ڣ����������ء�$n�뵽�Լ��İ��ˣ��е�ͬ����������ǰһ����׼������$N��\n"
                                 "" HIG "ͻȻ$N����һתգ�ۼ�ʹ�������е��ռ�����----"NOR""JQJY""HIM"֮"NOR""JQ"ʽ��\n"
                                 "" HIG "$N����ӨȻ�й⣬�ƺ�������" HIR "�����顿" HIG "�ľ��硣\n"
                                 "$N����" + weapon2->name() + "����������Ӱ����$n��\n";
                
        if (ap * 3 / 4 + random(ap) > dp)
        {
             // ת������
                weapon1->move(me, 1);
                weapon2->wield();

        	 me->add("neili",-800);
            damage += random(ap) ;
            nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
              HIY "$nֻ�������塹���˲�ǳ��$N��ͬ����һ�㣬�Ʊ�Ҫȡ$n������\n" NOR);    
                	
	      // ת�ƻس�ʼ״̬
                weapon2->move(me, 1);
                weapon1->wield();
                me->set_temp("handing", weapon2);
								
			if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "������žž����һ����죬$n" HIR "��"
										"�ŵ�" + name + HIR "��$N" HIR "������ɻ���"
										"������䣬������ؽ��ǡ�\n" NOR; 
			}
			if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "������žž����һ����죬$n" HIR "��"
										"�ŵ�" + name + HIR "��$N" HIR "������ɻ���"
										"������䣬������ؽ��ǡ�\n" NOR;   
			}
        } else
        {
           me->add("neili", -500);
            nextmsg += HIG "$n��֪���˱����޳ܣ����к��ţ���$N" HIG
            "�Ĺ���һһ���⡣\n" NOR;
        }
                message_vision(nextmsg, me, target);



       edmsg = HIW "$N����Ʊ���ʶ�ƣ�������������»�ڣ���������" + weapon1->name() + HIW "���һ��"
              "��������������ʩ������ʱ�����㣬����ҹ�ɻ��գ�����ǵ�����$n��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                edmsg += HIW "$n" HIW "ֻ���������⽣Ӱ���Լ���"
                       "�����ٸ��ۻ����ң��ĵ׺�����Ȼ������\n" NOR;
                count = ap / 6;
                me->set_temp("yinyang-ren/max_pfm", 1);
        } else
        {
                edmsg += HIG "$n" HIG "ͻȻ�����Լ����ܽԱ�����"
                      "��Ӱ����Χ����֪�����æС���мܡ�\n" NOR;
                count = ap / 12;
        }
        message_combatd(edmsg, me, target);

       me->add("neili", -600);
       me->add_temp("apply/attack", count);       
       me->add_temp("apply/damage", count * 1 / 3);

        for (j = 0; j < 6; j++)
       {
               if (! me->is_fighting(target))
                        break;
          COMBAT_D->do_attack(me, target, weapon1, 0);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count * 1 / 3);
     me->delete_temp("yinyang-ren/max_pfm");
        me->start_busy( 2 + random(7));      
        return 1;
}

                


