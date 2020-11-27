// xiaoyuan.c ���־�СԺ

#include <ansi.h> 

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "СԺ");             /* EXAMPLE */
//**    set("short", "ROOM_NAMEСԺ");
	set("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һЩ��
��ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡�
LONG );

       set("gate", "close");	

	set("exits", ([
		   "north"  : __DIR__"dulewu",     /* EXAMPLE */
                "out"    : "/d/room/xiaoyuan",
	]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_push", "push");
//**    add_action("do_close", "close");       
//**    add_action("set_code", "setcode");
//**    add_action("type_code", "typecode");
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
//**   save();
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
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("���ſ����أ��㻹��ʲô��\n");

        me = this_player();
        
        if (me->query("id") == query("room_owner_id") || ! query("code") )
        {
                message_vision("$N����һ�ƴ��ţ����������š�֨ѽѽ���Ŀ��ˡ�\n",
                               me);
        } else
        if ( me->query("id") != query("room_owner_id") )
        {                     
               if ( ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
               { 
                 write(HIR"Ҫ���ݵ�����typecode��������!\n"NOR);
                 return 1; 
               }     
               message_vision("$N����һ�ƴ��ţ����������š�֨ѽѽ���Ŀ��ˡ�\n",
                               me);
                           
        }        
        

        room = get_object(__DIR__"dulewu");
        message("vision", "���š�֨ѽѽ���ı����ƿ��ˡ�\n", room);       
        set("gate", "open");
        set("exits/north", __DIR__"dulewu");
        room->set("exits/south", __FILE__);
        room->set("gate", "open");
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("���Ź����أ��㻹�ٹ�һ�飿\n");

        me = this_player();
        
        if (! n && me )       
                message_vision("$N����һ�����ţ����������š�֨ѽѽ���Ĺ����ˡ�\n",
                               me);
                        
        message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n",
                        this_object());

        room = get_object(__DIR__"dulewu");
        message("vision", "���š�֨ѽѽ���Ĺ����ˡ�\n", room);
        set("gate", "close");
        delete("exits/north");
        room->delete("exits/south");
        room->set("gate", "close");
        return 1;
}

int valid_leave(object me, string dir)
{
        

//**        if ( dir == "north" &&  me->query("id") != query("room_owner_id") 
//**                 && query("code") &&
//**             ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
//**        { 
//**                 write(HIR"Ҫ���ݵ�����typecode��������!\n"NOR);
//**                 return 0; 
//**        }  
       
        if ( me->query("id") == query("room_owner_id")        
             && ! query("code") )
        {  
           message("vision", HIR"\n����δ��setcode�������룡"
                             "С�ĵ������Ŷ���!\n\n"NOR, me);
         }          

       
        me->delete_temp("roomcode_ok/" + query("room_owner_id") ); 
        return ::valid_leave(me, dir);           
        return 1;
}



