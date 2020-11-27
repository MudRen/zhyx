// File(/data/room/lxm/qianting.c) of lxm's room
// Create by LUBAN written by Doing Lu

#include <ansi.h> 
     inherit PRIVATE_ROOM;

void create()
{
        object ob;

        set("short", "飘渺之城前庭");
	set ("long", @LONG
这里似乎非常安静，听不到什么声响，到是时不时听见鸟儿唧唧
喳喳的叫。院中不少树木已然有遮天之势，肃穆非常。 
LONG );

	set("exits", ([
                "south"  : __DIR__"dayuan",
                "east"   : __DIR__"zuowei",
                "west"   : __DIR__"youwei",
	]));

        set("objects", ([
                "/d/room/roomnpc/laopu" : 1,
        ]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        set("gate", "close");
        setup();

        set("room_owner", "慕容星雅");
        set("room_name", "飘渺之城");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "南大街");
}

void init()
{
        add_action("do_push", "push");
        add_action("do_close", "close");       
        add_action("set_code", "setcode");
        add_action("type_code", "typecode");
}

int set_code(string arg)
{
	object me;
       me = this_player();
       if ( me->query("id") != query("room_owner_id") )
       return notify_fail(HIR"不是屋主不能设定密码!\n"NOR);
       if ( !arg) 
       return notify_fail("你要把密码设定成什么?\n");
       if ( sizeof(arg) > 10 ) 
       return notify_fail("密码长度不能超过10个字符!\n");

       this_object()->set("code", arg);  
       write(HIG"设定了密码为" + arg +"\n"NOR);     
       save();
       return 1;
}

int type_code(string arg)
{
       object me = this_player();
       if ( me->query("id") == query("room_owner_id") )
       return notify_fail(HIG"屋主不用输入密码!\n"NOR);
       if ( !arg ) 
       return notify_fail("你要输入什么密码?\n");
       if ( arg != query("code") )
       return notify_fail(HIR"对不起，密码错误，你不能进入这所房子！\n"NOR);
       me->set_temp("roomcode_ok/" + query("room_owner_id"),1); 
       write(HIG"密码正确，你可以push gate开门了。\n"NOR);
       return 1;

}

int do_push()
{
        object ob;
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大门开着呢，你还推什么？\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (me && (! ob || ! living(ob) || ob->is_owner_permit(me) || ! query("code") ))
        {
                message_vision("$N用力一推大门，就听见大门“吱呀呀”的开了。\n",
                               me);
        } else
        if (me && ! ob->is_owner(me))
        {                     
               if ( ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
               { 
                 write(HIR"要进屋得先用typecode输入密码!\n"NOR);
                 return 1; 
               }  else
               {
                  message("vision",  "大门“吱呀呀”的被人打开了。\n",
                  this_object());                  
               }          
               
        } else
        if (ob && living(ob))
        {
                message_vision("$n连忙跑上前来，对$N道：“主人何必亲"
                        "劳，我来吧！”\n$n走上前去，用力将大门“吱呀"
                        "呀”的推开了。\n", me, ob);
        } else
        {
                message("vision",  "大门“吱呀呀”的被人打开了。\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "大门“吱呀呀”的被人推开了。\n", room);       
        set("gate", "open");
        set("exits/north", __DIR__"zoudao");
        room->set("exits/south", __FILE__);
        room->set("gate", "open");
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object ob;
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大门关着呢，你还再关一遍？\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (! n && me && (! ob || ! living(ob)))
        {
                message_vision("$N用力一拉大门，就听见大门“吱呀呀”的关上了。\n",
                               me);
        } else
        if (! n && me && ! ob->is_owner(me))
        {
                message_vision("$N走上前去，用力合上大门。\n", me);
        } else
        if (! n && me && ob->is_owner(me))
        {
                message_vision("$n连忙跑上前来，对$N道：“主人何必"
                        "亲劳，我来吧！”\n$n走上前去，用力合上大门。\n",
                        me, ob);
        } else
        if (ob && living(ob))
        {
                message("vision", ob->name() + "走上前去，用力合上大门。\n",
                        this_object());
        } else
        {
                message("vision", "大门“吱呀呀”的被人关上了。\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "大门“吱呀呀”的被人关上了。\n", room);
        set("gate", "close");
        delete("exits/north");
        room->delete("exits/south");
        room->set("gate", "close");
        return 1;
}

string long()
{
        string msg;
        msg = "    ";
        if (present("lao jiaren"))
                msg += "一老家人慢慢的挥舞着扫把，打扫着落叶。";

        if (query("gate") != "open")
                msg += "向北望去，有一扇大门紧紧的关闭着。";
        else
                msg += "大门畅开，远远望去，隐然可见迎客厅。";

        return query("long") + sort_string(msg, 60, 0);
}

int valid_leave(object me, string dir)
{
        object ob;

        ob = present("saodi laopu", this_object());

            if ( dir == "north" &&  me->query("id") != query("room_owner_id") 
                     && query("code") &&
                 ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
            { 
                     write(HIR"要进屋得先用typecode输入密码!\n"NOR);
                     return 0; 
            }  
        if (dir != "north" || ! objectp(ob) || ! living(ob))
                return ::valid_leave(me, dir);

        if (ob->is_owner(me))
        {
            if ( ! query("code") )
            { message_vision(HIR"$N对$n小声道：“主人,您还未用setcode设置密码！”\n"NOR, ob, me);}
            else
               {
                message_vision("$N弯腰对$n道：“主人请进！”\n", ob, me);
               }
                return ::valid_leave(me, dir);
        }

        if (ob->is_owner_permit(me))
        {
                message_vision("$N对$n道：“即然是主人的朋友，但进无妨。”\n",
                               ob, me);
                return ::valid_leave(me, dir);
        }

        message_vision("$N对$n道：“既然知道密码定是主人朋友，但进无妨”\n", ob, me);
        me->delete_temp("roomcode_ok/" + query("room_owner_id") ); 
        return 1;
}

