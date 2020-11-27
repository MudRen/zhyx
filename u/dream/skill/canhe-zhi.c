// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// canhe-zhi.c �κ�ָ

inherit SKILL;

#include <ansi.h>

string *xue_name = ({ 
        "�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
        "����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
});

string *action_msg = ({
        "$N���缤����˫ָ������ã�һ�С�Ŀ��ʶ�����׺ݵ���$n��$l��ȥ",
        "$N���һ����ʮָ���·ַɣ�һ�С������㾦����˫ֱָȡ$n��$l",
        "$Nʮָ���������ʵ��һ�С���˷���롹��ǰ�����ң�˲Ϣ����$n����������",
        "$N�����ڿն���һ�С��ܳ���������������죬��$n��$l�Ͳ���ȥ",
        "$N����һ�������������ߵ�$n��ǰ��һ�С����ϲ�����������$n��$l",
        "$Nһ�С��˱����᡹������һȭ���������ƻ�ָ��һ��һָ��ջ���$n��$l",
        "$N˫�ƻ�ָ��ָ�д��ƣ�˫�����ƣ�һ�С���н��������һ����ɽ������������ֱ��$n$l",
        "$NͻȻ���м�ת��һ�С����μ�����ʮָ���裬��ʱ֮�佫$n����˷�����ס��",
        "$NĬ����Ԫ�񹦣�������������ָ��ƽƽ�������޻��εص���$n������Ѩ���ѵ���豹���ľ���",
        "$N��������ָ������ָ��ϳ�һ�ɽ�����ֱ����$n,����֮��������������֮��",
});

string *xue2_name = ({
        MAG "$NĬ����Ԫ�񹦣�������������ָ��ƽƽ�������޻��εص���$n������Ѩ" NOR,
        YEL "$N�������ϣ�����΢�飬������֮���ţ�����˫��ʳָ����һ��������ָ��ͬʱϮ��$n" NOR,
        WHT "$N��������ָ������ָ��ϳ�һ�ɽ�����ֱ��$n��ȥ"NOR,
        RED "$N�������֣���ָ���ǻ��ţ��ٻ���£ָ��ȭ����ʱ��������������Ľ�������" NOR,
        HIR "$Nָ��Ϭ������һ�����ν�������$n�������ڣ�$nֻ���ؿ�һʹ��ȫ��������к����" NOR
});
        
int valid_combine(string combo)  
{
        /*
         object me = this_player();
         mapping myfam = (mapping)me->query("family");
         if (myfam["master_name"] == "Ľ�ݲ�")
         */
        return combo == "qixing-quan";
}

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }


int valid_learn(object me)
{
        if ((int)me->query("int") < 30)
                return notify_fail("���������ô����Ͳ�Ҫǿ���ˡ�\n");
        if ((int)me->query("dex") < 30)
                return notify_fail("�����̫���ˣ��޷�ѧϰ�κ�ָ��\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���κ�ָ������֡�\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 15)
                return notify_fail("�����Ԫ����򲻹����޷�ѧ�κ�ָ��\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷����κ�ָ��\n");
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("canhe-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ĳκ�ָ��\n");                
        return 1;
}

mapping query_action(object me, object weapon)
{        
        string name;   
        int i, level;
        level   = (int) me->query_skill("canhe-zhi", 1);
        name = xue2_name[random(sizeof(xue2_name))];

        if (random(level) >= 300)
        {
                return ([
                        "action": "" + name + "" NOR,
                        "damage_type": "����",
                        "attack": 200,
                        "dodge" : 100,
                        "parry" : 100,
                        "force" : 500,
                ]);
        } else 
        {
                return ([
                        "action": action_msg[random(sizeof(action_msg))],
                        "force" : 330 + random(60),
                        "attack": 70 + random(10),
                        "dodge" : 70 + random(10),
                        "parry" : 70 + random(10),
                        "damage_type" : "����",
                ]);
        }
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 80)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("��������������κ�ָ��\n");
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canhe-zhi/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];
    
        if (victim->is_busy() || damage_bonus < 100) return 0;
        
        if (! objectp(weapon = me->query_temp("weapon"))) 
        {
                if ((me->query("neili") > 200) && random(me->query_skill("canhe-zhi", 1)) > 60)
                {
                        victim->start_busy(2);
                        me->add("neili",-30);
                        if (victim->query("neili") <= (damage_bonus / 2 + 30))
                                victim->set("neili", 0);
                        else
                                victim->add("neili", - damage_bonus / 2 + 30);
                                
                        return HIW "$NĬ����Ԫ�񹦣�ָ����ƮƮ�ص���$n��һ���ھ�������Ϣ������$n�����Ѩ��\n"
                               HIW "$nֻ��ȫ��һ�飬�ѱ�һ�е��С�" HIR + name + HIW "����\n" NOR;
                } 
        }
}

int difficult_level() 
{
        return 400;
}
