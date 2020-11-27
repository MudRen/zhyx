// fanliangyi-dao.c �����ǵ���
// by Lonely

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit SKILL;

mapping *action_msg = ({
        "$N����$wбָ��һ�С�����һ�ơ�������һ�٣�һ����$n��$l��ȥ",
        "$Nһ�С�̫�����ȡ�����������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
        "$Nչ���鲽������Ծ�䣬һ�С����Ǻϵ¡������滯������ն��$n",
        "$Nһ�С����»�������$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
        "$N����$wһ����һ�С���ɫ���ࡹ��˫�ֳ����������У�����$n���ؿ�",
        "$N����$w��ʹ��һ�С���ٲ��������������ã����ҿ�����������$n",
});


int valid_enable(string usage) 
{ 
        return usage == "blade" || usage == "parry" || usage == "array"; 
}

int form_array(object leader)
//int perform(object leader, object target)
{
        object *member,ob, weapon;
        int i,j,n;
        int max,min,skill;

        member = leader->query_team();
        if( sizeof(member) != 2 )
                return notify_fail("�����ǵ��������ˣ���һ����һ�������С�\n");

        j=sizeof (member);
        for (i=0;i<j;i++)
        {
                ob=member[i];
                if (!ob||!living(ob)||!ob->is_character())
                {
                        return notify_fail("�����˭ͬʹ�����ǵ���\n");
                }
                if (ob->query_temp("array/name"))
                {
                        return notify_fail("�Ѿ���ɵ����ˡ�\n");
                }
                if (environment(leader)!=environment(ob))
                {
                        return notify_fail("�����������ˡ�\n");
                }
                if (!ob->query_skill("fanliangyi-dao",1))
                {
                        return notify_fail(ob->name()+"�����ᷴ���ǵ�����\n");
                }
                if (ob->is_ghost())
                {
                        return notify_fail("ֻ��������˲����鵶��\n");
                }

                if( (int)ob->query("max_neili") < 50 )
                        return notify_fail(ob->query("name")+"������������\n");

                if( (string)ob->query_skill_mapped("force")!= "zixia-gong")
                        return notify_fail(ob->query("name")+"û��ʹ�û�ɽ���ڹ���\n");

                if( !(weapon = ob->query_temp("weapon"))
                ||      (string)weapon->query("skill_type") != "blade" )
                        return notify_fail(ob->query("name")+"�����ðѵ���������\n");

                if( (int)ob->query_skill("fanliangyi-dao",1)<30)
                        return notify_fail(ob->query("name")+"�ķ����ǵ���������������\n");

                if( (string)ob->query_skill_mapped("blade")!="fanliangyi-dao")
                        return notify_fail(ob->query("name")+"����ʹ�÷����ǵ�����\n");

        }

//get the average array skill of the team
        n=0;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                n+=(int)ob->query_skill("fanliangyi-dao",1);
        }
        n/=2;

//get the difference of the array skill,
//first get the max and mix skill level of the array
        max=member[0]->query_skill("fanliangyi-dao",1);
        min=max;
        for (i=0;i<j;i++)
        {
                skill=member[i]->query_skill("fanliangyi-dao",1);
                if(skill>max)
                        max=skill;
                else if(skill<min)
                        min=skill;
        }

//and the leader is important
        n += leader->query_skill("fanliangyi-dao", 1) * 5;
        n /= max - min + 1;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                ob->set_temp("no_quit",1);

                ob->set_temp("array/name","fanliangyi-dao");
                ob->set_temp("array/level",n);

                ob->add_temp("apply/attack",n);
                ob->add_temp("apply/defense", n);
                ob->add_temp("apply/damage",n);
                ob->add_temp("apply/armor", n);
        }
        message_vision( HIG "$N����$Nվ�����Ƿ�λ����ʱ����֮���Եû�Ȼ��ɡ����
�������\n" NOR, leader);
        return 1;
}

int dismiss_array(object person)
{
        int i,j,n;
        object *member,ob;

        member = person->query_team();
        j=sizeof(member);
        n=person->query_temp("array/level");
        for (i=0;i<j;i++)
        {
                ob=member[i];
                ob->delete_temp("array");
                ob->add_temp("apply/attack",-n);
                ob->add_temp("apply/damage",-n);
                ob->add_temp("apply/defense",-n);
                ob->add_temp("apply/armor", -n);
                tell_object(ob,"�����ɢ��\n");
        }
}

//if the leader kills enemy, then all members in the array kill enemy
int array_kill(object leader, object enemy)
{
        object *member, ob;
        int i,j;
        member=leader->query_team();
        j=sizeof(member);

        for(i=0;i<j;i++) {
                ob=member[i];
                ob->kill_ob(enemy);
        }

        return 1;
}

int effective_level() { return 10;}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("zixia-shengong", 1) < 10)
                return notify_fail("��ġ���ϼ�񹦡����̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(50), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : "����", 
        ]); 
}

int practice_skill(object me)
{
        object weapon;

        if( !me->query_skill("zixia-shengong", 1))
                return notify_fail("���������ǵ���������Ҫ�ԡ���ϼ�񹦡�Ϊ������\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("��������������������ǵ�������\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("�������������\n");

        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fanliangyi-dao/" + action;
}


