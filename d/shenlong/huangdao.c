// huangdao.c
// Modified by haiyan

inherit ROOM;
 
void create()
{
        set("short", "�ĵ�");
        set("long",@LONG
�����Ǵ��е�һ���µ����㼫ĿԶ�����ƺ��ܿ���һ���ڵ㣬���
�����������ˡ�����ֻ������ˮ�ι�ȥ�ˡ�
LONG);   
        set("no_clean_up", 0);
        set("exits", ([ 
             "south"     : __DIR__"milin", 
        ])); 

        setup();
}

void init()
{
      add_action("do_jump", "jump");
}

int do_jump(string arg)
{
    object me = this_player();

    if( !arg || (arg != "sea" && arg != "dahai" && arg != "hai"))
         return notify_fail("��Ҫ����������\n");

    tell_object(me, "�㡰��ͨ��һ�����뺣�С�\n");
    me->move("/d/shenlong/sea");
    return 1;
}

