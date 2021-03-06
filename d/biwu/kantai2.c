// 山猫(adx) by snow 2000-05-15

inherit ROOM;

void create ()
{
        set ("short", "中看台");
        set ("long", @LONG
这是小雪初晴比武场的中看台，看台上有一排排的木制条凳。你坐在
这里一丈高的比武台上一切比武过招你都能看得非常清楚。这里还提供免
费的饮食。
LONG);
        set("no_fight",1);
        set("no_clean_up",1);
        set("exits", ([
                "up"   : __DIR__"biwutai",
                "northwest"   : __DIR__"kantai1",
                "northeast"   : __DIR__"kantai3",
                "south"   : __DIR__"zoulang",
        ]));
        setup();
}

void init()
{
        add_action ("do_work","ansuan");
}

int do_work()
{
        write("这里不能使用这个指令！\n");
        return 1;
}

int valid_leave(object me, string dir)
{
        object tai=load_object(__DIR__"biwutai");
        object *inv=all_inventory(tai);
        object ob, where;
        int i=sizeof(inv);

        if (!where=find_object(__DIR__"gate"))
                where=load_object(__DIR__"gate");
        ob=present("gongping zi", where);

        if ( !wizardp(me) && dir=="up" ) {
                if( ob->query("start/start") && !me->query("biwu_fighter") )
                        return notify_fail("比武已经开始了，你不是选手不能上台。\n");
                if(i>=2)
                        return notify_fail("比武台上已经有两名选手，你现在不能上台。\n");
        }
        return ::valid_leave(me, dir);
}

