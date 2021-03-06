// touxi.c 偷袭
// by King 97.05
// Update by vin for heros.cn

#include <ansi.h>

int main(object me, string arg)
{
        object obj;
        int skill, count;

        if (environment(me)->query("no_fight")
             || environment(me)->query("no_fight1") )
                return notify_fail("这里不准战斗。\n");

        // 执行天书任务的特殊房间防止偷袭中断剧情。
        if (environment(me)->query("skybook"))
                return notify_fail("在这里不能攻击他人。\n");

        if (! arg || ! objectp(obj = present(arg, environment(me))))
                return notify_fail("你想偷袭谁？\n");

        if (me->is_chatter())
                return notify_fail("你这个样子有什么好偷袭的？\n");

        if (! obj->is_character())
                return notify_fail("看清楚一点，那并不是生物。\n");

        if (obj->is_fighting(me))
                return notify_fail("你已经在战斗中了，还想偷袭？\n");

        if (! living(obj))
                return notify_fail(obj->name() + "都已经这样了，你还用"
                                   "得着偷袭吗？\n"); 

        if (obj == me)
                return notify_fail("偷袭自己？别这么想不开。\n");

        if (me->is_busy())
                return notify_fail("你的动作还没有完成，不能偷袭。\n");

        if (obj->query_competitor())
                return notify_fail("人家比武你要偷袭？真是太不要脸了。\n");

        if ((int)obj->query_condition("die_guard"))
                return notify_fail("这个人正被官府保护着呢，还是别去招惹。\n");

       if ( me->query("special_skill/lonely") )
       {
           if (me->query_condition("killer") && obj->is_player())
           return notify_fail("你现在是官政府捉拿的要犯，不可造次！\n");
       }
       else
       /*  if (obj->is_player() && me->query("quest_count") < 300 )    
           return notify_fail("完成300个门派任务才能袭击一次玩家。\n"); */

        if ( obj->query("age") < 30 && ( obj->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("此人受上天庇佑且又尚未成年，还是别去招惹。\n");


        if ( obj->is_player() && me->query("age") < 30 
             && ( me->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("你在成年之前不能袭击玩家!\n");


        tell_object(me, HIW "\n你猛的飞身纵起，直扑" + obj->name() +
                        HIW "而去。\n" NOR);

        tell_object(obj, HIW "\n" + me->name() + HIW "忽然向你扑来"
                         "，来势甚为迅猛。\n" NOR);

        message("vision", HIW "\n" + me->name() + HIW "一声冷笑，忽"
                          "然向" + obj->name() + HIW "直扑而去。\n"
                          NOR, environment(me), ({me, obj}));

        switch (obj->accept_touxi(me))
        {
        case 0:
                return 0;
        case -1:
                return 1;
        }

        count = me->query_str();

        if (userp(me) && userp(obj) && ! obj->is_want_kill(me->query("id")) )
                me->want_kill(obj);

        me->kill_ob(obj);

        if (random(me->query("combat_exp")) < (int)obj->query("combat_exp") / 2)
        {
                me->add_temp("str", count * 4);
                COMBAT_D->do_attack(me, obj, me->query_temp("weapon") );
                me->add_temp("str", - count * 4);
        } else
        {
                COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
                COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
                COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
        }

        me->start_busy(3);
        obj->kill_ob(me);

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : touxi <人物>
 
这个指令用来向敌人偷袭。偷袭不成时，则会招至反击。特别适合于
经验低的玩家向经验高的玩家拚命。

其他相关指令: fight, kill, hit
HELP);
    return 1;
}
