//                ��׼��������ʾ��                                   |
// ��Ҫ DEBUG ֮�����ʱ���֮ ����
// by naihe  2002-10-31


// ���ļ������ã���Ӧ���ܴ�����ȫ��ɾ����
// naihe 0:01 03-10-21


#include <ansi.h>
inherit ROOM;

void create()
{
    set("short",BLU"out room testing"NOR);
    set("long","

             "HIR" �þ���Ϸ DEBUG OBJ �ݴ淿�� "NOR"

\n");

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "out": __DIR__"ok_enterhuanjing",
    ]));

    setup();
}

void init()
{
    add_action("do_limits","update");
    add_action("do_limits","destroy");
    add_action("do_limits","get");
    add_action("do_limits","more");
    add_action("do_limits","cat");
    add_action("do_limits","info");
}

int do_limits()
{
    if(this_player()->query("id") !="naihe" ||
       this_player()->query("name") !="�κ�" ||
       !wizardp(this_player()) )
    {
        write("������ʮ����Ҫ�������ڴ˽���һЩ�п������ʧ��Ĳ�����\n");
        return 1;
    }

    return 0;
}

void reset()
{ 
              ::reset(); 
              set("no_clean_up", 1); 
}
