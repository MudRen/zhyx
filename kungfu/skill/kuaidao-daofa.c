// �쵶���� �ﲮ��֮���� 
// By dream@rx

#include <ansi.h>
inherit SKILL;

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", }); 

mapping *action = ({
      ([      "action": MAG"\n$N���һ��������$w�������ֱ�����£����кȵ�����һ����\n"NOR,
              "force" : 100, 
              "attack": 50, 
              "parry" : 40, 
              "damage": 150, 
              "lvl" : 0, 
              "skill_name" : "��һ��", 
              "damage_type":  "����" 
      ]), 
      ([      "action":CYN"\n$N���һ��������$w�������ֱ�����£����кȵ����ڶ�����\n"NOR,   
              "force" : 150, 
              "attack": 80, 
              "parry" : 60, 
              "damage": 200, 
              "lvl" : 80, 
              "skill_name" : "�ڶ���", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIR"\n$N���һ��������$w�������ֱ�����£����кȵ�����������\n"NOR,
              "force" : 200, 
              "attack": 110, 
              "parry" : 80, 
              "damage": 250, 
              "lvl" : 160, 
              "skill_name" : "������", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIG"\n$N���һ��������$w�������ֱ�����£����кȵ������ĵ���\n"NOR, 
              "force" : 250, 
              "attack": 140, 
              "parry" : 100, 
              "damage": 300, 
              "lvl" : 240, 
              "skill_name" : "���ĵ�", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIY"\n$N���һ��������$w�������ֱ�����£����кȵ������嵶��\n"NOR, 
              "force" : 300, 
              "attack": 160, 
              "parry" : 120, 
              "damage": 350, 
              "lvl" : 320, 
              "skill_name" : "���嵶", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIB"\n$N���һ��������$w�������ֱ�����£����кȵ�����������\n"NOR, 
              "force" : 350, 
              "attack": 180, 
              "parry" : 140,  
              "damage": 400, 
              "lvl" : 400, 
              "skill_name" : "������", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIM"\n$N���һ��������$w�������ֱ�����£����кȵ������ߵ���\n"NOR, 
              "force" : 400, 
              "attack": 200, 
              "parry" : 160, 
              "damage": 450, 
              "lvl" : 480, 
              "skill_name" : "���ߵ�", 
              "damage_type":  "����" 
      ]), 
      ([      "action":HIW"\n$N���һ��������$w�������ֱ�����£����кȵ����ڰ˵���\n"NOR, 
              "force" : 450, 
              "attack": 220, 
              "parry" : 200, 
              "damage": 500, 
              "lvl" : 560, 
              "skill_name" : "�ڰ˵�", 
              "damage_type":  "����" 
      ]), 
      }); 
      
int valid_enable(string usage) 
     { 
             return usage == "parry" || 
                    usage == "blade"; 
     } 
      
int double_attack() { return 1; }      

int valid_learn(object me) 
     {  
      
             if (me->query("gender") == "Ů��") 
                     return notify_fail("Ů�Բ�����������ѧ��\n"); 
      
             if (me->query("gender") == "����") 
      
             if (me->query_skill("blade", 1) < 200) 
                    return notify_fail("��Ļ�����������̫ǳ���޷������쵶������\n"); 
     
            return 1; 
     } 
      
string query_skill_name(int level) 
     { 
             int i; 
             for (i = sizeof(action) - 1; i >= 0; i--) 
                     if (level >= action[i]["lvl"]) 
                             return action[i]["skill_name"]; 
    } 
     
mapping query_action(object me, object weapon) 
     { 
             int i, level; 
             level = (int) me->query_skill("kuaidao-daofa", 1); 
             for (i = sizeof(action); i > 0; i--) 
                  if (level > action[i-1]["lvl"]) 
                             return action[NewRandom(i, 20, level/8)]; 
     } 
     
      
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time) 
     { 
             object weapon; 
             string name; 
      
             weapon = me->query_temp("weapon"); 
      
             if (me->query_temp("weapon")) 
                     name = "����" + weapon->name(); 
              else
                name = finger_name[random(sizeof(finger_name))];

             attack_time = (int)(me->query_skill("kuaidao-daofa", 1) / 40); 
      
             if (attack_time > 8) 
                     attack_time = 8; 
      
             if (me->is_busy() 
                || random(2) == 0 
                || ! living(victim) 
                || victim->is_busy() 
                || damage_bonus < 180 
                || me->query("neili") < 800 
                || me->query_temp("action_flag") == 0 
                || me->query_skill("kuaidao-daofa", 1) < 240) 
                     return 0; 
       
        if (! me->query_temp("kuaidao-daofa/hit_msg"))
                message_vision(BLINK HIW "\nֻ��$N" HIW "����˲�����ǰ��" + name +
                               HIW "�������쵶��������������$n" HIW "��\n"
                               NOR, me, victim);

        me->start_busy(1);
        me->add("neili", -attack_time * 20);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        return 1;
}

    
string perform_action_file(string action) 
     { 
             return __DIR__"kuaidao-daofa/" + action; 
     } 

