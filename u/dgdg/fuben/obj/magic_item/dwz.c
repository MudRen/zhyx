
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
        set_name(HIG "¶«»ÊÖÓ" NOR, ({ "donghuang zhong","zhong" }));
        set_weight(15000);        
        set("special", 1);
        set("unit", "¼ş");        
        set("long", "[1;32mÕâÊÇÒ»¿ÚÍ¸×Å¹ÅÒâµÄÍ­ÖÓ£¬È´¼áÓ²ÎŞ±È£¬Í¨ÌåÉ¢·¢×Åµ­µ­µÄÏ¼¹â¡£
ÉÏÃæÒşÔ¼»¹»­×ÅĞí¶àÉñÃØ·ûºÅ£¬É¢·¢×ÅÎŞĞÎµÄÁ¦Á¿£¬È´¸øÈËÒ»ÖÖ°²È«¸Ğ¡£[2;37;0m\n");   
        set("point", 560);
        set("no_sell", 1 ); 
        set("value",1000000); 
        set("no_steal", 1);      
        set("material", "tian jing");
      /*  set("wear_msg", HIG "ĞşÒôÉ´ºá¿Õ³öÊÀ£¬Ï¼¹âËÄÉä£¬ÍğÈç°ÙÄñ³¯·ï°ã·ÉÖÁ$N£¬\n"
                            "É²Ê±±ãÓë$NºÏ¶øÎªÒ»¡£\n" NOR);
        set("remove_msg", HIC "$N" HIC "Ò»ÉùÇáÌ¾£¬µ«¼ûĞşÒôÉ´Ëæ·çÇá°Ú£¬¶ÙÊ±ÏûÊ§ÓÚÎŞĞÎ¡£\n" NOR);  */
      /*  if (! check_clone()) return;
        restore(); */
        set("armor_prop/dodge", 100);
        set("armor_prop/parry", 100);
        set("armor_prop/armor", 200);
        setup();
}

 //string long() { return query("long") + item_long(); }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "ÇáÇáÒ»Ì¾£¬ÉíÉÏ" HIC "ĞşÒôÉ´" HIR "¶£ßÊ"
                                            "×öÏì£¬$N" HIR "Ö»¾õĞÄÍ·Ò»ÕóÆà¿à¡£ÕâÒ»ÕĞ¾ÓÈ»´ò²»ÏÂÈ¥¡£\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "Ö»¼û$n" HIM "ÉíÉÏ" HIC "ĞşÒôÉ´" HIM "Ò»²ü£¬ÓĞ"
                                            "Èô·ïÃù¡£" HIM "$N" HIM "ÄãÖ»¸ĞÍ·ÔÎÄ¿Ñ££¬¾ÓÈ»Ò»ÕĞ´òÔÚ¿Õ´¦¡£\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "Ò»ÕĞ´òÖĞ$n" HIW "£¬¶Ù¾õºÁ²»ÊÜÁ¦¡£¶¨¾¦Ò»¿´£¬Ô­À´ÊÇ"
                                            "µÄ" HIC "ĞşÒôÉ´" HIW "»Ã»¯³öÀ´µÄ»ÃÏó¡£\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "ÉíÉÏ" HIC "ĞşÒôÉ´" HIY "Ò»ÕóÏ¼¹âÉÁ¹ı£¬$N" HIY "ÕâÒ»"
                                            "ÕĞ±»Ï¼¹âÀÎÀÎµ²×¡£¬ÉË²»ÁË$n" HIY "·ÖºÁ¡£\n" NOR]);
                        break;
                }
                return result;
        }
}

