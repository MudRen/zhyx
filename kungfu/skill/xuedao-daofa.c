// xuedao-daofa.c Ѫ��
// updated by lwx 

inherit SKILL;
#include <ansi.h> 

string *action_msg = ({
        "$Nʹ��һ��"HIW"��ĥ��˱Ѫ��"NOR"���ѵ�ҧ�ڿ��У�ֻ��$n��ǰ�����ת������������͵�������ǰ���γ�����һ��ֱ����ȥ",
        "$N�����˼磬��ͨ춱ۣ���ǰһ�壬���һ���룬�������ţ�����һ����$n����·ʵ������������һ��"HIB"����ֽ������"NOR,
        "$N�ڷ��ɺɹ��������е�ֱ��ǰ�죬һ��"HIR"��Ѫ��ãã��"NOR"������$wֱ��ǰ�죬��$n����������������ڵ���֮��",
        "$N��һ�һ��"HIC"�����Ǿ��졹"NOR"�����е����ַɳ���һ���⣬����$n��$l��ȥ",
        "$Nһ��"HIG"��Ѫ�����"NOR"������ԭ�ش���һ��ת, ����һ����$n��$lͱ�˹�ȥ",
        "$N˫�ַ�ִ���⣬��춻��У�ͻȻ���΢����һ��"HIC"��͵�ƻ��ա�"NOR"�����ִ��ұ��´���ת��$n��Ŀ�⣬����ִ���ʹ�$n��$l",
        "$NͻȻ�������ʣ�����۽���ȥ�������򣬷��ֳ鵶��һʽ"HIY"��Ѫϴ��ӡ�"NOR"��ֻ��һƬƥ��Ҳ�Ƶĵ����$n����ֱ���������",
        "$N����ƽָ��һ��"HIM"��Ѫ�����桹"NOR"�����������������ֱ�����������������$n������",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query("character") == "��������")
                return notify_fail("�����а�������Ѫ����а��̫�أ��������죬Ī" 
                                   "����ר���������˵ģ�\n");

        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("xuehai-mogong", 1) < 20)
                return notify_fail("���Ѫ��ħ�����̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type": random(2) ? "����" : "����", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 40)
                return notify_fail("�������������Ѫ��������\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("�������������Ѫ��������\n");
        me->receive_damage("qi", 30);
        me->add("neili", -20);
        return 1;
} 
mixed hit_ob(object me, object victim, int damage) 
{
        mixed result;
        if (damage < 100) return 0; 
        if (random(damage / 2) > victim->query_str()) 
        { 
                result = ([ "damage": damage ]);
                result += (["msg" : HIW "$Nа���󷢣���ʱ��â��ʤ�����Ŵ�����$n���ϻ�����$n" BLINK + 
                                    HIR "��Ѫ" NOR + HIW "���������\n" NOR ]);
                return result;
        } 
}
string perform_action_file(string action)
{
        return __DIR__"xuedao-daofa/" + action;
}

