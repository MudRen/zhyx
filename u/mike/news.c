// news cmds
// by Doing
 
inherit F_CLEAN_UP;

#ifndef NEWS_D
#define NEWS_D          "/adm/daemons/newsd"
#endif

int main(object me, string arg)
{
        if (! arg || arg == "" || arg == "all")
        {
                NEWS_D->show_news(me, (arg != "all") ? 1 : 0);
                return 1;
        }

        if (sscanf(arg, "discard %s", arg))
        {
                NEWS_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                NEWS_D->do_post(me, arg);
                return 1;
        }
        if (sscanf(arg, "search %s", arg)) 
        { 
                NEWS_D->search_content(me, arg); 
                return 1; 
        } 

        NEWS_D->do_read(me, arg);
        return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : 	news [next] | [<新闻编号>] | new | all
			news search [关键字]

这条指令让你你可以阅读游戏中的新闻。所有的更新和消息都是通过
新闻发布的。

使用 new 参数可以让你阅读还没有读过的新闻。
使用 all 参数可以让你查看系统目前所有的新闻。

使用 news search [内容] 参数可以让你查找系统中含有 关键字 的所有的新闻。
例如：news search 中华英雄 系统会返回新闻中含有 中华英雄 的所有新闻。

总站的巫师可以通过news post <标题>来发布新闻。news discard来
删除新闻。
HELP );
    return 1;
}
