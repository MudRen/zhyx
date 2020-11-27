//nap-unarmed.c
//Created by Kasumi

#include <ansi.h>
#include <combat.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N�������ᣬ��Ȼ��$n����һ��",
        "force" : 500,
        "attack": 400,
        "dodge" : 200,
        "parry" : 200,
        "damage": 300,
        "lvl"   : 0,
        "damage_type" : "����"
]),
([      "action": "$N˯��ϡ�ɣ��������ģ�����бб����$n����һ��",
        "force" : 700,
        "attack": 600,
        "dodge" : 300,
        "parry" : 300,
        "damage": 800,
        "lvl"   : 300,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"|| usage == "cuff"|| usage == "strike"|| usage == "hand"|| usage == "claw"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��˯���޺�ȭ������֡�\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("����ڹ���򲻹�������ǿ����ϰ˯���޺�ȭ��\n");
        
        if ((int)me->query("max_neili") < 2500)
                return notify_fail("�������������ǿ���޷���ϰ˯���޺�ȭ��\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("nap-unarmed", 1))
                return notify_fail("��Ļ���ȭ�Ż��ˮƽ���ޣ��޷����������˯���޺�ȭ��\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("nap-unarmed", 1);
        if (level < action[1]["lvl"])
                return action[0];

        return action[1];
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("����������ϰ��\n");

        if ((int)me->query("qi") < 300)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�������������˯���޺�ȭ��\n");

        me->receive_damage("qi", 200);
        me->add("neili", -250);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{        
        int lvl;      
        int i, ap, dpp, dpd; 
        string type, msg, msg1; 
        
        lvl = me->query_skill("nap-unarmed", 1); 
        
        if (me->query("neili") < 1000 ||  me->query_skill_mapped("force") != "huimeng-xinfa"||  lvl < 300 )
           return 0; 
          
        ap = me->query_skill("nap-unarmed",1); 
        dpp = victim->query_skill("parry",1); 
        dpd = victim->query_skill("dodge",1); 

        
        if(random(2)==0) 
        {         
                if (ap * 4 / 5 + random(ap) > dpp) 
                { 
                        me->add("neili", -100); 
                        victim->receive_damage("qi", damage_bonus*3, me);
                     
                        msg1 = HIR "$N��һ��ò�ƺ���׼ͷ��ȴ���治��ػ���$n�ؿ�ҪѨ��$n�۵��³�һ����Ѫ��\n" NOR;                        
                        return msg1;
                } 
		}
        else
        {		 
                if (ap * 3 / 4 + random(ap) > dpd && ! me->is_busy() && ! me->query_temp("nap-unarmed/lian")) 
                {                       
                        message_sort(HIY "\n$N" HIY "ҡҡ�λΣ��������ᣬ���²������ң�˫�����裬���ع������С�\n" NOR, 
                                     me, victim); 
        
                        me->add("neili", -300); 
						
						if (me->query_skill("count"))
			             me->set_temp("count",1);
	                    else
			              me->set_skill("count", 300);
           
                        me->set_temp("nap-unarmed/lian", 1); 
						me->add_temp("apply/attack", 200);
						me->add_temp("apply/unarmed_damage", 200);
                        for (i = 0; i < 7; i++) 
                        { 
                                if (! me->is_fighting(victim)) 
                                        break; 
                  
                                if (! victim->is_busy() && random(2) == 1) 
                                        victim->start_busy(1); 
        
                                COMBAT_D->do_attack(me, victim, 0, 0); 
                        } 
                        me->delete_temp("nap-unarmed/lian"); 
						me->add_temp("apply/attack",-200);
						me->add_temp("apply/unarmed_damage", -200);
					  if (me->query_temp("count"))
			           me->delete_temp("count");
		               else
			           me->delete_skill("count", 300);
                 return;
                } 
                                        
        } 
}

