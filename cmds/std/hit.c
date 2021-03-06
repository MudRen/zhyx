// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;

        if (me->is_chatter())
                return 0;

        if (environment(me)->query("no_fight")
             || environment(me)->query("no_fight1") )
                return notify_fail("这里不准战斗。\n");

        if (! arg || ! objectp(obj = present(arg, environment(me))))
                return notify_fail("你想攻击谁？\n");

        if (! obj->is_character())
                return notify_fail("看清楚一点，那并不是你能招呼的对象。\n");

        if (! living(obj))
                return notify_fail("你还要打？不如杀了算了。\n");

        if (obj->is_fighting(me))
                return notify_fail("加油！加油！加油！\n");

        if (obj == me)
                return notify_fail("打自己？别这么想不开。\n");

       if ( me->query("special_skill/lonely") )
       {
           if (me->query_condition("killer") && obj->is_player())
           return notify_fail("你现在是官府捉拿的要犯，不可造次！\n");
       }
       else
     /*  if (obj->is_player() && me->query("quest_count") < 300 )    
           return notify_fail("完成300个门派任务才能袭击一次玩家。\n"); 
       if (obj->is_player())  return notify_fail("目前特殊时期，暂时关闭PK。\n"); */ 


        if ((int)obj->query_condition("die_guard"))
                return notify_fail("这个人正被官府保护着呢，还是别去招惹。\n");


        if ( obj->query("age") < 30 && ( obj->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("此人受上天庇佑且又尚未成年，还是别去招惹。\n");

        if ( obj->is_player() && me->query("age") < 30 
             && ( me->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("你在成年之前不能袭击玩家!\n");


        if (me->query("qi") < me->query("max_qi") * 3 / 10)
                return notify_fail("你现在没有力气战斗了。\n");

        if (obj->query("can_speak"))
                message_vision(HIW "\n$N" HIW "对著$n" HIW "大喝一声道：看"
                               "招！\n\n" NOR, me, obj);
        else
                message_vision(HIW "\n$N" HIW "大喝一声，开始对$n" HIW "发"
                               "动攻击！\n\n" NOR, me, obj);

        notify_fail("你无从下手。\n");
        switch (obj->accept_hit(me))
        {
        case 0:
                return 0;
        case -1:
                return 1;
        default:
        }

        me->fight_ob(obj);
        if (obj->query("can_speak"))
        {
                me->want_kill(obj);
                obj->fight_ob(me);
        } else
                obj->kill_ob(me);

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : hit <人物>
 
这个指令让你直接向一个人物「进招」。这种形式的战斗是即时的，只要玩家一
敲这个命令，战斗就会开始，直到某一方受伤50% 以上为止。这个指令对那些不
喜欢fight的NPC很有用，因为很多时候你的比武要求会被拒绝。不过使用这个命
令有可能遭到NPC 的强烈反应，所以要小心使用。
 
其他相关指令: fight, kill

HELP
    );
    return 1;
}


