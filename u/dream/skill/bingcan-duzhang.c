// bingcan-duzhang.c  ���϶���
// by Lonely

#include <ansi.h>
inherit SKILL;

string *action_msg = ({ 
        "$N����¶�������Ц�ݣ�˫��Я����˪����ɨ$n",
        "$N����һ����Х���ۼ�ȫ�����������$n",
        "$N�����һЦ��˫�ƴ��������ĺ�������$n��$l",
        "$N��ɫ���ɷ�ף�����ƽ������$n$l����һ��",
        "$Nʹ��ȫ��˫����$n���ƣ���ʽƽ�����룬��խ�ٳ�.",
        "$N�����Ϻ�����ת��������������ʽ��ȴ�����ޱȵ���$n��$lϮȥ",
        HIW "$N" + HIW "����������" + HIR "����" + HIC "����" + HIW"����˫�����ģ�\nֻ��" + 
        HIC "��" + HIW "��һ����һ���ɫ�����������ı������������$n"+NOR"",
        "$N�����Ϻ����������֣������ޱȵ�����$n��$l",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }   

int valid_combine(string combo) { return combo == "bingcan-shenzhao"; }

mapping query_action(object me)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(90), 
                "attack": 70 + random(10), 
                "dodge" : 70 + random(10), 
                "parry" : 70 + random(10), 
                "damage_type" : random(2) ? "����" : "����", 
        ]);
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");
        if ((int)me->query_skill("freezing-force", 1) < 10)
                return notify_fail("��ı��Ϻ�����򲻹����޷����������ơ�\n");
        if ((int)me->query("max_neili") < 60)
                return notify_fail("�������̫�����޷����������ơ�");
        return 1;
}


int practice_skill(object me)
{
        if ((int)me->query("qi") < 80)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("��������������������ơ�\n");
        if (me->query_skill("bingcan-duzhang", 1) < 50)
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

        lvl  = me->query_skill("bingcan-duzhang", 1);
        flvl = me->query("jiali");
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("bingcan_duzhang",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "ֻ��һ�󼫺����ĵ����𣬿���������$N" HIW "���ϵı��Ϻ�����\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bingcan-duzhang/" + action;
}