/*
void init()
{
    add_action("do_canwu", "canwu");  
    add_action("do_linghui", "linghui");      
}

int do_canwu( string arg )
{
   object me;
   int s_skill, t_skill;

   me = this_player();

   if ( ! arg || arg != "xuanyin")
      return notify_fail("ÄãÒª²ÎÎòÊ²Ã´?\n");

   if ( ! me->query("special_skill/queen") )
      return notify_fail("Äã¶Ô×ÅĞşÒôÉ´¶ËÏêÁË°ëÌì£¬"
                         "·¢ÏÖÆÕÍ¨ÈËËÆºõÄÑÒÔ´ÓÖĞÁì»áµ½ÈÎºÎĞş»ú¡£\n");


   s_skill = (int)me->query_skill("sword", 1);
   t_skill = (int)me->query_skill("xuannv-jian", 1);

        if (s_skill < t_skill)
        {
                message_vision("$N¶Ô»ù±¾½£·¨µÄÁË½âÌ«µÍ£¬ÎŞ"
                               "·¨ÁìÎòĞşÒôÉ´ÉÏµÄÄÚÈİ¡£\n", me);
                return 1; 
        }

        if (me->query("jing")< 90)
        {
                message_vision("$NÌ«ÀÛÁË£¬ÏÖÔÚÎŞ·¨ÁìÎòĞşÒôÉ´ÉÏµÄÄÚÈİ¡£\n",me);
                return 1; 
        }

        if (t_skill >= 180)
        {
                message_vision("$N¾õµÃĞşÒôÉ´ÉÏµÄÄÚÈİÌ«·ôÇ³ÁË¡£"
                               "ÊÔÊÔ(linghui ¾øÕĞ)°É\n", me);
                return 1;
        }

        message_vision("$N×ĞÏ¸²ÎÎòĞşÒôÉ´ÉÏËùÔØµÄÃÜ¼®£¬¶ÔĞşÅ®"
                       "½£·¨ËÆÓĞËùÎò¡£\n", me);
        me->improve_skill("xuannv-jian", 1 + random(me->query("int")));
        me->receive_damage("jing", 75);
    return 1;
}

int do_linghui( string arg )
{
    object me = this_player();
    

    if ( ! me->query("special_skill/queen") )
        return 0;    
  
    if (me->is_busy())
          return notify_fail("ÄãÏÖÔÚÕıÃ¦×ÅÄØ¡£\n");

    if (me->is_fighting())
          return notify_fail("Äã»¹ÊÇÏÈ´òÍê¼ÜÔÙËµ°É£¡\n");

    if ( ! arg || ( arg != "Î¢·çÇá·÷Ãæ" && arg != "ÈËÃæÌÒ»¨ºì") )
          return notify_fail("ÄãÒªÁì»áÊ²Ã´¾øÕĞ£¿¸ñÊ½Îª(linghui ¾øÕĞ)¡£\n");

    if ( arg == "Î¢·çÇá·÷Ãæ" 
        && me->query("can_perform/xuannv-jian/qingfu"))
          return notify_fail("ÕâÕĞÄã²»ÊÇÒÑ¾­»áÁËÂğ£¿\n");
  
    if ( arg == "ÈËÃæÌÒ»¨ºì" 
        && me->query("can_perform/xuannv-jian/taohua"))
          return notify_fail("ÕâÕĞÄã²»ÊÇÒÑ¾­»áÁËÂğ£¿\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("ÄãµÄ¾«Á¦ÎŞ·¨¼¯ÖĞ£¬ÎŞ·¨Áì»á¾øÕĞ£¡\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(10) == 1 && arg == "Î¢·çÇá·÷Ãæ" )
    {
        me->add("xuannv-jian/qingfu/count", 1);

        if (me->query("xuannv-jian/qingfu/count") >= 10)
        {
            write(HIM "ÃÍÈ»¼ä£¬ÄãĞØÖĞ»íÈ»¹áÍ¨£¬ÔÙÎŞÒÉÂÇ¡£\n" NOR);
            write(HIC "ÄãÖÕÓÚÍ¨ÏşÁË¾øÑ§¡¸Î¢·çÇá·÷Ãæ¡¹¡£\n" NOR);

            me->set("can_perform/xuannv-jian/qingfu", 1);
            me->delete("xuannv-jian/qingfu/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "Äã¶Ô¡¸Î¢·çÇá·÷Ãæ¡¹ÕâÕĞÓĞÁËĞÂµÄÈÏÊ¶£¬µ«ÊÇÈÔÓĞĞí¶à²»½âÖ®´¦¡£\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "ÈËÃæÌÒ»¨ºì")
    {
        me->add("xuannv-jian/taohua/count", 1);

        if (me->query("xuannv-jian/taohua/count") >= 20)
        {
            write(HIM "ÃÍÈ»¼ä£¬ÄãĞØÖĞ»íÈ»¹áÍ¨£¬ÔÙÎŞÒÉÂÇ¡£\n" NOR);
            write(HIC "ÄãÖÕÓÚÍ¨ÏşÁË¾øÑ§¡¸ÈËÃæÌÒ»¨ºì¡¹¡£\n" NOR);

            me->set("can_perform/xuannv-jian/taohua", 1);
            me->delete("xuannv-jian/taohua/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "Äã¶Ô¡¸ÈËÃæÌÒ»¨ºì¡¹ÕâÕĞÓĞÁËĞÂµÄÈÏÊ¶£¬µ«ÊÇÈÔÓĞĞí¶à²»½âÖ®´¦¡£\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
        return notify_fail("ÄãÊÔÍ¼´ÓĞşÒôÉ´ÉÏÁì»áÓĞ¹Ø¡¸" + arg + "¡¹µÄÄÚÈİ£¬\n"
                           "µ«ÊÇÕâ´ÎÃ»Ê²Ã´Ğ§¹û£¬¿´À´µÃÔÙÀ´¹ı£¡\n");

}
*/



void owner_is_killed()
{
        destruct(this_object());
} 
