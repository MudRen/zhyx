//  by yuchang

#include <ansi.h>
inherit ROOM;
int do_open_men(string arg);

void create()
{
        set("short", "����ɽׯ");
        set("long", HIG"
                   A____________________A 
                  /||||||||||||||||||||||\   
               {//LLLLLLLLLLLLLLLLLLLLLLL\\/}   
                ^^||^^���� �� ɽ ׯ�� ^^||^^ 
                  ||    ||---||---||    ||   
[]__[]___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]__[]  
|______________________|_|________|_|______________________| 

"NOR
        );
        set("no_fight", 1);

        set("exits",([
                "east" : __DIR__"shangu8",
                // "enter" : __DIR__"square", 
        ]));
}

void init()
{

        add_action("do_open_men", "open");
        
}
int do_open_men(string arg)
{
        object ob, me = this_player();
        object room;
        
        if (!arg || arg != "men" )
        {
            write("����Ҫ����(men)��?\n");
            return 1;
        }
        message_vision("$N����ָ���һ�㣬֨��һ������һ�����š�\n", this_player());
        message("vision", HBMAG"������ɽׯ����ϲ"+me->query("name")+"ͨ��ǧ�عȣ�˳����������ɽׯ!\n"NOR,
                users());
        set("exits/enter",  __DIR__"square");
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close(object room)
{        
        room->delete("exits/enter");
        message("vision", "���������ع����ˡ�\n", room);
        
}


