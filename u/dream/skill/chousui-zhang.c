// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// chousui-zhang.c ������

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N����¶�������Ц�ݣ�����΢�ڣ��Իε�$n���������������ɫ��˫��ɨ��$n��$l",
        "$NͻȻһ���У�������ת��������$n��˫�Ʒ���������$n��$l",
        "ͻȻ��$N��ɫһ���������з����Ź����죬�������������֣�һ�С���ʬ���������ޱȵ�ץ��$n��$l",
        "$N��һת����һת�����ӻ���֮����ת�ۼ��Ѿ��۵�$n��ǰ��˫��Ю��һ���ȳ�֮������$n��$l",
        "$N�͵�Ծ�𣬴�����$n��ȥ����$nһ�ǻ���֮�ʣ��������𶾹��͵���$n��ȥ��",
        "$NͻȻ���˵ض�����˫����$n������ȥ����$n����֮ʱ��˳��ץ�����ʯͷ��$n��$l��ȥ",
        "$N˫Ŀ�׹���䣬�ؿڸ߸߹��𣬽����������������У�ƴ������$n��ȥ",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }
int valid_combine(string combo) { return combo == "sanyin-zhua"; }

mapping query_action(object me, object weapon)
{
        if (present("huo yan", environment(me)))
        {
                if (random(me->query_skill("strike")) > 250 && me->query("neili") > 1000) 
                {
                        me->add("neili", -100);
                        return ([
                                "action": BLU "$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ�������ҧ��⣬" HIR "һ����"
                                "Ѫ���������ȥ��\n�ǻ������һ����" HIW "�漴��Ϊ������$N�͵����Ӽ���������"
                                "�ݰ���ת��ʮ���Ȧ�ӣ�\n" HIR "�����������������Ѷ��ز��𣬱���һ����ǽ����$nѹ��ȥ" NOR,
                                "force" : 450,
                                "dodge" : 100,
                                "parry" : 100,
                                "weapon": "����",
                                "attack": 200,
                                "damage_type": "����"]);
                }
                if (random(me->query_skill("strike")) > 215 &&
                    me->query("neili") > 800) 
                    {
                        me->add("neili", -75);
                        return ([
                                "action": HIG "$N������ȣ�������ʢ���̻�ͻȻ����һ��" 
                                          HIR "����Ļ�����$n���������\nʹ�����ͣ�ȥ����죬" 
                                          HIG "ֻ��һ���̵Ļ����ڿ��й�µµ��Ѹ��ת��" NOR,
                                "force" : 420,
                                "dodge" : 90,
                                "parry" : 90,
                                "weapon": "����",
                                "attack": 180,
                                "damage_type": "����"]);
                }
                if (random(me->query_skill("strike")) > 180 &&
                    me->query("neili") > 600) 
                {
                        me->add("neili", -50);
                        return ([
                                "action": HIR "$N����һ����һ�ɾ���ֱ�������֮�У�"+HIG+"�������ֳַ�һ��ϸϸ���̻𣬱���һ��ˮ�߰㣬\n"
                                          HIW "$N����Ӷ������ɾ����Ϯ$n����" NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "weapon": HIG "�̻�" NOR,
                                "attack": 150,
                                "damage_type": "����"]); 
                }
                if (random(me->query_skill("strike")) > 150 &&
                    me->query("neili") > 500) 
                {
                        me->add("neili", -20);
                        return ([
                                "action": HIR "$N�漴����б�ĳ�һ��"+HIG+"�̻�"+HIR+"��$n��ȥ���������ڣ�"+HIG+"����һ����ɫ���ߺ��Կռʣ�����ڶ���\n"
                                          HIR "��ɫ�������ޣ�"+BLU+"���ǹ��죬��â��˸����"+HIG+"��ӳ��$nͷ���Ա�"NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "weapon": HIG"�̻�"NOR,
                                "attack": 120,
                                "damage_type": "����"]); 
                }
                
                if (random(me->query_skill("strike")) > 120 &&
                        me->query("neili") > 400 ) {
                        me->add("neili", -10);
                        return ([
                                "action": HIR "$NͻȻ��˫ü����һ��������ʳָ�����㣬������������������죬"+HIG+"��������𻨣���������һ�㣬\n"
                                          "��$N���������£��ִ�����Ϯ��$n������Ѹ��֮��" NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "attack": 100,
                                "weapon": "��",
                                "damage_type": "����"]);
                }
        }
        
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(50), 
                "attack": 70 + random(10), 
                "dodge" : 70 + random(10), 
                "parry" : 70 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int valid_learn(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("chousui-zhang", 1);

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");
                
        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷���߳����ơ�\n");
                
        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
        
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĳ����Ʒ���\n");
                
        if ((int)me->query("max_neili") < 60)
                return notify_fail("�������̫�����޷���������");
        return 1;
}

int practice_skill(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("chousui-zhang", 1);

        if ((int)me->query("qi") < 80)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("������������������ơ�\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷���߳����ơ�\n");

        if (me->query_skill("chousui-zhang", 1) < 50)
                me->receive_damage("qi", 60);
        else
                me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chousui-zhang", 1);
        flvl = me->query("jiali");

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                // �����ǳ����Ƶ� perform sandu �е�ɢ������ת�����
                if (me->query_skill("poison", 1) < 101) 
                        me->set("body_poison", me->query_skill("poison", 1) + 1); 
                if (me->query_skill("poison", 1) > 100) 
                        me->set("body_poison", me->query_skill("poison", 1) + 10); 
                //  ɢ������
                return HIW "$n" HIW "ֻ��һ�󼫺����ĵ����𣬿���������$N" HIW "���ϵľ綾��\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}

