// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// banruo-zhang.c ������

#include <ansi.h>

inherit SHAOLIN_SKILL;

string *action_msg = ({
        "$Nǰ���߳������Ƚż��أ�һʽ����ճ�����������ֱ��������$n����������·",
        "$N���ƻ�һ��Բ��һʽ��������ա�������б������������$n����ǰ��Ѩ",
        "$Nʹһʽ���ƶ����롹�����������������ɺ����һ��˦����ն��$n��$l",
        "$N���ƻ��أ���ȭ�����󷢣�һʽ����������������������$n��$l",
        "$Nʹһʽ������ء���ȫ�������ת��˫��һǰһ���͵�����$n���ؿ�",
        "$N���Ʊ�������һ������һʽ�����б��¡���˫�Ƽ�����$n�ļ�ͷ",
        "$N���ϸ߸�Ծ��һʽ����ɽ��ˮ�����Ӹ����£���������$n��ȫ��",
        "$Nʹһʽ��ժ�ǻ�����������������˫�����֣�һ������$n��$l�ȥ",
        "$N�������»��أ�һʽ����������������Ȼ��Ϊ�������꣬����$n",
        "$Nһʽ����շ�ħ����˫�ֺ�ʮ������$n΢΢һҾ��ȫ���ھ�����˰���ӿ����",
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "yizhi-chan"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹����޷��������ơ�\n");

        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷��������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("banruo-zhang", 1))
                return notify_fail("��Ļ����Ʒ����ˮƽ���ޣ��޷���������İ�������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        string *msg = ({
                "�ȵ���������һ�ƣ���",
                "˫�ֺ�ʲ��˵�����������ӷ𣡡�",
                "˵����������������������һ���ڣ�����",
                "",
        });

        level = (int)me->query_skill("banruo-zhang", 1);
        if (me->query_temp("sl_perform/san"))
        {
                i = me->query_skill("force") + level;
                return([      
                        "action": HIW"$N"+ msg[random(sizeof(msg))] +"˫����������ת�˸�ԲȦ��������$n���˹�����\n"
                                        "$P����δ����$n�Ѹ��ؿں������������֮�䣬$N��������ŭ������ӿ������"NOR,         
                        "force" : i + random(i),
                        "dodge" : 100,
                        "parry" : 100,
                        "attack": 200,
                        "damage_type" : "����", ]);
        }
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(120), 
                "attack": 50 + random(10), 
                "dodge" : 50 + random(10), 
                "parry" : 50 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 60)
                return notify_fail("������������������ơ�\n");

        if( (int)me->query_skill("nianhua-zhi", 1) < 150 )
                return notify_fail("����黨ָ��Ϊ��������\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

void skill_improved(object me)
{
        int level = (int)me->query_skill("banruo-zhang", 1);

        if (level >= 180
        &&  (int)me->query_skill("yizhi-chan", 1) >= 180
        &&  ! me->query("sl_gifts/yzc") ) {
                me->add("con", 1);
                me->set("sl_gifts/yzc", 1);
                tell_object(me, "\n���һָ���Ͱ�����ѧ�����ɣ��������ĸ��ǡ�\n");
        }

        if( !(level % 10) && level >= (int)me->query_skill("force", 1) ) {
                me->improve_skill("force", (level - 5), 1);
                tell_object(me, "\n���ڰ����Ʒ����������������Ļ����ڹ���Ϊ��\n");
        }

        /*
        if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) ) {
                me->improve_skill("hunyuan-yiqi", (level - 5)/2, 1);
                tell_object(me, "\n���ڰ����Ʒ����������������Ļ�Ԫһ������Ϊ��\n");
        }              
        */
}

string perform_action_file(string action)
{
        return __DIR__"banruo-zhang/" + action;
}

