// poshan-dao.c ·­ÔÆµ¶·¨

#include <ansi.h>
inherit SKILL;

string *xue_name = ({ 
"ÀÍ¹¬Ñ¨", "ëþÖÐÑ¨", "Çú³ØÑ¨", "¹ØÔªÑ¨", "Çú¹ÇÑ¨", "ÖÐ¼«Ñ¨", "³Ð½¬Ñ¨", "ÌìÍ»Ñ¨", "°Ù»áÑ¨",
"ÓÄÃÅÑ¨", "ÕÂÃÅÑ¨", "´óºáÑ¨", "×Ï¹¬Ñ¨", "ÀäÔ¨Ñ¨", "Ìì¾®Ñ¨", "¼«ÈªÑ¨", "ÇåÁéÑ¨", "ÖÁÑôÑ¨", });

string *attack_name = ({
"·­ÔÆµ¶Æø", "¸²Óêµ¶Æø", "·­½­µ¹º£Ðþ¾¢", "Ìì·­µØ¸²ÎÞÉÏÐþ¹¦", });

string *parry_msg = ({
       "$nÒÔ"+MAG"¡¸·­ÔÆµ¶Æø¡¹"NOR+"»¤Ìå£¬Éí±ß¾¹ÐýÆðÒ»ÕóÐý·ç£¬ÈÃ$NÄ¿µÉ¿Ú´ô¡£\n",
      "$nÔÚÕâÉ²ÄÇ¼ä£¬ÉíÌå±äµÃÈáÈõÎÞ¹Ç£¬¸øÔÚÈËÒ»ÖÖÆæÒìµÄ¸Ð¾õ£¬ÕâÕýÊÇÀ´×ÔÍâÓòµÄ"+HIM"¡¸è¤çìÆæÊõ¡¹\n",
       "$nÔËÆð"+CYN"¡¸Ìì·­µØ¸²ÎÞÉÏÐþ¹¦¡¹"NOR+"ÓÌÈçÌìÉñÁÙÊÀ,$NµÄÕÐÊ½ÔÙÒ²²»Ê¹²»ÏÂÈ¥ÁË¡£\n",
        "$n´óºÈÒ»Éù£¬ÒÔ"+RED"¡¸·­½­µ¹º£Ðþ¾¢¡¹"NOR+"Ö®Íþ£¬ÕðÉåÔÚ³¡ÖÚÈË¡£¾¹ÎÞÈË¸Ò³öÊÖÁË¡£\n",
});

mapping *action = ({
([      "action" : "$NÎÕ½ôÊÖÖÐ$wÒ»ÕÐ¡¸·­ÔÆÒ»µ¶¡¹µãÏò$nµÄ$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "·­ÔÆµ¶Æø" NOR,
        "damage_type" : "¸îÉË"
]),
([      "action" : "$NÏòÇ°¿çÉÏÒ»²½£¬ÊÖÖÐ$wÊ¹³ö¡¸·­ÔÆ¸²Óê¡¹¿³Ïò$nµÄºí²¿",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "¸²Óêµ¶Æø" NOR,
        "damage_type" : "¸îÉË"
]),
([      "action" : "Ö»¼û$NÂÕÆðÊÖÖÐµÄ$w£¬Ê¹³ö¡¸·­½­µ¹º£¡¹Íòµã½ð¹âÖ±Åü$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "·­½­µ¹º£Ðþ¾¢" NOR,
        "damage_type" : "ÅüÉË"
]),
([      "action" : "$NÊ¹³ö¡¸½Áº£·­½­¡¹£¬ÊÖÖÐ$wÈç¹ÎÆð¿ñ·çÒ»°ãÉÁË¸²»¶¨£¬¸îÏò$n",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "¸²Óêµ¶Æø" NOR,
        "damage_type" : "¸îÉË"
]),
([      "action" : "$NËæÊÖÊ¹³öµ¶·¨Ö®°ÂÒå¡¸·­ÊÖÎªÔÆ¡¹£¬ÊÖÖÐ$wÈç¹í÷ÈÒ»°ãÆÌÌì¸ÇµØµÄ¿³Ïò$n",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "·­½­µ¹º£Ðþ¾¢" NOR,
        "damage_type" : "¸îÉË"
]),
([      "action" : HIY"$NÊ¹³ö·­ÔÆµ¶·¨Ö®×îÖÕ¾ø¼¼[1;36m¡¸Ìì·­µØ¸²¡¹[0m,[1;33mÊÖÖÐ$wÓÌÈçòÔÁúÒ»°ãÅüÏò$n[0m"NOR,
        "force" : 1000,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 500,
        "weapon": WHT "Ìì·­µØ¸²ÎÞÉÏÐþ¹¦" NOR,
        "damage_type" : "¸îÉË"
]),
});


string *usage_skills = ({ "blade", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
int practice_skill(object me)
{
      return notify_fail("·­ÔÆµ¶·¨²©´ó¾«Éî£¬ÎÞ·¨¼òµ¥µÄÍ¨¹ýÁ·Ï°½ø²½¡£\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fanyun-daofa", 1);

        if (me->query_skill("blade", 1) < level)
                return notify_fail("Äã¶Ô»ù±¾µ¶·¨µÄÀí½â»¹²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·­ÔÆµ¶·¨¡£\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("Äã¶Ô»ù±¾ÕÐ¼ÜµÄÀí½â»¹²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·­ÔÆµ¶·¨¡£\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("ÄãµÄÎäÑ§ÐÞÑø²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·­ÔÆµ¶·¨¡£\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fanyun-daofa", 1) > 300)
       return 1200;
       else   return 1000;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        me->add("neili", me->query("jiali") / 3);

        if (victim->query("neili") < 500)
                victim->set("neili", 0);
        else
                victim->add("neili", -300);

        return NOR + HIR "$n" HIR "½ÓÏÂ$N" HIR "Ò»ÕÐ£¬" + name2 + "¶ÙÊ±ÆÆÌå¶ø"
               "Èë£¬È«ÉíÕæÆøÓÉ" + name1 + "¿ñÐº¶ø³ö¡£\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("fanyun-daofa", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "ÒÔ"HIR"¡¸·­ÔÆµ¶Æø¡¹»¤Ìå£¬Éí±ß¾¹ÐýÆðÒ»,"
                                                  "ÕóÐý·ç£¬ÈÃ$NÄ¿µÉ¿Ú´ô¡£\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "ÔÚÕâÉ²ÄÇ¼ä£¬ÉíÌå±äµÃÈáÈõÎÞ¹Ç£¬¸ø"
                                                  "ÈËÒ»ÖÖÆæÒìµÄ¸Ð¾õ£¬ÕâÕýÊÇÀ´×ÔÍâÓòµÄ"HIM"¡¸è¤çìÆæÊõ¡¹¡£\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "ÔËÆð"CYN"¡¸Ìì·­µØ¸²ÎÞÉÏÐþ¹¦¡¹£¬ÓÌÈçÌìÉñÁÙÊÀ,"
                                                   "$NµÄÕÐÊ½ÔÙÒ²²»¸Ò³öÊÖ¡£\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "´óºÈÒ»Éù£¬ÒÔ"RED"¡¸·­½­µ¹º£Ðþ¾¢¡¹Ö®Íþ£¬"
                                                     "ÕðÉåÔÚ³¡ÖÚÈË¡£¾¹ÎáÈË¸Ò³öÊÖÁË¡£\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fanyun-daofa", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fanyun-daofa/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"fanyun-daofa/exert/" + action;
}


