// jiuyin-zhao.c
// by Lonely

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        BLU"$N�����転������аħ��˫צ���ץ�������������󷭴������ּ��죬�����ָץ��$n$l"NOR,
        BLU"ͻȻ��Ӱ������$N�ȵ�$n�����������֣������ָ��$n$l������ȥ"NOR,
        BLU"$N�ֱ۹ؽڿ���һ�죬�ֱ۶�Ȼ���˰�ߣ�һ�ư���$n$l����ָ��Ҫ���"NOR,
        BLU"$N˫��΢�ţ�ʮ������ָ��ӳ���Ұ׹�æ��ͻȻ�����צ����ָ�͵ز���"NOR,
        BLU"$N����ͻȻ��$n��ǰ��Χ�¹���������ת���������߰˰㣬���������һ�죬�����ֱָ��$n$l"NOR,
        BLU "$N��צ��Σ���צ������һ��" HIR "��������ǡ�" BLU "ֱ����$n��$l" NOR,
        BLU "$N˫��������צ��צצ����$n��" HIR "������������" BLU "����$n��$lץ��" NOR,
        BLU "$N����Χ$nһת��ʹ��" HIR "�����޵�����" BLU "��$n��$l����ȫ������צӰ��" NOR,
        BLU "$Nʹһ��" HIR "�������ơ�" BLU "��˫צ�ó�����צӰץ��$nȫ��" NOR, 
        BLU "$N����������һ��" HIR "��Ψ�Ҷ���" BLU "˫צ������$n�������" NOR,
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������׹�צ������֡�\n");
        if ((int)me->query_skill("claw", 1) < 41)
                return notify_fail("��Ļ���צ����򲻹����޷�ѧϰ��\n");
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷��������׹�צ��\n");
        if (me->query("character") != "�ĺ�����" && me->query("character") != "��ʿ��˫") 
                return notify_fail("�����Բ���������������޷��������׹�צ����ּ��\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(120),
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type" : random(2)?"ץ��":"����",
        ]);
}

int practice_skill(object me)
{
        object obj;

        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("������������������׹�צ��\n");
        if (environment(me)->query("no_fight") )
                return notify_fail("�����������������ˡ�\n");
        if (environment(me)->query("sleep_room") )
                return notify_fail("������������ű�����Ϣ��\n");
        if (! objectp(obj=present("corpse", environment(me))) || ! obj->is_corpse())
                return notify_fail("�������׹�ץ����ʬ�塣\n");
        if (me->query_skill("jiuyin-zhao", 1) > 100 && me->query("shen") > -100)
                return notify_fail("����а���书��������������ġ�\n");
        me->receive_damage("qi", 35);
        me->add("neili", -25);
//        tell_room(environment(me), 
//                HIB"ֻ��"+me->query("name")+"������Ȧ�¹���������ת���������߰˰㻨�������������һ�죬�۵�"
//                "һ�죬\n�����ֱָ�������ʬ������š���������ָ"HIR"Ѫ����"HIB"���Ὣ������\n");

        return 1;
}
void skill_improved(object me)
{
        tell_object(me, HIR "���Ȼ���ĵ�����һ�ɶ��ɱ��ɱ��ɱ����Ҫɱ�������ˣ�\n" NOR );
        me->add("shen", -200);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;
        mixed result;

        lvl  = me->query_skill("jiuyin-zhao", 1);
        flvl = me->query("jiali");
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (random(damage_bonus / 2) > victim->query_str()
        &&  victim->affect_by("jy_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                result = ([ "damage" : damage_bonus ]); 
                result += ([ "msg" : HIR "��������������һ�����죬�����ǹ����������\n" NOR ]); 

                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("jiuyin-zhao", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action) 
{
        return __DIR__"jiuyin-zhao/" + action; 
}

