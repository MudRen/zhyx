// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dagou-bang.c

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
        "$p$W���𣬾������$P����ʽ���ò��־�һ��һ���������쳣��ȥ��ȫ�����������ϵ�֮����\n"
        "$P��Ծ��ܣ���֪$W��Ȼ��ת����$P�Ľ��֡�$Pһ�����ģ��н�Ծ����\n",
        "$p��������ӵأ�ֱ�����ء���һ��ȥ�ƹŹ֣����ɴ���$P$w��$P��һ����δʹ�㣬��֪�����æԾ����ܡ�\n",
        "$p���в�֧�������ƶ��Ų���ʹ�����⡹�־���ס$P$w���ơ�\n",
        "���վ���������һ����$p$W��ת�����ش���$P���ҹɡ���һ���ᷢ��������$P$wδ��$p���壬\n"
        "�����ȵñ����˴��У�$P��æ��$w���С�\n",
        "$pȴ��������������$W�ϡ�$Pֻ��$p�������$W�о���һ�ɼ�ǿ������ǣ����$P$w����бб��$w������ƫ�󣬱���ƫ�ҡ�\n",
        "$p�ۼ�Σ�����Ӱ���ס��ǰ�����˼��ּ��ͣ�ʹ��" + HIG "��������ͷ��" NOR + "����$P$w���䡣\n",
        "$p��ʱ��$Pվ�����������ܲ�������æ��ת$W����$P��ʽһһ������\n",
});

string query_parry_msg(object weapon)
{
        object ob;
        object victim = this_player();

        if (! objectp(ob = victim->query_temp("weapon"))
        ||  ob->query("skill_type") != "staff" 
        ||  victim->query_skill("dagou-bang", 1) < 100)
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return replace_string(parry_msg[random(sizeof(parry_msg))], "$W", ob->name());
}

string *action_msg = ({
        "$Nʹ��һ��"+HIG"������˫Ȯ��"+NOR"������$w���������������$n��$l",
        "$N����$w���һζ���һ��"+HIG"������Ѱ�ߡ�"+NOR"��$n��$l��ȥ",
        "$N����$w���Ӹ�����ʹһ��"+HIG"����ݾ��ߡ�"+NOR"����$n��$l",
        "$Nʩ��"+HIG"���������졹"+NOR"��$w����������$n��ȥ",
        "$N����$w���к�ɨ��һ��"+HIG"�����ع��Ρ�"+NOR"�����з���������Ѹ�ͣ�����$nҪ��",
        "$Nͻʹһ��"+HIG"��б�򹷱���"+NOR"�����о����ޱȣ�$wһ�ϣ��ѻ���$n��$l",
        "$N����$w��һ��"+HIG"������ͷ��"+NOR"����$n$l��ȥ�����ֺ���������"+HIG"���򹷰�����"+NOR"�еĸ���",
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query("dex") < 26)
                return notify_fail("���������̫��޷�ѧϰ�򹷰�����\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("���������Ϊ���㣬�޷�ѧϰ�򹷰�����\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("��Ļ����ȷ��������޷�ѧϰ�򹷰�����\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ĵ򹷰�����\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "dodge" : 80 + random(10),
                "parry" : 80 + random(10),
                "damage": 120 + random(50),
                "attack": 80 + random(10),
                "damage_type": "����",
        ]);
}

/*
mixed hit_ob(object me, object victim, int damage)
{
        string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")))
                return 0;
        
        zhencost = sqrt(weapon->weight() / 10) + 10;
        if (me->query("neili") < zhencost || me->query("jing") < zhencost)
                return 0;
                
        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);
        

        
        if (random(ap+dp) > ap) 
        {
                result = HIG "ͻȻ����������������������޷���" + (string)weapon->query("name") + HIG "������$n��\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap) 
        {
                result = HIG "$N�͵صݳ�һ�У���һ��Ѹ�����ף�ֱȡ$nü�ģ�$p��������һ�������˳����ߣ�\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "�϶�������֮�侹��ת��$n����ĵ�һ������$p���ϳ���һ�¡���\n" NOR;
                damage = weapon->query("weapon_prop/damage");
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
}
*/

int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
           || ! me->query_temp("feng_zijue")
           || ! (weapon = me->query_temp("weapon"))
           || ! living(me)
           || weapon->query("skill_type") != "staff")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "�����ʩչ�򹷰���" HIY "��"
                                            HIG "���־�������" + weapon->name() + HIG
                                            "����ұգ�ʹ��$N" HIG "�Ĺ���ȫȻ��ա�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "��ת����" + weapon->name() +
                                            HIG "���򹷰���" HIY "��" HIG "���־�����"
                                            "�����쾡�£��ٽ�$N" HIG "����ʽ�������Ρ�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "���ʩչ���򹷰����⡹��"
                                 "��������$N" HIY "��Ҳ������������ֱ"
                                 "�룬��Ϯ$n" HIY "��\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "��ת����" + weapon->name() +
                                 HIY "������ұգ�Ȼ��$N" HIY "ȴ�Ǿ���"
                                 "������˿������$n" HIY "���Ի�\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 90)
                return notify_fail("��������������򹷰�����\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("��������������򹷰�����\n");

        me->receive_damage("qi", 80);
        me->add("neili", -80);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}
