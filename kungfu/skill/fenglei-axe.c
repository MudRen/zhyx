// fenglei-axe.c �������׸� 

inherit SKILL;
#include <ansi.h>

string *action_msg = ({
       "$N��$wһ�ڣ�����������������һʽ������է�졻��Ȼ��ɣ�����ʵ�ʵ�����������������$n" NOR,
       "$w����һ�䣬���紩��������С��ϸ�壬���ǡ��������׸����ھ�ʽ��������꡻" NOR,
       "$N�󿪴��أ��ڶ�ʽ��������ơ����������$n" NOR,
       "$N��������$w�߾ٹ�ͷ���˾�ֱ��������ʽ�����׷ٳǡ���Ȼ���ް�㻨��" NOR,
       "$w�ٱ䣬��$N���´�����ң��$n��$l������ʽ��Ѹ��ǧ�á���$n��ȫ�޷�׽������" NOR,
       "$N����$w������һ���һ���󻡣�$w�����ʽ�������ɳ��������߷����㸫Ӱ����$nƽ�ƶ���" NOR,
       "$NԾ����գ�ʹ������ʽ���������ס�������$w��Ю������֯��һ��������$n��ȥ" NOR,
       "$N�������У�$w������Ϊ��׾���˾��Ƴ�����ѩ����â������ʽ���������꡻һ������һ���ع���$n" NOR,
       "$N�Ӹ����й�ֱ�������󷭴�����;ת�򣬵ڰ�ʽ���������������ѱ任��������λ����������$n��$l" NOR,
       "$w��$N���е��𣬻���һ��Ư���Ļ�������$n��ͬʱ���ֻ�ȭֱ���������������ĵ�ʮʽ������������" NOR,
});

int valid_enable(string usage) { return usage == "axe" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("zidian-jin", 1) < 25)
                return notify_fail("��������ϵ羢���̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 180 + random(50),
                "attack": 100 + random(30),
                "dodge" : 100 + random(30),
                "parry" : 100 + random(30),
                "damage_type" : random(2)?"����":"����",
        ]);
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result; 
        
        if (me->query_skill("zidian-jin", 1) < 100
        ||  me->query_skill_mapped("force") != "fenglei-axe"
        ||  ! me->query_temp("powerup")
        ||  damage < 100) return 0;

        if (random(damage / 2) > 50) 
        {
                result = ([ "damage": damage ]);                 
                result += (["msg" : HIR "ֻ����â������$n�rѪ�ĞR����$N" HIR "���Ͼۼ��������ϵ羢���ˣ�\n" NOR]);
                return result;
        }
}


int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "axe")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 70)
                return notify_fail("��������������������׸���\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("��������������������׸���\n");               
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fenglei-axe/" + action;
}

