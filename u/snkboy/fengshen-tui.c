#include <ansi.h> 
#include <combat.h> 
inherit SKILL;

string *xue_name = ({ 
"ÀÍ¹¬Ñ¨", "ëþÖÐÑ¨", "Çú³ØÑ¨", "¹ØÔªÑ¨", "Çú¹ÇÑ¨", "ÖÐ¼«Ñ¨", "³Ð½¬Ñ¨", "ÌìÍ»Ñ¨", "°Ù»áÑ¨",
"ÓÄÃÅÑ¨", "ÕÂÃÅÑ¨", "´óºáÑ¨", "×Ï¹¬Ñ¨", "ÀäÔ¨Ñ¨", "Ìì¾®Ñ¨", "¼«ÈªÑ¨", "ÇåÁéÑ¨", "ÖÁÑôÑ¨", });

string *attack_name = ({
"·çÉñÍÈ¾¢", "¿ñ·çÉ¨ÂäÒ¶¾¢Æø", "Ä¦Ú­ÎÞÁ¿Ðþ¾¢", "ÈýºÏÎªÒ»µÄ°ÔÁÒÕæÆø", });

string *parry_msg = ({
       "$nÒÔ"+MAG"¡¸·çÉñÍÈ¾¢¡¹"NOR+"»¤Ìå£¬Éí±ß¾¹ÐýÆðÒ»ÕóÐý·ç£¬ÈÃ$NÄ¿µÉ¿Ú´ô¡£\n",
      "$nÔÚÕâÉ²ÄÇ¼ä£¬ÉíÌå±äµÃÈáÈõÎÞ¹Ç£¬¸øÔÚÈËÒ»ÖÖÆæÒìµÄ¸Ð¾õ£¬ÕâÕýÊÇÀ´×ÔÍâÓòµÄ"+HIM"¡¸è¤çìÆæÊõ¡¹\n",
       "$nÔËÆð"+CYN"¡¸¿ñ·çÉ¨ÂäÒ¶¾¢Æø¡¹"NOR+"ÓÌÈçÌìÉñÁÙÊÀ,$NµÄÕÐÊ½ÔÙÒ²²»Ê¹²»ÏÂÈ¥ÁË¡£\n",
        "$n´óºÈÒ»Éù£¬ÒÔ"+RED"¡¸Ä¦Ú­ÎÞÁ¿Ðþ¾¢¡¹"NOR+"Ö®Íþ£¬ÕðÉåÔÚ³¡ÖÚÈË¡£¾¹ÎÞÈË¸Ò³öÊÖÁË¡£\n",
});

mapping *action = ({
([      "action" : "$NË«ÊÖÐé»Î£¬×ó½ÅÃÍµØ·ÉÆð£¬Ò»Ê½[1;36m¡¸·ç¾íÂ¥²Ð¡¹[0m,[1;33m£¬ÌßÏò$nµÄ$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "·çÉñÍÈ¾¢" NOR,
        "damage_type" : "ðöÉË",
        "skill_name"  : "·ç¾íÂ¥²Ð"
]),
([      "action" : "$N×ó½Å¶ÙµØ£¬ÉíÐÎÃÍ×ª£¬ÓÒ½ÅÒ»Ê½[1;36m¡¸·çÖÐ¾¢²Ý¡¹[0m,[1;33m£¬ÃÍõß$nµÄ$l",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "¿ñ·çÉ¨ÂäÒ¶¾¢Æø" NOR,
        "damage_type" : "ðöÉË",
        "skill_name"  : "·çÖÐ¾¢²Ý"
]),
([      "action" : "$NÓÒ½Å·ÉÒ»°ãõß³ö£¬¼ÈÃÍÇÒ×¼£¬Ò»Ê½[1;36m¡¸À×À÷·çÐÐ¡¹[0m,[1;33m£¬ÌßÏòµÄ$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "Ä¦Ú­ÎÞÁ¿Ðþ¾¢" NOR,
        "damage_type" : "ðöÉË",
        "skill_name"  : "À×À÷·çÐÐ"
]),
([      "action" : "$NË«×ãÁ¬»·È¦×ª£¬Ò»Ê½[1;36m¡¸±©·çÖèÓê¡¹[0m,[1;33m£¬×ã´ø·ç³¾£¬¹¥Ïò$nµÄÈ«Éí",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "Ä¦Ú­ÎÞÁ¿Ðþ¾¢" NOR,
        "damage_type" : "ðöÉË",
        "skill_name"  : "±©·çÖèÓê"
]),
([      "action" : "$NË«½Å½»²æÌßÆð£¬Ò»Ê½[1;36m¡¸ß³ßå·çÔÆ¡¹[0m,[1;33m£¬½Å½Å²»Àë$nµÄÃæÃÅ×óÓÒ",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "ÈýºÏÎªÒ»µÄ°ÔÁÒÕæÆø" NOR,
        "damage_type" : "ðöÉË",
        "skill_name"  : "ß³ßå·çÔÆ"
]),
});

