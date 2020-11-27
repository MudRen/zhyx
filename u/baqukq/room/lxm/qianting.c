// File(/data/room/lxm/qianting.c) of lxm's room
// Create by LUBAN written by Doing Lu

#include <ansi.h> 
     inherit PRIVATE_ROOM;

void create()
{
        object ob;

        set("short", "Ʈ��֮��ǰͥ");
	set ("long", @LONG
�����ƺ��ǳ�������������ʲô���죬����ʱ��ʱ�����������
�����ĽС�Ժ�в�����ľ��Ȼ������֮�ƣ����·ǳ��� 
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

        set("room_owner", "Ľ������");
        set("room_name", "Ʈ��֮��");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "�ϴ��");
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
       return notify_fail(HIR"�������������趨����!\n"NOR);
       if ( !arg) 
       return notify_fail("��Ҫ�������趨��ʲô?\n");
       if ( sizeof(arg) > 10 ) 
       return notify_fail("���볤�Ȳ��ܳ���10���ַ�!\n");

       this_object()->set("code", arg);  
       write(HIG"�趨������Ϊ" + arg +"\n"NOR);     
       save();
       return 1;
}

int type_code(string arg)
{
       object me = this_player();
       if ( me->query("id") == query("room_owner_id") )
       return notify_fail(HIG"����������������!\n"NOR);
       if ( !arg ) 
       return notify_fail("��Ҫ����ʲô����?\n");
       if ( arg != query("code") )
       return notify_fail(HIR"�Բ�����������㲻�ܽ����������ӣ�\n"NOR);
       me->set_temp("roomcode_ok/" + query("room_owner_id"),1); 
       write(HIG"������ȷ�������push gate�����ˡ�\n"NOR);
       return 1;

}

int do_push()
{
        object ob;
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("���ſ����أ��㻹��ʲô��\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (me && (! ob || ! living(ob) || ob->is_owner_permit(me) || ! query("code") ))
        {
                message_vision("$N����һ�ƴ��ţ����������š�֨ѽѽ���Ŀ��ˡ�\n",
                               me);
        } else
        if (me && ! ob->is_owner(me))
        {                     
               if ( ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
               { 
                 write(HIR"Ҫ���ݵ�����typecode��������!\n"NOR);
                 return 1; 
               }  else
               {
                  message("vision",  "���š�֨ѽѽ���ı��˴��ˡ�\n",
                  this_object());                  
               }          
               
        } else
        if (ob && living(ob))
        {
                message_vision("$n��æ����ǰ������$N���������˺α���"
                        "�ͣ������ɣ���\n$n����ǰȥ�����������š�֨ѽ"
                        "ѽ�����ƿ��ˡ�\n", me, ob);
        } else
        {
                message("vision",  "���š�֨ѽѽ���ı��˴��ˡ�\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "���š�֨ѽѽ���ı����ƿ��ˡ�\n", room);       
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
                return notify_fail("���Ź����أ��㻹�ٹ�һ�飿\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (! n && me && (! ob || ! living(ob)))
        {
                message_vision("$N����һ�����ţ����������š�֨ѽѽ���Ĺ����ˡ�\n",
                               me);
        } else
        if (! n && me && ! ob->is_owner(me))
        {
                message_vision("$N����ǰȥ���������ϴ��š�\n", me);
        } else
        if (! n && me && ob->is_owner(me))
        {
                message_vision("$n��æ����ǰ������$N���������˺α�"
                        "���ͣ������ɣ���\n$n����ǰȥ���������ϴ��š�\n",
                        me, ob);
        } else
        if (ob && living(ob))
        {
                message("vision", ob->name() + "����ǰȥ���������ϴ��š�\n",
                        this_object());
        } else
        {
                message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n", room);
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
                msg += "һ�ϼ��������Ļ�����ɨ�ѣ���ɨ����Ҷ��";

        if (query("gate") != "open")
                msg += "����ȥ����һ�ȴ��Ž����Ĺر��š�";
        else
                msg += "���ų�����ԶԶ��ȥ����Ȼ�ɼ�ӭ������";

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
                     write(HIR"Ҫ���ݵ�����typecode��������!\n"NOR);
                     return 0; 
            }  
        if (dir != "north" || ! objectp(ob) || ! living(ob))
                return ::valid_leave(me, dir);

        if (ob->is_owner(me))
        {
            if ( ! query("code") )
            { message_vision(HIR"$N��$nС������������,����δ��setcode�������룡��\n"NOR, ob, me);}
            else
               {
                message_vision("$N������$n�����������������\n", ob, me);
               }
                return ::valid_leave(me, dir);
        }

        if (ob->is_owner_permit(me))
        {
                message_vision("$N��$n��������Ȼ�����˵����ѣ������޷�����\n",
                               ob, me);
                return ::valid_leave(me, dir);
        }

        message_vision("$N��$n��������Ȼ֪�����붨���������ѣ������޷���\n", ob, me);
        me->delete_temp("roomcode_ok/" + query("room_owner_id") ); 
        return 1;
}

