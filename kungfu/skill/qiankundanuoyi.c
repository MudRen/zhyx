// qingkundanuoyi.c Ǭ����Ų��
// Created by Lonely (06/11/2002)

#include <ansi.h>
#include <combat.h>
inherit SKILL;


int valid_enable(string usage) { return usage=="parry"; }

int valid_learn(object me)
{
   	if ((int)me->query("shen") < 0)
   		return notify_fail("���а��̫�أ��޷�����Ǭ����Ų�ơ�\n");
   		
        if (me->query("character") != "��������" || me->query("character")!="������˫" )
                return notify_fail("�����Բ���������������޷�����Ǭ����Ų�ơ�\n");

   	if (me->query("gender") == "����")
   		return notify_fail("�����һ�������������Ժ���ԭ����û������֮"
			"�����޷���������Ǭ�������仯֮����\n");

   	return 1;
}

int practice_skill(object me)
{
    	return notify_fail("Ǭ����Ų��ֻ��ѧϰ������\n");
}

int parry_action(object me, object target, object target_weapon, 
		 int attack_type, mapping action, string limb)
{
        object weapon, *enemy, vic;
        string msg;
        int pp, ap, i;

        if (me->query_condition("jiujian_qi_damage")) 
                return 0;

        if (! living(me)) return 0;

        if (target_weapon)
        	ap = target->query_skill(target_weapon->query("skill_type"));
        else ap = target->query_skill("force");

        pp = me->query_skill("parry");
        if (random(pp) < ap / 2) return 0;

        msg = "\n" + action["action"] + "\n";
        if (target_weapon)   
        	msg = replace_string(msg, "$w", target_weapon->query("name"));
        	
        msg = replace_string(msg ,"$l", limb);
        enemy = me->query_enemy();
        
        if (! enemy || ! arrayp(enemy) || sizeof(enemy) < 1) 
        	return 0;

	weapon = me->query_temp("weapon");         
        i = sizeof(enemy);
        if (i == 1)       
        {
        	if ((target_weapon && ! weapon) || (! target_weapon && weapon))
		{        	
                	msg += HIW "$n " HIW "�����һ��ʩչ��Ǭ����Ų�ơ��񼼣�$N" HIW "������������գ�\n" NOR;
                	message_combatd(msg, target, me);
                	return 1;
                }
                msg += HIW "$n" HIW "�����һ��ʩչ��Ǭ����Ų�ơ��񼼣���$N" HIW "����������Ų��ȥ��" NOR;
                message_combatd(msg, target, me); 
                COMBAT_D->do_attack1(me, target, weapon, 2, action, limb); 
                return 1;
        }
        else if (i > 2)
        {
        	if (member_array(target, enemy) != -1) 
        		enemy -= ({target});
        	vic = enemy[random(sizeof(enemy))];
                msg += HIW "$n" HIW "�����һ��ʩչ��Ǭ����Ų�ơ��񼼣���$N" HIW "��������������" + 
                       vic->query("name") + HIW "��\n" NOR;
                message_combatd(msg, target, me);
                
                if (! vic->is_busy())
                	vic->start_busy(1);
                	
                COMBAT_D->do_attack1(target, vic, target_weapon, 2, action, limb);
                return 1;
        }
}

string perform_action_file(string action) 
{
        return __DIR__"qiankundanuoyi/" + action; 
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("qiankundanuoyi", 1);
        layer = lvl / 50;
        if (layer > 7) layer = 7;

        if (! layer)
        {
                tell_object(me, HIM "��Ǳ������Ǭ����Ų"
                            "���ķ�����������\n" NOR);
        } else
        if ((lvl % 50) == 0)
        {
                tell_object(me, HIM "���������˵�" + chinese_number(layer) +
                            "���Ǭ����Ų���ķ���\n" NOR);
        } else
                tell_object(me, HIM "��Ե�" + chinese_number(layer) +
                            "���Ǭ����Ų���ķ��ּ�����һ���˽⡣\n" NOR);

        if (lvl > me->query_skill("force") * 2 / 3)
        {
                if (lvl < me->query_skill("force") * 2 / 3 + 10)
                {
                        tell_object(me, HIG "�������Ϣһ�����ң�����ʱ��ʱ"
                                        "�ȣ����ɵô��һ����\n����Ī������"
                                        "����ħ������Խ��Խ�Ǻ��䣬��Ϊ����"
                                        "��\n" NOR);

                        message("vision", HIG + me->name() + HIG "����ɫ����"
                                          "���̣���ò�ͣ��ֻ�ǻ����������"
                                          "��ʮ��ʹ�ࡣ\n" NOR,
                                          environment(me), ({ me }));
                        return;
                }

                tell_object(me, HIB "���Ȼ���õ�������һ���⣬��ʱ����֫"
                                "����һ���ú����ޱȣ��̲�ס����������\n" NOR);

                message("vision", HIB + me->name() + HIB "��Ȼһ������ɫ��Ȼ"
                                  "��òҰף���Ȼ������һ��������������ֹ��"
                                  "\n" NOR, environment(me), ({ me }));
        } else

        if (lvl < 350 && (lvl * 20 + 4000) > me->query("max_neili"))
        {
                if ((lvl * 20 + 4000) < me->query("max_neili") + 200)
                {
                        tell_object(me, HIR "��������ת��һ����Ϣ��һʱ������"
                              "�����ã��������ǲ�ҪóȻ������Ų���񹦡�\n" NOR);
                        return;
                }

                tell_object(me, HIR "��������ת��һ����Ϣ����Ȼ����һ����"
                      "��Ȼת����������ʱ���н�ʹ���������˼�����Ѫ��\n" NOR);
                message("vision", HIR + me->name() + HIR "��ɫ��Ȼ"
                        "һ�䣬Ż��������Ѫ����Ŀ���ġ�\n" NOR,
                        environment(me), ({ me }));
        } else
                return;
}
