// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yuxiao-jianfa.c ��������

#include <ansi.h>

inherit SKILL;

string *xue_name = ({ 
        "�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
        "����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
}); 

string *parry_msg = ({
        "ȴ��$n����΢ת�����赭д����$w���ᵲ�����ڴ�δ����ߣ�������δ��Ƭ��ͣ�͡�\n",
});

string query_parry_msg(object weapon)
{
        object me = this_player();

        if (! objectp(weapon)
        ||  ! me->query_temp("exercise/playing"))
                // return SKILL_D("parry")->query_parry_msg(weapon);
                return 0;
        else
                return parry_msg[random(sizeof(parry_msg))];
}

string *action_msg = ({
        "$N����һ��������$wһ��ʹ��һ�С�ɽ����������Ȧת����$w��������������Ȼ����һ����$w���ã���۵�ֿ�㼲��$n��$l",
        "$N$wһ�ᣬʹ��һʽ���������񡹣����潣�ߣ�Ԣ���ڹ�����$n����ʽ���ǲ������ܣ���ֱ����$n��$l",
        "$N����$w�������裬ʹ��һ�С����¥̨��������һ���̳�����;��������ü�����λ������$n��$l",
        "$N����$w��Ȼһ����ʹ��һ�С����亮������$w�����°�ɻ�Ȧת��ٿ��һչ�����ʯ������$n��$l",
        "$Nͦ����$w����$n���̴̵�������һ�С�������������������˸������΢��������$w��������֮��������$n�������Ѩ",
        "$N����һ����˳��ʹ��һ�С�����ˮ�ơ����������࣬�������磬����һմ���ߣ������������裬ƮȻ����$n��$l",
        "$N��ָ��$w��һ�����һ�����죬һ�С�������������$w�й�ֱ��������˿�����ɣ�������ǰ�Ĵ���$n��$l",
        "$N����չ����ʹ��һʽ����ʷ������������$w��ز���裬�������ƿ�һ�㣬����$n��$l����̬Ʈ�ݣ���������",
        "$N����һ�䣬���μ������ˣ�һʽ���ɻ���䡹������ɭɭ�����������컨��һ�㣬������˷�����������ʵ�����˱��޿ɱ�",
        "$N��̤������Է�λ���������֣�����ʹ��һ�С������˪��������$wбָ������$n����������ʵʵ��Ӧ�����ң���ͨ��������ྶͥ",
        "$N����$w�ɻ���һ�С���©��������������$n��ȥ���䲻��������ȴռ���Ȼ�����$n�������߷�Բ֮�ؾ�����ס",
        "$N�Ų��������ģ�������ҡҡ��׹��ʵ����ȾŹ���һ�С����������ѡ�������ƽƽ�������������޵ش���$n��$l",
        "$N�Ʋ����Σ�һ�С���ɽ��ס���$w���ַɳ�������$n��$l������ʹ������׽Ӱ��������������$w���ù�������ָΪ��������$n",
        "$Nһ����Х������ԴԴ����ע�뽣��������â��ʢ��һʽ������ֹϢ��������������\nһ��ƥ��Ҳ�ƵĽ���Ю��ɭɭ�����ƿն���������ӵ�к����ȻĪ��",
        "$N�Ųȷ�����ʮ���Է�λ�����Ƽӿ죬ʹ��һ�С��Ǻ�ǧ���衹��ֻ��һƬãã�����У�\n������ɫ��Ȧ��ӿ���������֮��$n��û�뽣��֮��",
        "$N����һ����$w��ǰ�ݳ���������֮һ����̫������֮һ����̫��������һʽ�����ʶ���ۡ�����������������ƣ���Ͼ�޹�",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
                
        if ((int)me->query_skill("bibo-shengong", 1) < 50)
                return notify_fail("��ı̲��񹦻��̫ǳ��\n");
 
        return 1;
}

mapping query_action(object me, object weapon)
{
        int level = me->query_skill("yuxiao-jianfa", 1);
        
        if (random(level) > 200 &&
            me->query_skill("force", 1) > 100 &&
            me->query("neili") > 200)
        {
                return ([
                        "action": HIC "$w" NOR + HIC "�ϵĽ�â�����Ƴ��߰���������......\n\n"
                                  HIG"$N����������һ�����������ӵ�����Ĵ��˰��Ȧ�ӣ�����$w"NOR+HIG"һͦ����ؽ�âͻʢ����â����$n$l��"NOR,
                        "dodge" : 100,
                        "parry" : 100,
                        "attack": 200,
                        "damage": 200,
                        "damage_type":  "����"
                ]);
        }
                       
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(50),
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}
        
int practice_skill(object me)
{
        object weapon;

        if (! (weapon = me->query_temp("weapon")))
                return notify_fail("����ʱ�޷������｣����\n");
        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ��޷������｣����\n");
        if ((int)me->query("qi") < 80)
                return notify_fail("����������������｣����\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("����������������｣����\n");
                                
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"yuxiao-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage) 
{
        mixed result;
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if( damage < 50 ) return 0;

        if (! objectp(weapon = me->query_temp("weapon"))
        ||  (weapon->query("id") != "yu xiao" &&
            weapon->query("id") != "xiao")) 
                return;

        result = ([ "damage" : damage ]);
        
        if (random(2) != 1)
                result += ([ "msg" : HIR "$n�������ߴ���һ������������ʱѪ��������һ���������Ķ�����\n" NOR]);
        else
                result += ([ "msg" : HIB "$n��$N����������һ����������������" RED + name + NOR + 
                                     HIB "����ʱ������ת��ʹ����֣�\n" NOR]);
        return result;
}

int query_effect_parry(object attacker, object me) 
{
        int lvl;

        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("yuxiao-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}


