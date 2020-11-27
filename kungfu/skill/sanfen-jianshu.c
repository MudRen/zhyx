#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N��¶΢Ц������$wһ�������Ⱪ��������$n��$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 10,
     "lvl"    : 0,
     "damage_type":  "����"
]),
([   "action" : "$N����ͻ�������ж��䣬����$w��һ�����벻���ķ�λб����$n��$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 5,
     "lvl"    : 10,
     "damage_type":  "����"
]),
([   "action" : "$N�������ߣ����׸������������$w��Ȼ���ϣ�����$n��$l",
     "force"  : 75,
     "attack" : 33,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 20,
     "lvl"    : 20,
     "damage_type":  "����"
]),
([   "action" : "$N����һ�Σ����Ӷ��ϣ�һ�С����տ��㡹������$w����һ������׼$n��$l��������",
     "force"  : 90,
     "attack" : 39,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 25,
     "lvl"    : 30,
     "damage_type":  "����"
]),
([   "action" : "$N��ɫ΢�䣬һ�С�����ݡ������ж�ʱ��������ޱȣ�����$w��ƥ��������$n��$l",
     "force"  : 180,
     "attack" : 71,
     "dodge"  : 30,
     "parry"  : 52,
     "damage" : 40,
     "lvl"    : 70,
     "damage_type":  "����"
]),
([   "action" : "$N�������ף�����һ�С��ٻ����졹������$w�й�ֱ����Ѹ���ޱȵ���$n��$l��ȥ",
     "force"  : 200,
     "attack" : 85,
     "dodge"  : 20,
     "parry"  : 54,
     "damage" : 35,
     "lvl"    : 80,
     "damage_type":  "����"
]),
([   "action" : "$N����ಽ��һ�С���Į���̡�������$w���ּ�����������ৡ���һ����$n��$l��ȥ",
     "force"  : 240,
     "attack" : 91,
     "dodge"  : 65,
     "parry"  : 65,
     "damage" : 58,
     "lvl"    : 100,
     "damage_type":  "����"
]),
([   "action" : "$N��ؼ���һ�����ֳ�ǰ������һ�С�ƽɳ���㡹������$w��Ϊһ��������$n��$l��ȥ",
     "force"  : 265,
     "attack" : 93,
     "dodge"  : 40,
     "parry"  : 68,
     "damage" : 72,
     "lvl"    : 110,
     "damage_type":  "����"
]),
([   "action" : "$N����Ծ��һ�С�ѩ����������������Ӱ������ȴ�ִӰ���д��£�$wֱ��$n��$l",
     "force"  : 290,
     "attack" : 97,
     "dodge"  : 60,
     "parry"  : 72,
     "damage" : 78,
     "lvl"    : 120,
     "damage_type":  "����"
]),
([   "action" : "$Nһ�С�ǧ����ɳ��������$wңָ�Կգ���Ȼ����һ�����֣���$n��$l��ȥ",
     "force"  : 310,
     "attack" : 100,
     "dodge"  : 45,
     "parry"  : 75,
     "damage" : 86,
     "lvl"    : 130,
     "damage_type":  "����"
]),
([   "action" : "$Nһ�С����ӵ�к�����������������$w�͵����·����𣬼���һ�ɾ��練��$n��$l",
     "force"  : 330,
     "attack" : 105,
     "dodge"  : 50,
     "parry"  : 82,
     "damage" : 95,
     "lvl"    : 140,
     "damage_type":  "����"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 700)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ���ֽ�����\n");

        if ( me->query("dex") < 45 && me->query_skill("sanfen-jianshu", 1) > 150) 
                return notify_fail("������鶯�Բ��������Լ����������ֽ�����\n"); 

        if ( me->query("gender") == "����" ) 
                return notify_fail("���޸����ԣ������������ֽ�����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("sanfen-jianshu", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������ֽ�����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("sanfen-jianshu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 150)
                return notify_fail("�������Ŀǰû�а취��ϰ���ֽ�����\n");

        if ((int)me->query("neili") < 360)
                return notify_fail("��������������޷���ϰ���ֽ�����\n");

        if (me->query("dex") < 45 && me->query_skill("sanfen-jianshu", 1) > 150) 
                return notify_fail("������鶯�Բ��������Լ����������ֽ�����\n"); 

        if ( me->query("gender") == "����" ) 
                return notify_fail("���޸����ԣ������������ֽ�����\n");
        
        me->add("qi", -120);
        me->add("neili", -250);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("sanfen-jianshu", 1);

        if (damage_bonus < 120
           || me->query("neili") < 500
           || me->query_skill_mapped("sword") != "sanfen-jianshu")
                     return 0;

        switch(random(3))
        {
           case 1:
              if (damage_bonus > victim->query_con())
              {
                  me->add("neili", -20);
                  victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                  
                  return random(2) ? MAG "$N" MAG "���ƴ̳�һ����$n" MAG
                                     "���ڷ�������ʱ���С�\n" NOR:
                                     MAG "$N" MAG "��̾һ��������ʩ��һ����$n" MAG ""
                                     "��Ҫ������ȴ�������У������ҽС�\n" NOR;
             }
             break;

          case 2:
             if (random(lvl / 2) + lvl > victim->query_skill("dodge",1))
             {
                  weapon = me->query_temp("weapon");
                  victim->start_busy(2);
                  return   HIG "$N" HIG "����һ��������" + weapon->name() + HIG "����һ��������,"
                           "$n" HIG "һʱ����������⻮����Ѫ���졣\n" NOR;
             }
             break;

          case 3:
             if (lvl > 250 && random(lvl / 2) + lvl > victim->query_skill("parry", 1)
                  && ! me->query_temp("perform_sanfenjian/lian"))
             {
                weapon = me->query_temp("weapon");
                message_sort(HIR "\n$N" HIR "һ�����������" + weapon->name() + HIR"��ʱ"
                             "�û����������������Я��籩��֮��"
                             "��$n" HIR "���빥ȥ��\n" NOR, me, victim);
                me->set_temp("perform_sanfenjian/lian", 1);

                for (i = 0; i < 5; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                } 
                me->delete_temp("perform_sanfenjian/lian");     
                me->add("neili", -50);          
                
             }
             break;     
          	                        
          default:
                return 0;
       }
}

string perform_action_file(string action)
{
        return __DIR__"sanfen-jianshu/" + action;
}