string *usage_skills = ({ "unarmed", "parry" });

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
      return notify_fail("·çÉñÍÈ²©´ó¾«Éî£¬ÎÞ·¨¼òµ¥µÄÍ¨¹ýÁ·Ï°½ø²½¡£\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fengshen-tui", 1);

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("Äã¶Ô»ù±¾È­½ÅµÄÀí½â»¹²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·çÉñÍÈ¡£\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("Äã¶Ô»ù±¾ÕÐ¼ÜµÄÀí½â»¹²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·çÉñÍÈ¡£\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("ÄãµÄÎäÑ§ÐÞÑø²»¹»£¬ÎÞ·¨¼ÌÐøÁì»á¸ü"
                                   "¸ßÉîµÄ·çÉñÍÈ¡£\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fengshen-tui", 1) > 300)
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
        int ap, dp, sk1, sk2, lvl, ran;
        string msg;

        sk1 = ob->query_skill("paiyun-zhang", 1); 
        sk2 = me->query_skill("fengshen-tui", 1); 
//        ap = ob->query_skill("parry");
        ap = ob->query_skill("fanyun-daofa", 1);
        dp = me->query_skill("fengshen-tui", 1);

        lvl = ob->query_skill("paiyun-zhang", 1);

        if (lvl > 100) ran = 20;
        if (lvl > 200) ran = 15;
        if (lvl > 300) ran = 10;
        if (lvl > 400) ran = 8;
        if (lvl > 500) ran = 5;

        if (dp/2 > ap)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "ÒÔ"HIR"¡¸·çÉñÍÈ¾¢¡¹»¤Ìå£¬Éí±ß¾¹ÐýÆðÒ»,"
                                                  "ÕóÐý·ç£¬ÈÃ$NÄ¿µÉ¿Ú´ô¡£\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "ÔÚÕâÉ²ÄÇ¼ä£¬ÉíÌå±äµÃÈáÈõÎÞ¹Ç£¬¸ø"
                                                  "ÈËÒ»ÖÖÆæÒìµÄ¸Ð¾õ£¬ÕâÕýÊÇÀ´×ÔÍâÓòµÄ"HIM"¡¸è¤çìÆæÊõ¡¹¡£\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "ÔËÆð"CYN"¡¸¿ñ·çÉ¨ÂäÒ¶¾¢Æø¡¹£¬ÓÌÈçÌìÉñÁÙÊÀ,"
                                                   "$NµÄÕÐÊ½ÔÙÒ²²»¸Ò³öÊÖ¡£\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "´óºÈÒ»Éù£¬ÒÔ"RED"¡¸Ä¦Ú­ÎÞÁ¿Ðþ¾¢¡¹Ö®Íþ£¬"
                                                     "ÕðÉåÔÚ³¡ÖÚÈË¡£¾¹ÎáÈË¸Ò³öÊÖÁË¡£\n" NOR]);
                        break;
                }
                return result;
        }
        else
        if (sk1/2 > sk2 && random(ran) == 1)
        {
//                msg = "$N¾¹ÔËÆðÅÅÔÆÕÆ·¨£¬½«Æä°ÂÒå·¢»ÓµÃÁÜÀì¾¡ÖÂ£¬$n¾¹Ò»Ê±ÕÒ²»³öÆÆÕÀ£¬´¦´¦ÊÜÖÆ£¡";
                msg = HIY + msg + NOR; 
                msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 200, 
                HIR"$N¾¹ÔËÆðÅÅÔÆÕÆ·¨£¬½«Æä°ÂÒå·¢»ÓµÃÁÜÀì¾¡ÖÂ£¬$n¾¹Ò»Ê±ÕÒ²»³öÆÆÕÀ£¬´¦´¦ÊÜÖÆ£¡"NOR);
//                COMBAT_D->set_bhinfo(msg); 
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fengshen-tui/perform/" + action;
}




