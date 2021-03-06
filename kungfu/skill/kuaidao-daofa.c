// 快刀刀法 田伯光之刀法 
// By dream@rx

#include <ansi.h>
inherit SKILL;

string *finger_name = ({ "左手中指", "左手无名指", "左手食指",
                         "右手中指", "右手无名指", "右手食指", }); 

mapping *action = ({
      ([      "action": MAG"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第一刀！\n"NOR,
              "force" : 100, 
              "attack": 50, 
              "parry" : 40, 
              "damage": 150, 
              "lvl" : 0, 
              "skill_name" : "第一刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":CYN"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第二刀！\n"NOR,   
              "force" : 150, 
              "attack": 80, 
              "parry" : 60, 
              "damage": 200, 
              "lvl" : 80, 
              "skill_name" : "第二刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":HIR"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第三刀！\n"NOR,
              "force" : 200, 
              "attack": 110, 
              "parry" : 80, 
              "damage": 250, 
              "lvl" : 160, 
              "skill_name" : "第三刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":HIG"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第四刀！\n"NOR, 
              "force" : 250, 
              "attack": 140, 
              "parry" : 100, 
              "damage": 300, 
              "lvl" : 240, 
              "skill_name" : "第四刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":HIY"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第五刀！\n"NOR, 
              "force" : 300, 
              "attack": 160, 
              "parry" : 120, 
              "damage": 350, 
              "lvl" : 320, 
              "skill_name" : "第五刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":HIB"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第六刀！\n"NOR, 
              "force" : 350, 
              "attack": 180, 
              "parry" : 140,  
              "damage": 400, 
              "lvl" : 400, 
              "skill_name" : "第六刀", 
              "damage_type":  "砍伤" 
      ]), 
      ([      "action":HIM"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第七刀！\n"NOR, 
              "force" : 400, 
              "attack": 200, 
              "parry" : 160, 
              "damage": 450, 
              "lvl" : 480, 
              "skill_name" : "第七刀", 
              "damage_type":  "内伤" 
      ]), 
      ([      "action":HIW"\n$N大喝一声，手中$w如闪电般直劈而下，口中喝道：第八刀！\n"NOR, 
              "force" : 450, 
              "attack": 220, 
              "parry" : 200, 
              "damage": 500, 
              "lvl" : 560, 
              "skill_name" : "第八刀", 
              "damage_type":  "内伤" 
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
      
             if (me->query("gender") == "女性") 
                     return notify_fail("女性不能修炼此武学。\n"); 
      
             if (me->query("gender") == "男性") 
      
             if (me->query_skill("blade", 1) < 200) 
                    return notify_fail("你的基本刀法造诣太浅，无法修炼快刀刀法。\n"); 
     
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
                     name = "手中" + weapon->name(); 
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
                message_vision(BLINK HIW "\n只见$N" HIW "身形瞬间冲上前，" + name +
                               HIW "暴出满天刀气，如网般罩向$n" HIW "！\n"
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

